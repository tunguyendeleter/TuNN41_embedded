/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "TuNN41_OsKernel.h"

/******************************************************************************
 *  USER CONFIGURATION VERIFICATION
 *****************************************************************************/
#if((SOFTWARE_PERIODIC_THREAD_SUPPORT == STD_ON) && (HARDWARE_PERIODIC_THREAD_SUPPORT == STD_ON))
#error "Only one of software or hardware can be used to support periodic thread"
#endif

#if((NUMBER_OF_THREAD > OS_ZERO) && (STATIC_STACK_SIZE < MIN_STATIC_STACK_SIZE))
#error "Stack size should be larger than min stack allowed"
#endif


/******************************************************************************
 *  GLOBAL VARIABLES
 *****************************************************************************/
/**
 * @brief  Init timescale of systick timer in kernel
 */
static uint32 MILLIS_PRESCALER = OS_ZERO;
static uint32 Os_Quanta = OS_ZERO;

/**
 * @brief  Init number of threads are configured in OS 
 */
static uint16 Os_NumberOfThread = OS_ZERO;
static uint16 Os_NumOfPeriThread = OS_ZERO;

/**
 * @brief  Init current pointer to Thread Control Block
 */
Os_TcbType *Os_CurrentTCB = NULL_PTR;

/**
 * @brief  Init current pointer to periodic Thread Control Block
 */
Os_PeriTcbType *Os_CurrentPeriTCB = NULL_PTR;

#if(DYNAMIC_ALLOCATION == STD_OFF)
/**
 * @brief  Init stack region on RAM
 */
Os_RegType TCB_STACK[NUMBER_OF_THREAD][STATIC_STACK_SIZE];
Os_TcbType Os_TCB[NUMBER_OF_THREAD];
#endif


/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/
#if(DYNAMIC_ALLOCATION == STD_ON)
/******************************************************************************
 * Function name:                   :Os_KernelStackInit
 * Description:                     :This function allocate a stack region based on the heap region in memory 
 * Input parameter:                 :ThreadTask (address of task) 
 *                                  :StackSize (stack size)
 * Output parameter:                :None
 * return:                          :E_OK(success)
 *                                  :E_NOT_OK(fail to allocate stack memory)
 *****************************************************************************/
