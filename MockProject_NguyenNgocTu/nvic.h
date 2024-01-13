/******************************************************************************
 * Project Name: NVIC DRIVER
 * File Name:   nvic.h
 *
 * Description: Implementation of the NVIC
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex-M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/
#ifndef DRIVERS_INC_NVIC_H_
#define DRIVERS_INC_NVIC_H_

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "S32K144xx.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/


/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPE
 *****************************************************************************/
/**
* @brief  This function configures interrupt IRQ and priority for modules
*/
extern void Interrupt_Enable(uint32 IRQNumber, uint32 Priority);


#endif /* DRIVERS_INC_NVIC_H_ */