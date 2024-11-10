#ifndef SYSTICK_H_
#define SYSTICK_H_

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "stm32f411xx.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/**
* @brief  Define SysTick Control and Status Register bit macros
*/
#define SYSTICK_CSR_ENABLE_SHIFT                            0U   
#define SYSTICK_CSR_TICKINT_SHIFT                           1U   
#define SYSTICK_CSR_CLKSOURCE_SHIFT                         2U   
#define SYSTICK_CSR_COUNTFLAG_SHIFT                         16U        
             
/**
* @brief  Define SysTick Current Value Register bit macros
*/
#define SYSTICK_CVR_CURRENT_MASK                            0XFFFFFFU   
             
/**
* @brief  Define Clock source avaiable for STM32 
*/
#define SYSTICK_CSR_CLKSOURCE_EXTERNAL                      0U   
#define SYSTICK_CSR_CLKSOURCE_COREBUS                       1U   

/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/


/******************************************************************************
 *  GLOBAL VARIABLES
 *****************************************************************************/


/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/
/**
* @brief  this function enable or disable NVIC interrupt with IRQNumber, and IRQPriority
*/
extern void SysTick_Init(uint32 CountValue, uint8 ClockSource);

/**
* @brief  This function enables SysTick timer to start
*/
extern void SysTick_StartTimer(void);

/**
* @brief  This function disables SysTick timer
*/
extern void SysTick_StopTimer(void);

#endif /* SYSTICK_H_ */