Os_ReturnType Os_KernelStackInit(void (*ThreadTask)(void), uint32 StackSize)
{
    /* Initialize local variables */
    Os_ReturnType Retval = E_OK;
    uint8 lucNumberOfThread;
    Os_TcbType *lpCurrentTCB;
    lucNumberOfThread = Os_NumberOfThread;
    lpCurrentTCB = Os_CurrentTCB;
    
    /* Disable global exceptions */
    asm volatile("CPSID I");

    /* Check NULL_PTR for Os_CurrentTCB */
    if (Os_CurrentTCB == NULL_PTR)
    {
        Os_CurrentTCB = (Os_TcbType *)calloc(1, sizeof(Os_TcbType));
        lpCurrentTCB = Os_CurrentTCB;
    }
    else /* Os_CurrentTCB != NULL_PTR */
    {
        while (lpCurrentTCB->nextPtr != NULL && lpCurrentTCB->nextPtr != Os_CurrentTCB)
        {
            lpCurrentTCB = lpCurrentTCB->nextPtr;
        }

        lpCurrentTCB->nextPtr = (Os_TcbType *)calloc(1, sizeof(Os_TcbType));
        lpCurrentTCB = lpCurrentTCB->nextPtr;
        lpCurrentTCB->nextPtr = Os_CurrentTCB;
    }

    /* Check TCP pointer failed to allocate TCB */
    if (lpCurrentTCB == NULL_PTR)
    {
        Retval = E_NOT_OK;
        return Retval;
    }

    lpCurrentTCB->stackPtr = (Os_RegType *)calloc(StackSize, sizeof(Os_RegType));
    
    /* Check TCP pointer failed to allocate Stack */
    if (lpCurrentTCB->stackPtr == NULL_PTR)
    {
        Retval = E_NOT_OK;
        return Retval;
    }

    lpCurrentTCB->stackSize = StackSize;
    /* Initialize pointer to begin of stack */
    lpCurrentTCB->stackBegin = lpCurrentTCB->stackPtr + StackSize - 1;
    /* Initialize pointer to end of stack */
    lpCurrentTCB->stackEnd = lpCurrentTCB->stackPtr;
    /* Rechange position of stack pointer to top of stack */
    lpCurrentTCB->stackPtr = lpCurrentTCB->stackBegin - 15;

    /* Initialize dummy values for General-Purpose Registers */
    /* Caller registers: xPSR, PC, LR, R12, R3, R2, R1, R0 */
    *(lpCurrentTCB->stackBegin - STACK_XPSR_OFFSET) = (1 << 24);                    /* xPSR: T bit = 1(Thump state) */
    *(lpCurrentTCB->stackBegin - STACK_PC_OFFSET) = (Os_RegType)(ThreadTask);       /* PC: function address */
    *(lpCurrentTCB->stackBegin - STACK_LR_OFFSET) = 0XAAAAAAAAU;                    /* LR: link return */
    *(lpCurrentTCB->stackBegin - STACK_R12_OFFSET) = 0XAAAAAAAAU;                   /* R12 */
    *(lpCurrentTCB->stackBegin - STACK_R3_OFFSET) = 0XAAAAAAAAU;                    /* R3 */
    *(lpCurrentTCB->stackBegin - STACK_R2_OFFSET) = 0XAAAAAAAAU;                    /* R2 */
    *(lpCurrentTCB->stackBegin - STACK_R1_OFFSET) = 0XAAAAAAAAU;                    /* R1 */
    *(lpCurrentTCB->stackBegin - STACK_R0_OFFSET) = 0XAAAAAAAAU;                    /* R0 */

    /* Callee register: R11, R10, R9, R8, R7, R6, R5, R4 */
    *(lpCurrentTCB->stackBegin - STACK_R11_OFFSET) = 0XAAAAAAAAU;                   /* R11 */
    *(lpCurrentTCB->stackBegin - STACK_R10_OFFSET) = 0XAAAAAAAAU;                   /* R10 */
    *(lpCurrentTCB->stackBegin - STACK_R9_OFFSET) = 0XAAAAAAAAU;                    /* R9 */
    *(lpCurrentTCB->stackBegin - STACK_R8_OFFSET) = 0XAAAAAAAAU;                    /* R8 */
    *(lpCurrentTCB->stackBegin - STACK_R7_OFFSET) = 0XAAAAAAAAU;                    /* R7 */
    *(lpCurrentTCB->stackBegin - STACK_R6_OFFSET) = 0XAAAAAAAAU;                    /* R6 */
    *(lpCurrentTCB->stackBegin - STACK_R5_OFFSET) = 0XAAAAAAAAU;                    /* R5 */
    *(lpCurrentTCB->stackBegin - STACK_R4_OFFSET) = 0XAAAAAAAAU;                    /* R4 */

    /* Increase num of threads used */
    lucNumberOfThread++;
    Os_NumberOfThread = lucNumberOfThread;
    
    return Retval;
}
#endif


#if(DYNAMIC_ALLOCATION == STD_ON)
/******************************************************************************
 * Function name:                   :Os_KernelStackRelease
 * Description:                     :This function release a stack region based on the heap region in memory
 * Input parameter:                 :ThreadTask (address of task) 
 * Output parameter:                :None
 * return:                          :E_OK(success)
 *                                  :E_NOT_OK(fail to release stack memory)
 *****************************************************************************/
