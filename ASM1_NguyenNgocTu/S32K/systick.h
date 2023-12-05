/******************************************************************************
 * Project Name: SYSTICK DRIVER
 * File Name:   systick.h
 *
 * Description: Implementation of the SYSTICK TIMER
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex-M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/
#ifndef DRIVERS_INC_SYSTICK_H_
#define DRIVERS_INC_SYSTICK_H_

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
* @brief  This function configures SysTick timer modules
*/
extern void SysTick_Init(uint32 CountValue);

/**
* @brief  This function enables SysTick timer to start 
*/
extern void SysTick_StartTimer(void);

/**
* @brief  This function disables SysTick timer 
*/
extern void SysTick_StopTimer(void);


#endif /* DRIVERS_INC_SYSTICK_H_ */