#include "nvic.h"
#include "stm32f411xx.h"


void NVIC_IRQConfig(uint8 IRQNumber, uint8 IRQPriority, uint8 EnorDis)
{
	if(EnorDis == ENABLE)
	{
		/*setup ISER register*/
		NVIC->ICPR[IRQNumber/32] |= (1 << (IRQNumber % 32));
		NVIC->ISER[IRQNumber/32] |= (1 << (IRQNumber % 32));
		/*setup IP register*/
		NVIC->IP[IRQNumber] = (IRQPriority);
	}
	else if(EnorDis == DISABLE)
	{
		/*setup ICER register*/
		NVIC->ICER[IRQNumber/32] |= (1 << (IRQNumber % 32));
	}

}