Os_ReturnType Os_KernelStackRelease(void (*ThreadTask)(void))
{
    /* Initialize local variables */
    Os_ReturnType Retval = E_OK;
    uint8 lucNumberOfThread;
    Os_TcbType *lpCurrentTCB;
    Os_TcbType *lpCurrentTCB2;
    lucNumberOfThread = Os_NumberOfThread;
    lpCurrentTCB = Os_CurrentTCB;

    /* Check invalid number of thread, and invalid TCB pointer */
    if (lucNumberOfThread == 0 || lpCurrentTCB == NULL)
    {
        Retval = E_NOT_OK;
        return Retval;
    }

    /* Check first TCB in list */
    if (*(lpCurrentTCB->stackPtr + STACK_PC_OFFSET) != (Os_RegType)(ThreadTask))
    {
        Os_CurrentTCB = Os_CurrentTCB->nextPtr;
        free(lpCurrentTCB->stackPtr);
        free(lpCurrentTCB);
        return Retval;
    }
    
    /* Check a TCB in list with specific ThreadTask */
    while (lpCurrentTCB->nextPtr != NULL_PTR && (*(lpCurrentTCB->nextPtr->stackPtr + STACK_PC_OFFSET) != (Os_RegType)(ThreadTask)))
    {
        lpCurrentTCB = lpCurrentTCB->nextPtr;
    }
    if (lpCurrentTCB == NULL_PTR)
    {
        Retval = E_NOT_OK;
        return Retval;
    }
    
    lpCurrentTCB2 = lpCurrentTCB->nextPtr;
    lpCurrentTCB->nextPtr = lpCurrentTCB->nextPtr->nextPtr;
    free(lpCurrentTCB2->stackPtr);
    free(lpCurrentTCB2);

    /* Decrease num of threads used */
    if (Retval == E_OK)
    {
        Os_NumberOfThread--;
    }
    return Retval;
}
#endif



#if(DYNAMIC_ALLOCATION == STD_OFF && NUMBER_OF_THREAD > 0)
/******************************************************************************
 * Function name:                   :Os_KernelStackInit
 * Description:                     :This function init a stack region on RAM in memory
 * Input parameter:                 :NumOfThread (number of thread: NUMBER_THREAD(x)) 
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Os_KernelStackInit(uint32 NumOfThread)
{
    for (uint32 stackIdx = 0; stackIdx < NumOfThread; stackIdx++)
    {
        Os_TCB[stackIdx].stackPtr = &TCB_STACK[stackIdx][STATIC_STACK_SIZE-16];
        /*Set bit21 (T-Bit) in PSR to 1 to operate it*/
        /*Thumb Mode*/
        TCB_STACK[stackIdx][STATIC_STACK_SIZE-1] = 1<<24;	            /* PSR */
        /*Skip the PC*/
        /*Dumming Stack Content*/
        TCB_STACK[stackIdx][STATIC_STACK_SIZE-3] = 0xAAAAAAAA;          /* R14 (LR) */
        TCB_STACK[stackIdx][STATIC_STACK_SIZE-4] = 0xAAAAAAAA;          /* R12 */
        TCB_STACK[stackIdx][STATIC_STACK_SIZE-5] = 0xAAAAAAAA;          /* R3 */
        TCB_STACK[stackIdx][STATIC_STACK_SIZE-6] = 0xAAAAAAAA;          /* R2 */
        TCB_STACK[stackIdx][STATIC_STACK_SIZE-7] = 0xAAAAAAAA;          /* R1 */
        TCB_STACK[stackIdx][STATIC_STACK_SIZE-8] = 0xAAAAAAAA;          /* R0 */
        
        TCB_STACK[stackIdx][STATIC_STACK_SIZE-9] = 0xAAAAAAAA;          /* R11 */
        TCB_STACK[stackIdx][STATIC_STACK_SIZE-10] = 0xAAAAAAAA;         /* R10 */
        TCB_STACK[stackIdx][STATIC_STACK_SIZE-11] = 0xAAAAAAAA;         /* R9 */
        TCB_STACK[stackIdx][STATIC_STACK_SIZE-12] = 0xAAAAAAAA;         /* R8 */
        TCB_STACK[stackIdx][STATIC_STACK_SIZE-13] = 0xAAAAAAAA;         /* R7 */
        TCB_STACK[stackIdx][STATIC_STACK_SIZE-14] = 0xAAAAAAAA;         /* R6 */
        TCB_STACK[stackIdx][STATIC_STACK_SIZE-15] = 0xAAAAAAAA;         /* R5 */
        TCB_STACK[stackIdx][STATIC_STACK_SIZE-16] = 0xAAAAAAAA;         /* R4 */
    }
}
#endif

