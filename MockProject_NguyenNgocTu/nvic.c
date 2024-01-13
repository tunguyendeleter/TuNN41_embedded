/******************************************************************************
 * Project Name: NVIC DRIVER
 * File Name: 	nvic.c
 *
 * Description: Implementation of the NVIC
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex-M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "nvic.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/


/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/
/**
 *   @brief      This function configures interrupt IRQ and priority for modules
 *
 *   @param[in]  uint32                 IRQNumber
 *   @param[in]  uint32                 Priority
 *
 *   @return     void                   xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void Interrupt_Enable(uint32 IRQNumber, uint32 Priority)
{
	/* Config NVIC IRQNumber */
	NVIC->ICPR[IRQNumber / 32] |= (1 << (IRQNumber % 32));
	NVIC->ISER[IRQNumber / 32] |= (1 << (IRQNumber % 32));
	/* Config NVIC Priority */
	NVIC->IP[IRQNumber] |= (Priority);
}   