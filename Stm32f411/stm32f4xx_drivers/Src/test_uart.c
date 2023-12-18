/****************************************************************/
/**
 *  file        main.c
 *  containts   Run application code
 */
/****************************************************************/

/****************************************************************/
/*  Includes section                                            */
/****************************************************************/
#include "stm32f411xx.h"
#include "gpio2.h"
#include "nvic.h"
#include "usart.h"
#include "systick.h"
#include "string.h"

/****************************************************************/
/*  Define section                                              */
/****************************************************************/
/**
* @brief    Define LED order of R -> O -> Y
*/
#define SWITCH_LED1(X) ((X == 0) ? (12) : ((X == 1) ? (13) : (14)))
/**
* @brief    Define LED order of Y -> O -> R
*/
#define SWITCH_LED2(X) ((X == 0) ? (14) : ((X == 1) ? (13) : (12)))

/****************************************************************/
/*  Global variable                                             */
/****************************************************************/
/**
* @brief    Define global variable to store led state, order state, systick value
*/
volatile uint8 g_u8ButtonState;
volatile uint8 g_u8LedOrder;
volatile uint32 g_systick;
uint8 g_u8LedState;
GPIO_Handle_t Led, Led2, Led3, Led4, TX_Pin, RX_Pin;
USART_Handle_Type Usart2;
char hello[20] = "HELLO WORLD???\n\r";
char read[1024];

#define ButtonNum 0
uint8 change = 0;

/****************************************************************/
/*  Internal function                                           */
/****************************************************************/
void EXTI0_IRQHandler(void);


/****************************************************************/
/*  MAIN FUNCTION	                                            */
/****************************************************************/
int main(void)
{
    g_u8ButtonState = 1;
    g_u8LedState = 0;
    g_u8LedOrder = 1;
    g_systick = 0;
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

	Usart2.pUSARTx = USART2;
	Usart2.USART_Config.USART_Baud = USART_STD_BAUD_9600;
	Usart2.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;
	Usart2.USART_Config.USART_Mode = USART_MODE_TXRX;
	Usart2.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
	Usart2.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
	Usart2.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;

	/*peripheral clock configuration*/
	GPIO_PeriClockControl(GPIOA, ENABLE);
	GPIO_PeriClockControl(GPIOB, ENABLE);
	GPIO_PeriClockControl(GPIOD, ENABLE);
	USART_PeriClockControl(USART2, ENABLE);

	/*GPIO initialization*/
	GPIO_Init(&Led);
	GPIO_Init(&Led2);
	GPIO_Init(&Led3);
	GPIO_Init(&Led4);
	GPIO_Init(&TX_Pin);
	GPIO_Init(&RX_Pin);

	/*UASRT1 initialization*/
	USART_Init(&Usart2);
	USART_SetBaudRate(&Usart2);

	/* Config NVIC for USART */
	NVIC_IRQConfig(38, 15, ENABLE);

    /* Config SysTick */
    SysTick_Init(1199999);
    SysTick_StartTimer();

    /* Loop forever */
	while(1)
	{
//		if(g_systick >= 10)
//		{
			volatile uint32 i = 0xffff;
			while(i--);
			while(USART_ReadIT(&Usart2, (uint8 *)read, 6) != USART_READY);
//			USART_WriteIT(&Usart2, (uint8 *)hello, strlen(hello));
			
//			g_systick = 0;
//		}
	}
	return 0;
}

void USART2_IRQHandler(void)
{
	USART_IRQHandling(&Usart2);
}

void SysTick_Handler(void)
{
	g_systick++;
}