#if(DYNAMIC_ALLOCATION == STD_OFF && NUMBER_OF_THREAD > 0)
/******************************************************************************
 * Function name:                   :Os_KernelAddThread
 * Description:                     :This function add tasks to TCB and link TCB together
 * Input parameter:                 :NumOfThread (number of thread: NUMBER_THREAD(x)) 
 *                                  :... (Follow by x number of addresses of tasks)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Os_KernelAddThread(uint32 NumOfThread, ...)
{
    Os_NumberOfThread = NumOfThread;
    va_list argv;
    va_start(argv, NumOfThread);

    /* Disable global exceptions */
    asm volatile("CPSID I");

    for (uint32 idx = 0; idx < NumOfThread; idx++)
    {
        uint32 PC = va_arg(argv, uint32);
        TCB_STACK[idx][STATIC_STACK_SIZE-2] = PC;
    }

    va_end(argv);

    /* Connect Os_TCB to the next Os_TCB */
    for (uint32 idx = 0; idx < NumOfThread; idx++)
    {
        if (idx < NumOfThread - 1)
        {
            Os_TCB[idx].nextPtr = &Os_TCB[idx + 1];
        }
    }
    Os_TCB[NumOfThread - 1].nextPtr = &Os_TCB[0];

    /* Init Os_CurrentTCB pointer to the first Os_TCB */
    Os_CurrentTCB = &Os_TCB[0];
}
#endif

/******************************************************************************
 * Function name:                   :Os_KernelInit
 * Description:                     :This function init MILLIS_PRESCALER, and Os_Quanta varible
 * Input parameter:                 :quanta (period for a thread running in scheduler) 
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Os_KernelInit(uint32 quanta)
{
    MILLIS_PRESCALER = (BUS_DIV_8/1000);
    Os_Quanta = quanta;
}

/******************************************************************************
 * Function name:                   :Os_KernelLaunch
 * Description:                     :This function init a systick timer with MILLIS_PRESCALER
 * Input parameter:                 :None
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Os_KernelLaunch(void)
{
    /* Disable timer to configure timer */
    SysTick->CSR &= ~(1 << SYSTICK_CSR_ENABLE_SHIFT);

    /* Configure clock source from processor */
    SysTick->CSR |= (SYSTICK_CSR_CLKSOURCE_EXTERNAL << SYSTICK_CSR_CLKSOURCE_SHIFT);

    /* Enable interrupt request to  systick timer */
    SysTick->CSR |= (1 << SYSTICK_CSR_TICKINT_SHIFT);

    /* Reload value [0:24] bits: max count value = 16,777,215 - 1 */
    SysTick->RVR = (Os_Quanta*MILLIS_PRESCALER - 1) & SYSTICK_CVR_CURRENT_MASK;

    /* Clear current value */
    SysTick->CVR = 1;

    /* Enable timer to start timer*/
    SysTick->CSR |= (1 << SYSTICK_CSR_ENABLE_SHIFT);

    // Os_PeriodicTaskInit();
	Os_SchedulerLaunch();
}

/******************************************************************************
 * Function name:                   :Os_ThreadYield
 * Description:                     :This function release resource to other threads before timeout quanta
 * Input parameter:                 :None
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Os_ThreadYield(void)
{
    /* Clear current value */
    SysTick->CVR = 0;
    
    /* Set pending systick event by software */
    ICSR |= (1 << ICSR_PENDSTSET_SHIFT);
}

/******************************************************************************
 * Function name:                   :Os_SemaphoreInit
 * Description:                     :This function init value of semaphore
 * Input parameter:                 :value (initial value of semaphore)
 * Output parameter:                :semaphore (semaphore value)
 * return:                          :None
 *****************************************************************************/
void Os_SemaphoreInit(Os_Semaphore *semaphore, uint32 value)
{
	*semaphore = value;
}

