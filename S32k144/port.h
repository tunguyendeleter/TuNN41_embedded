/******************************************************************************
 * Project Name: PORT DRIVER
 * File Name:   port.h
 *
 * Description: Implementation of the PORT DRIVER
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex-M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/
#ifndef DRIVERS_INC_GPIO_H_
#define DRIVERS_INC_GPIO_H_

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "S32K144xx.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/**
* @brief    Define function-like macro
*/
#define BIT_MASK_REVISION(address, position, level)     ((level == 0) ? (*((uint32*)address) |= (level<<position)) : (*((uint32*)address) &= ~(level<<position)))

#define TOGGLE_BIT(address, position)                   ((*((uint32*)address) & (1 << position)) ? (*((uint32*)address) &= ~(1 << position)) : (*((uint32*)address) |= (1 << position)))

#define READ_BIT(address, position)                     (*((uint32*)address) |= (1 << position))


/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPE
 *****************************************************************************/
/**
* @brief  this function config GPIO pin as OUTPUT
*/
extern void PORT_Pin_Output_Config(PORT_TypeDef *pPORTx, GPIO_TypeDef *pGPIOx, uint32 PinNumber);

/**
* @brief  this function config GPIO pin as INPUT
*/
extern void PORT_Pin_Input_Config(PORT_TypeDef *pPORTx, GPIO_TypeDef *pGPIOx, uint32 PinNumber, uint8 PullUpDown);

/**
* @brief  this function config GPIO pin as Interrupt INPUT
*/
extern void PORT_Pin_Input_IT_Config(PORT_TypeDef *pPORTx, GPIO_TypeDef *pGPIOx, uint32 PinNumber, uint32 IQRCMode, uint8 PullUpDown);

/**
* @brief  this function read data at GPIO pin
*/
extern uint8 GPIO_ReadFromInputPin(GPIO_TypeDef *pGPIOx, uint8 PinNumber);

/**
* @brief  this function read data at GPIO port
*/
extern uint32 GPIO_ReadFromInputPort(GPIO_TypeDef *pGPIOx);

/**
* @brief  this function write data at GPIO pin
*/
extern void GPIO_WriteToOutputPin(GPIO_TypeDef *pGPIOx, uint8 PinNumber, uint8 Value);

/**
* @brief  this function write data at GPIO port
*/
extern void GPIO_WriteToOutputPort(GPIO_TypeDef *pGPIOx, uint32 Value);

/**
* @brief  this function toggle data at GPIO pin
*/
extern void GPIO_ToggleOutputPin(GPIO_TypeDef *pGPIOx, uint8 PinNumber);

#endif /* DRIVERS_INC_GPIO_H_ */