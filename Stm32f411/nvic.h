#ifndef NVIC_H_
#define NVIC_H_

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "stm32f411xx.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/**
 * @brief  Define IRQNumber for peripherals
 */
#define IRQ_NO_EXTI0 						6
#define IRQ_NO_EXTI1 						7
#define IRQ_NO_EXTI2 						8
#define IRQ_NO_EXTI3 						9
#define IRQ_NO_EXTI4 						10
#define IRQ_NO_EXTI9_5 						23
#define IRQ_NO_EXTI15_10 					40


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
extern void NVIC_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDis);

#endif /* NVIC_H_ */