/******************************************************************************
 * Function name:                   :Os_SemaphoreGive
 * Description:                     :This function give semaphore
 * Input parameter:                 :None
 * Output parameter:                :semaphore (semaphore value)
 * return:                          :None
 *****************************************************************************/
void Os_SemaphoreGive(Os_Semaphore *semaphore)
{
	asm volatile("CPSID I");
	*semaphore +=1;
	asm volatile("CPSIE I");
}

/******************************************************************************
 * Function name:                   :Os_SpinLockWait
 * Description:                     :This function block the Thread and wait for semaphore
 * Input parameter:                 :None
 * Output parameter:                :semaphore (semaphore value)
 * return:                          :None
 *****************************************************************************/
void Os_SpinLockWait(Os_Semaphore *semaphore)
{
	asm volatile("CPSID I");
	
	while(*semaphore <= 0){
	    asm volatile("CPSIE I");
	    asm volatile("CPSID I");
	}
	*semaphore -=1;
	
	asm volatile("CPSID I");
}

/******************************************************************************
 * Function name:                   :Os_CooperativeWait
 * Description:                     :This function block the Thread and release thread for semaphore
 * Input parameter:                 :None
 * Output parameter:                :semaphore (semaphore value)
 * return:                          :None
 *****************************************************************************/
void Os_CooperativeWait(Os_Semaphore *semaphore)
{
	asm volatile("CPSID I");
	
	while(*semaphore <= 0){
	    asm volatile("CPSIE I");
        Os_ThreadYield();
	    asm volatile("CPSID I");
	}
	*semaphore -=1;
	
	asm volatile("CPSID I");
}

/******************************************************************************
 * Function name:                   :Os_SchedulerRoundRobin
 * Description:                     :This function run scheduler with round robin
 * Input parameter:                 :None
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Os_SchedulerRoundRobin(void)
{
#if(SOFTWARE_PERIODIC_THREAD_SUPPORT == STD_ON)
    Os_PeriTcbType *lpCurrentPeriTCB = Os_CurrentPeriTCB;
    while (lpCurrentPeriTCB != NULL_PTR)
    {
        /* Loop to check all periodic TCB if timeleft is zero */
        lpCurrentPeriTCB->TimeLeft -= Os_Quanta;
        if (lpCurrentPeriTCB->TimeLeft == OS_ZERO)
        {
            /* Call periodic task and update timeleft */
            lpCurrentPeriTCB->ThreadTask();
            lpCurrentPeriTCB->TimeLeft = lpCurrentPeriTCB->Period;
        }
        lpCurrentPeriTCB = lpCurrentPeriTCB->nextPtr;
    }
#endif
    Os_CurrentTCB = Os_CurrentTCB->nextPtr;
}

/******************************************************************************
 * Function name:                   :SysTick_Handler
 * Description:                     :This function create PENSV exception by software
 * Input parameter:                 :None
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void SysTick_Handler(void)
{
    ICSR |= (1 << ICSR_PENDSVSET_SHIFT);
}

/******************************************************************************
 * Function name:                   :Os_KernelAddPeriodicTask
 * Description:                     :This function add periodic tasks to periodic TCB
 * Input parameter:                 :NumOfPeriodicTask
 *                                  :... (Follow by x number of addresses of periodic tasks)
 * Output parameter:                :None
 * return:                          :E_OK(assign tasks to TCB successfully)
 *                                  :E_NOT_OK(fail to assign tasks to TCB)
 *****************************************************************************/
