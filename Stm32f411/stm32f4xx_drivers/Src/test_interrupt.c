/****************************************************************/
/**
 *  file        test_interrupt.c
 *  containts   Run application code
 */
/****************************************************************/

/****************************************************************/
/*  Includes section                                            */
/****************************************************************/
#include "stm32f411xx.h"
#include "TuNN41_OsKernel.h"
#include "usart.h"
#include "gpio2.h"
#include "systick.h"

/****************************************************************/
/*  Define section                                              */
/****************************************************************/
/**
* @brief    Define LED order of Led1 -> Led2 -> Led3 -> Led4
*/
#define SWITCH_LED(X) ((X == 0) ? (12) : ((X == 1) ? (13) : ((X == 2) ? (14) : (15))))


/****************************************************************/
/*  Global variable                                             */
/****************************************************************/
/**
* @brief    Define global variable to store led state, order state, systick value
*/
volatile uint8 ucLedOrder = 0;
volatile uint8 ucTick = 0;
GPIO_Handle_Type Led, Led2, Led3, Led4, TX_Pin, RX_Pin;
USART_Handle_Type Usart2;
Os_Semaphore semaphore;
volatile int a = 0;
volatile int b = 0;
volatile int c = 0;
volatile int d = 0;
volatile int e = 0;
volatile int f = 0;


/****************************************************************/
/*  Internal function                                           */
/****************************************************************/
int sum(int a, int b)
{
	return a + b;
}

void ThreadTask(void)
{
	while(1)
	{
		Os_CooperativeWait(&semaphore);
		a++;
//		USART_Write(&Usart2, (uint8*)"Hello_world1_!!!\n\r", 18);
		Os_SemaphoreGive(&semaphore);
	}
}
void ThreadTask2(void)
{
	while(1)
	{
		Os_CooperativeWait(&semaphore);
		b++;
//		USART_Write(&Usart2, (uint8*)"Hello_world2_!!!\n\r", 18);
		Os_SemaphoreGive(&semaphore);
	}
}
void ThreadTask3(void)
{
	while(1)
	{
		Os_CooperativeWait(&semaphore);
		c++;
//		USART_Write(&Usart2, (uint8*)"Hello_world3_!!!\n\r", 18);
		Os_SemaphoreGive(&semaphore);
	}
}

void ThreadTask4(void)
{
		d++;
//		USART_Write(&Usart2, (uint8*)"Hello_world3_!!!\n\r", 18);
}

void ThreadTask5(void)
{
		e++;
//		USART_Write(&Usart2, (uint8*)"Hello_world3_!!!\n\r", 18);
}

void BlinkLed(void)
{
	ucLedOrder = (ucLedOrder < 3)?(ucLedOrder + 1):(0);
	GPIO_WriteToOutputPort(GPIOD, 0);
	GPIO_WriteToOutputPin(GPIOD, SWITCH_LED(ucLedOrder), SET);
}
/****************************************************************/
/*  MAIN FUNCTION	                                            */
/****************************************************************/
int main(void)
{
	Led.pGPIOx = GPIOD;
	Led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	Led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM(12);
	Led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	Led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	Led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	Led2.pGPIOx = GPIOD;
	Led2.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	Led2.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM(13);
	Led2.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	Led2.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	Led2.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	Led3.pGPIOx = GPIOD;
	Led3.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	Led3.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM(15);
	Led3.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	Led3.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	Led3.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	Led4.pGPIOx = GPIOD;
	Led4.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	Led4.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM(14);
	Led4.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	Led4.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	Led4.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	
	Usart2.pUSARTx = USART2;
	Usart2.USART_Config.USART_Baud = USART_STD_BAUD_9600;
	Usart2.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;
	Usart2.USART_Config.USART_Mode = USART_MODE_TXRX;
	Usart2.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
	Usart2.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
	Usart2.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
	
	TX_Pin.pGPIOx = GPIOA;
	TX_Pin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALT;
	TX_Pin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	TX_Pin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM(2);
	TX_Pin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	TX_Pin.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_ALT_NUM(7);

	RX_Pin.pGPIOx = GPIOA;
	RX_Pin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALT;
	RX_Pin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	RX_Pin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	RX_Pin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM(3);
	RX_Pin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	RX_Pin.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_ALT_NUM(7);

	/*peripheral clock configuration*/
	GPIO_PeriClockControl(GPIOD, ENABLE);
	GPIO_PeriClockControl(GPIOA, ENABLE);
	USART_PeriClockControl(USART2, ENABLE);

	/*GPIO initialization*/
	GPIO_Init(&Led);
	GPIO_Init(&Led2);
	GPIO_Init(&Led3);
	GPIO_Init(&Led4);
	GPIO_Init(&TX_Pin);
	GPIO_Init(&RX_Pin);

	/*UASRT2 initialization*/
	USART_Init(&Usart2);
	USART_SetBaudRate(&Usart2);

#if(DYNAMIC_ALLOCATION == STD_OFF)
	/* Static allocation */
	Os_SemaphoreInit(&semaphore, 1);
	Os_KernelInit(10);
	Os_KernelStackInit(NUMBER_THREAD(3));
	Os_KernelAddThread(NUMBER_THREAD(3), ThreadTask, ThreadTask2, ThreadTask3);
#if(HARDWARE_PERIODIC_THREAD_SUPPORT == STD_ON)
	Os_PeriodicTaskHardwareInit(1000, 5);
#endif
	Os_KernelAddPeriodicTask(NUMBER_PERIODIC_THREAD(2), ThreadTask4, 1000,ThreadTask5, 2000);
	Os_KernelLaunch();
#else
	/* Dynamic allocation */
	Os_SemaphoreInit(&semaphore, 1);
	Os_KernelInit(10);
	Os_KernelStackInit(ThreadTask, 100);
	Os_KernelStackInit(ThreadTask2, 100);
	Os_KernelStackInit(ThreadTask3, 100);
#if(HARDWARE_PERIODIC_THREAD_SUPPORT == STD_ON)
	Os_PeriodicTaskHardwareInit(1000, 5);
#endif
	Os_KernelAddPeriodicTask(NUMBER_PERIODIC_THREAD(2), BlinkLed, 1000, ThreadTask4, 2000);
	Os_KernelLaunch();
#endif

    while (1)
    {
    }    
	return 0;
}



/****************************************************************/
/*  Exception handlers                                          */
/****************************************************************/

#if(HARDWARE_PERIODIC_THREAD_SUPPORT == STD_ON)
void TIM2_IRQHandler(){
	TIM2->SR = 0;
	Os_CallbackPeriodicTask();
}
#endif
