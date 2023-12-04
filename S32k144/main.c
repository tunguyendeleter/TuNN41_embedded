/****************************************************************/
/**
 *  file        main.h
 *  containts   Run application code
 */
/****************************************************************/

/****************************************************************/
/*  Includes section                                            */
/****************************************************************/
#include "port.h"
#include "nvic.h"
#include "systick.h"

/****************************************************************/
/*  Define section                                              */
/****************************************************************/
#define SWITCH_LED1(X) ((X == 0) ? (0) : ((X == 1) ? (15) : (16)))
#define SWITCH_LED2(X) ((X == 16) ? (0) : ((X == 1) ? (15) : (0)))

/****************************************************************/
/*  Global variable                                             */
/****************************************************************/
uint8 u8ButtonState;
uint8 u8LedState;
volatile uint32 g_systick = 0;
/****************************************************************/
/*  Internal function                                           */
/****************************************************************/

void BIT_MASK_REVISION(unsigned int *address, unsigned char position, unsigned char level)
{
	if (level == 1)
	{
		*(address) |= (level << position);
	}
	else if (level == 0)
	{
		*(address) &= ~(level << position);
	}
}

/****************************************************************/
/*  MAIN FUNCTION	                                            */
/****************************************************************/
int main(void)
{
	/*****************************************************************************
	PRACTICE 1: BIT MASK REVISION
	*****************************************************************************/
	// uint8 u8BitState = 1;

	// /* Enable clock at PORTD */
	// PCC->PORT[PORTD_INDEX] |= PCC_CGC_MASK;

	// /* Set pin D0 as OUTPUT */
	// PORT_Pin_Output_Config(PORTD, GPIOD, 0);
	// BIT_MASK_REVISION((uint32 *)(GPIOD_BASE + 0X14), 0, 1);

	// while (1)
	// {
	// 	/* check level at pin D0 */
	// 	u8BitState = GPIOD->PDOR & (1 << 0);

	// 	if (u8BitState)
	// 	{
	// 		/* Set pin D0 */
	// 		BIT_MASK_REVISION((uint32 *)(GPIOD_BASE + 0X14), 0, 1);
	// 	}
	// 	else
	// 	{
	// 		/* Clear pin D0 */
	// 		BIT_MASK_REVISION((uint32 *)(GPIOD_BASE + 0X14), 0, 0);
	// 	}

	// 	Delay(2000);
	// }

	// return 0;
	/*****************************************************************************
	PRACTICE 3: USING SW3 TO ENABLE/DISABLE BLINK RED LED - PTD15
	*****************************************************************************/
	// uint8 u8ButtonState = 0;

	// /* Enable clock PORTC, PORTD */
	// PCC->PORT[PORTC_INDEX] |= PCC_CGC_MASK;
	// PCC->PORT[PORTD_INDEX] |= PCC_CGC_MASK;

	// /* Set MUX pin D15, C13 as GPIO */
	// PORTD->PCR[15] |= (2 << 8);
	// PORTC->PCR[13] |= (2 << 8);

	// /* Init pin D15 as OUTPUT */
	// GPIOD->PDDR |= PIN(15);

	// /* Init pin C13 as INPUT */
	// GPIOC->PDDR &= ~PIN(13);

	// while (1)
	// {
	// 	if (GPIOC->PDIR & PIN(13))
	// 	{
	// 		/* update led status*/
	// 		u8ButtonState++;
	// 		u8ButtonState %= 2;
	// 	}

	// 	if (u8ButtonState)
	// 	{
	// 		/* Set pin D15 */
	// 		Delay(500);
	// 		GPIOD->PDOR |= PIN(15);
	// 		/* Clear pin D15 */
	// 		Delay(500);
	// 		GPIOD->PDOR &= ~PIN(15);
	// 	}
	// }

	// return 0;
	/*****************************************************************************
	PRACTICE 4: USING SW2 and SW3 TO ENABLE/DISABLE BLINK RGB LED
	*****************************************************************************/
	u8ButtonState = 1;
	u8LedState = 0;
	g_systick = 0;

	/* Enable clock PORTC, PORTD */
	PCC->PORT[PORTC_INDEX] |= PCC_CGC_MASK;
	PCC->PORT[PORTD_INDEX] |= PCC_CGC_MASK;

	/* Set pin C13, C12 as INPUT */
	PORT_Pin_Input_IT_Config(PORTC, GPIOC, 12, IRQC_RE);
	PORT_Pin_Input_IT_Config(PORTC, GPIOC, 13, IRQC_RE);

	/* Set pin D0,D15,D16 as OUTPUT */
	PORT_Pin_Output_Config(PORTD, GPIOD, 0);
	PORT_Pin_Output_Config(PORTD, GPIOD, 15);
	PORT_Pin_Output_Config(PORTD, GPIOD, 16);

	/* Config NVIC for PORTC */
	Interrupt_Enable(61, 0);

	/* Config SysTick */
	SysTick_Init_IT(10);

	/* Set */

	while (1)
	{
		if (u8ButtonState == 1 && g_systick >= 10)
		{
			GPIO_WriteToOutputPort(GPIOD, (uint32)~0);
			GPIO_WriteToOutputPin(GPIOD, (uint8)SWITCH_LED1(u8LedState), GPIO_PIN_RESET);
			u8LedState++;
			u8LedState %= 3;
			Delay_ms(1000);
			g_systick = 0;
		}
	}

	return 0;
}

void PORTC_IRQHandler(void)
{
	if (PORTC->PCR[12] & (1 << 24))
	{
		/* clear pending flag */
		PORTC->PCR[12] |= PORT_PCR_ISF_MASK;
		u8ButtonState = 1;
	}
	else if (PORTC->PCR[13] & (1 << 24))
	{
		/* clear pending flag */
		PORTC->PCR[13] |= PORT_PCR_ISF_MASK;
		u8ButtonState = 0;
	}
}

void SysTick_Handler(void)
{
	g_systick++;
}