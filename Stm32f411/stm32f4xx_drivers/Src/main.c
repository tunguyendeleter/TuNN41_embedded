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
#include "systick.h"

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
GPIO_Handle_t Led, Led2, Led3, Led4, Button1, Button2;

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

	Button1.pGPIOx = GPIOA;
	Button1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FE;
	Button1.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	Button1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM(3);
	Button1.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PD;

	Button2.pGPIOx = GPIOB;
	Button2.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FE;
	Button2.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	Button2.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM(8);
	Button2.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PD;


	/*peripheral clock configuration*/
	GPIO_PeriClockControl(GPIOA, ENABLE);
	GPIO_PeriClockControl(GPIOB, ENABLE);
	GPIO_PeriClockControl(GPIOD, ENABLE);

	/*GPIO initialization*/
	GPIO_Init(&Led);
	GPIO_Init(&Led2);
	GPIO_Init(&Led3);
	GPIO_Init(&Led4);
	GPIO_Init(&Button1);
	GPIO_Init(&Button2);

	/*IQR configuration for pin A3, C8*/
	NVIC_IRQConfig(IRQ_NO_EXTI3, 0x15, ENABLE);
	NVIC_IRQConfig(IRQ_NO_EXTI9_5, 0x15, ENABLE);

    /* Config SysTick */
    SysTick_Init(1199999);
    SysTick_StartTimer();

    /* Loop forever */
	while(1)
	{
		if(g_u8ButtonState == 1 && g_systick >= 15)
		{
			GPIO_WriteToOutputPort(GPIOD, 0);
			if(g_u8LedOrder == 1)
				GPIO_WriteToOutputPin(GPIOD, SWITCH_LED1(g_u8LedState), SET);
			else
				GPIO_WriteToOutputPin(GPIOD, SWITCH_LED2(g_u8LedState), SET);

	        g_u8LedState++;
	        g_u8LedState %= 3;
	        g_systick = 0;
		}
	}
	return 0;
}

void EXTI3_IRQHandler(void)
{
	/*clear the EXTI PR register corresponding to the pin number*/
	if(EXTI->PR & (1 << 3))
	{
		/*clear pending */
		EXTI->PR |= (1 << 3);
		g_u8LedOrder++;
		g_u8LedOrder %= 2;
	}
}

void EXTI9_5_IRQHandler(void)
{
	/*clear the EXTI PR register corresponding to the pin number*/
	if(EXTI->PR & (1 << 8))
	{
		/*clear pending */
		EXTI->PR |= (1 << 8);
		g_u8ButtonState++;
		g_u8ButtonState %= 2;
		if(g_u8ButtonState == 0)
		{
			SysTick_StopTimer();
		}else{
			SysTick_StartTimer();
		}
	}
}

void SysTick_Handler(void)
{
	g_systick++;
}