Os_ReturnType Os_KernelAddPeriodicTask(uint32 NumOfPeriodicTask, ...)
{
    Os_ReturnType Retval = E_NOT_OK;
    Os_PeriTcbType *lpCurrentPeriTCB = NULL_PTR; 
    boolean lucPeriodCheck = OS_TRUE;

    /* Disable global exceptions */
    asm volatile("CPSID I");

    /* Check not enough parameters */
    if (NumOfPeriodicTask % 2 == OS_ZERO)
    {
        va_list argv;
        va_start(argv, NumOfPeriodicTask);

        for (uint32 idx = 0; idx < NumOfPeriodicTask/2; idx++)
        {
            if (lucPeriodCheck == OS_TRUE)
            {
                /* Assign task address to TCB */
                uint32 Task = va_arg(argv, uint32);
                /* Assign time period to TCB */
                uint32 Period = va_arg(argv, uint32);
                
                if (Period % Os_Quanta)
                {
                    lucPeriodCheck = OS_FALSE;
                    continue;
                }
                
                /* Connect Os_TCB to the next Os_TCB */
                if (Os_CurrentPeriTCB == NULL_PTR)
                {                
                    Os_CurrentPeriTCB = (Os_PeriTcbType *)calloc(1, sizeof(Os_PeriTcbType));
                    lpCurrentPeriTCB = Os_CurrentPeriTCB;
                }
                else /* Os_CurrentPeriTCB == NULL_PTR */
                {
                    Os_CurrentPeriTCB->nextPtr = (Os_PeriTcbType *)calloc(1, sizeof(Os_PeriTcbType));
                    Os_CurrentPeriTCB = Os_CurrentPeriTCB->nextPtr;
                }
                
                /* Assign Thread information to TCB */
                Os_CurrentPeriTCB->ThreadTask = (void*)Task;
                Os_CurrentPeriTCB->Period = Period;
                Os_CurrentPeriTCB->TimeLeft = Period;
                Os_CurrentPeriTCB->nextPtr = NULL_PTR;
            }
        }

        va_end(argv);
    }
    
    if (lucPeriodCheck != OS_FALSE)
    {
        Retval = E_OK;
        Os_NumOfPeriThread += NumOfPeriodicTask/2;
    }
    /* Init Os_CurrentTCB pointer to the first Os_TCB */
    Os_CurrentPeriTCB = lpCurrentPeriTCB;
    
    return Retval;
}

#if(HARDWARE_PERIODIC_THREAD_SUPPORT == STD_ON)
/******************************************************************************
 * Function name:                   :Os_PeriodicTaskHardwareInit
 * Description:                     :This function init hardware timer TIM2 for periodic TCB
 * Input parameter:                 :Frequency (frequency to call exception)
 *                                  :Priority (priority for ISR)
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Os_PeriodicTaskHardwareInit(uint32 Frequency, uint8_t Priority)
{
    /* Disable global exceptions */
    asm volatile("CPSID I");

    /* Enable module clock on APB bus */
	TIM2_CLK_EN();

    /* Config timer prescaler: APB2 = 16M */
	TIM2->PSC = 16-1;

    /* Config Auto-reload register */
	TIM2->ARR = 1000000/Frequency -1;

    /* Enable interrupt */
	TIM2->DIER |= 1;

    /* Enable timer */
	TIM2->CR1 |= 1;

    /* setup ISER register */
    NVIC->ICPR[28/32] |= (1 << (28 % 32));
    NVIC->ISER[28/32] |= (1 << (28 % 32));
    /* setup IP register */
    NVIC->IP[28] = (Priority);
}
#endif

#if(HARDWARE_PERIODIC_THREAD_SUPPORT == STD_ON)
/******************************************************************************
 * Function name:                   :Os_CallbackPeriodicTask
 * Description:                     :This function is placed in exception handler to call periodic tasks
 * Input parameter:                 :None
 * Output parameter:                :None
 * return:                          :None
 *****************************************************************************/
void Os_CallbackPeriodicTask(void)
{
    Os_PeriTcbType *lpCurrentPeriTCB = Os_CurrentPeriTCB;
    while (lpCurrentPeriTCB != NULL_PTR)
    {
        /* Loop to check all periodic TCB if timeleft is zero */
        lpCurrentPeriTCB->TimeLeft--;
        if (lpCurrentPeriTCB->TimeLeft == OS_ZERO)
        {
            /* Call periodic task and update timeleft */
            lpCurrentPeriTCB->ThreadTask();
            lpCurrentPeriTCB->TimeLeft = lpCurrentPeriTCB->Period;
        }
        lpCurrentPeriTCB = lpCurrentPeriTCB->nextPtr;
    }
}
#endif
