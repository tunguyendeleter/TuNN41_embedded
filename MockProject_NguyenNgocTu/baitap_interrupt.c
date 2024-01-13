/****************************************************************/
/**
 *  file        baitap_interrupt.h
 *  containts   Run application code
 */
/****************************************************************/

/****************************************************************/
/*  Includes section                                            */
/****************************************************************/
#include "port.h"
#include "nvic.h"

/****************************************************************/
/*  Define section                                              */
/****************************************************************/


/****************************************************************/
/*  Global variable                                             */
/****************************************************************/


/****************************************************************/
/*  Internal function                                           */
/****************************************************************/


/****************************************************************/
/*  MAIN FUNCTION	                                            */
/****************************************************************/
int main(void)
{
	/* Enable clock PORTC, PORTD */
	PCC->PORT[PORTC_INDEX] |= PCC_CGC_MASK;
	PCC->PORT[PORTD_INDEX] |= PCC_CGC_MASK;

	/* Set pin D0 as OUTPUT */
	PORT_Pin_Output_Config(PORTD, GPIOD, 15);

	/* Set pin C13 as INPUT */
	PORT_Pin_Input_IT_Config(PORTC, GPIOC, 12, IRQC_EE);
	
	/* Config NVIC for PORTC */
	Interrupt_Enable(61, 0);

	while (1)
	{
	}
	return 0;
}

void PORTC_IRQHandler(void)
{
	if (PORTC->PCR[12] & (1 << 24))
	{
		/* clear pending flag */
		PORTC->PCR[12] |= PORT_PCR_ISF_MASK;
		if (GPIO_ReadFromInputPin(GPIOC, 12))
		{
			GPIO_WriteToOutputPin(GPIOD, 15, GPIO_PIN_RESET);
		}
		else if (!GPIO_ReadFromInputPin(GPIOC, 12))
		{
			GPIO_WriteToOutputPin(GPIOD, 15, GPIO_PIN_SET);
		}
	}
}
