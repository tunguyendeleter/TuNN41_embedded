#ifndef INC_TUNN41_OSKERNEL_H_
#define INC_TUNN41_OSKERNEL_H_

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "stm32f411xx.h"
#include "TuNN41_OsScheduler.h"
#include "systick.h"
#include <stdlib.h>
#include <stdarg.h>


/******************************************************************************
 *  USER CONFIGURATION MACROS
 *****************************************************************************/
/**
 * @brief  Config Thread allocation
 */
#define DYNAMIC_ALLOCATION                      STD_ON
#define SOFTWARE_PERIODIC_THREAD_SUPPORT        STD_ON
#define HARDWARE_PERIODIC_THREAD_SUPPORT        STD_OFF

/**
 * @brief  Config static stack size
 */
#define STATIC_STACK_SIZE                       100U
#define NUMBER_OF_THREAD                        3


/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/**
 * @brief  Define type of common macros 
 */
#define MIN_STATIC_STACK_SIZE					(30U)
#define THREAD_ID(X)                            ((uint8)(0XFFU&X))
#define NUMBER_PERIODIC_THREAD(X)               (X*2)
#define NUMBER_THREAD(X)                        (X)
#define E_OK                                    (0U)
#define E_NOT_OK                                (1U)
#define OS_ZERO                                 (0U)
#define OS_TRUE                                 (1U)
#define OS_FALSE                                (0U)
#define STD_ON                                  E_OK
#define STD_OFF                                 E_NOT_OK
#define STACK_XPSR_OFFSET                       (0U)
#define STACK_PC_OFFSET                         (1U)
#define STACK_LR_OFFSET                         (2U)
#define STACK_R12_OFFSET                        (3U)
#define STACK_R3_OFFSET                         (4U)
#define STACK_R2_OFFSET                         (5U)
#define STACK_R1_OFFSET                         (6U)
#define STACK_R0_OFFSET                         (7U)
#define STACK_R11_OFFSET                        (8U)
#define STACK_R10_OFFSET                        (9U)
#define STACK_R9_OFFSET                         (10U)
#define STACK_R8_OFFSET                         (11U)
#define STACK_R7_OFFSET                         (12U)
#define STACK_R6_OFFSET                         (13U)
#define STACK_R5_OFFSET                         (14U)
#define STACK_R4_OFFSET                         (15U)

/**
 * @brief  Define type of stack allocation 
 */
#define BUS_DIV_8                               2000000U

/**
 * @brief  Define address and bit-shift of ICSR register 
 */
#define ICSR                                    *((volatile uint32*)(0xE000ED04))
#define ICSR_PENDSTSET_SHIFT                    26U
#define ICSR_PENDSVSET_SHIFT                    28U


/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/
/**
 * @brief  Define type of general-purpose register pointer
 */
typedef uint32 Os_RegType;

/**
 * @brief  Define type of semaphore variable
 */
typedef uint32 Os_Semaphore;

/**
 * @brief  Define common return type
 */
typedef uint8 Os_ReturnType;
typedef uint8 boolean;

/**
 * @brief  Define structure of specific Thread infomation
 */
typedef struct Os_ThreadInfo
{
    uint8 Os_ThreadID;                          /* Thread ID */
    uint8 Os_State;                             /* Thread state in Scheduler */
}Os_ThreadInfoType;

/**
 * @brief  Define structure of normal Thread Control Block
 */
typedef struct Os_Tcb
{
    Os_RegType *stackPtr;                       /* Pointer to Top of Stack in RAM */
    struct Os_Tcb *nextPtr;                     /* Pointer to next Thread Control Block */
    Os_RegType *stackBegin;                     /* Pointer to begin of stack in thread */
    Os_RegType *stackEnd;                       /* Pointer to end of stack in thread */
    uint32 stackSize;                           /* Size of start in thread */
    Os_ThreadInfoType TcpInfo;
}Os_TcbType;

/**
 * @brief  Define structure of periodic Thread Control Block
 */
typedef struct Os_PeriTcb
{
    struct Os_PeriTcb *nextPtr;                 /* Time to run the thread */
    void (*ThreadTask)(void);                   /* Task to run */
    uint32 Period;                              /* Time to run the thread */
    uint32 TimeLeft;                            /* Time left for waiting before running */
}Os_PeriTcbType;


/******************************************************************************
 *  GLOBAL VARIABLES
 *****************************************************************************/
/**
 * @brief  Declear current pointer to Thread Control Block
 */
extern Os_TcbType *Os_CurrentTCB;

/**
 * @brief  Declear current pointer to periodic Thread Control Block
 */
extern Os_PeriTcbType *Os_CurrentPeriTCB;

#if(DYNAMIC_ALLOCATION == STD_OFF)
/**
 * @brief  Declear stack region on RAM
 */
extern Os_RegType TCB_STACK[NUMBER_OF_THREAD][STATIC_STACK_SIZE];
extern Os_TcbType Os_TCB[NUMBER_OF_THREAD];
#endif


/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/
#if(DYNAMIC_ALLOCATION == STD_ON)
/**
 * @brief  This function allocate a stack region based on the heap region in memory
 */
extern Os_ReturnType Os_KernelStackInit(void (*ThreadTask)(void), uint32 StackSize);

/**
 * @brief  This function release a stack region based on the heap region in memory
 */
extern Os_ReturnType Os_KernelStackRelease(void (*ThreadTask)(void));
#endif

#if(DYNAMIC_ALLOCATION == STD_OFF && NUMBER_OF_THREAD > 0)
/**
 * @brief  This function init a stack region on RAM in memory
 */
extern void Os_KernelStackInit(uint32 NumOfThread);

/**
 * @brief  This function add tasks to TCB and link TCB together
 */
extern void Os_KernelAddThread(uint32 NumOfThread, ...);
#endif

/**
 * @brief  This function init MILLIS_PRESCALER variable
 */
extern void Os_KernelInit(uint32 quanta);

/**
 * @brief  This function init a systick timer with MILLIS_PRESCALER
 */
extern void Os_KernelLaunch(void);

/**
 * @brief  This function init a systick timer with MILLIS_PRESCALER
 */
extern void Os_ThreadYield(void);

/**
 * @brief  This function init value of semaphore
 */
extern void Os_SemaphoreInit(Os_Semaphore *semaphore, uint32 value);

/**
 * @brief  This function give semaphore
 */
extern void Os_SemaphoreGive(Os_Semaphore *semaphore);

/**
 * @brief  This function block the Thread and wait for semaphore
 */
extern void Os_SpinLockWait(Os_Semaphore *semaphore);

/**
 * @brief  This function block the Thread and release thread for semaphore
 */
extern void Os_CooperativeWait(Os_Semaphore *semaphore);

/**
 * @brief  This function run scheduler with round robin 
 */
extern void Os_SchedulerRoundRobin(void);

/**
 * @brief  This function add periodic tasks to periodic TCB
 */
extern Os_ReturnType Os_KernelAddPeriodicTask(uint32 NumOfPeriodicTask, ...);

#if(SOFTWARE_PERIODIC_THREAD_SUPPORT == STD_ON)
/**
 * @brief  This function init hardware timer TIM2 for periodic TCB
 */
extern void Os_PeriodicTaskHardwareInit(uint32 Frequency, uint8_t Priority);

/**
 * @brief  This function is placed in exception handler to call periodic tasks
 */
extern void Os_CallbackPeriodicTask(void);
#endif

#endif /* INC_TUNN41_OSKERNEL_H_ */
