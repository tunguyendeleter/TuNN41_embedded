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
#include "Common_S32K144.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/

/**
* @brief    Define PORT bit fields masks
*/
#define PORT_PCR_ISF_MASK       0X01000000U       /* Interrupt flag MASK */
#define PORT_PCR_IQRC_MASK      0X000F0000U       /* Interrupt configuration MASK */
#define PORT_PCR_MUX_MASK       0X00000700U       /* MUX select MASK */
#define PORT_PCR_DSE_MASK       0X00000040U       /* Drive strength enable MASK */
#define PORT_PCR_PFE_MASK       0X00000010U       /* Passive filter enable (external button) MASK */
#define PORT_PCR_PE_MASK        0X00000002U       /* Pull enable MASK */
#define PORT_PCR_PS_MASK        0X00000001U       /* Pullup Pulldown select MASK */

/**
* @brief    Define PORT bit fields shift
*/
#define PORT_PCR_ISF_SHIFT      24U                /* Interrupt flag SHIFT */
#define PORT_PCR_IQRC_SHIFT     16U                /* Interrupt configuration SHIFT */
#define PORT_PCR_MUX_SHIFT      8U                 /* MUX select SHIFT */
#define PORT_PCR_DSE_SHIFT      6U                 /* Drive strength enable SHIFT */
#define PORT_PCR_PFE_SHIFT      4U                 /* Passive filter enable (external button) SHIFT */
#define PORT_PCR_PE_SHIFT       1U                 /* Pull enable SHIFT */
#define PORT_PCR_PS_SHIFT       0U                 /* Pullup Pulldown select SHIFT */

/**
* @brief    Define PORT bit fields shift
*/
#define IRQC_LOW                8U                /* ISF flag and Interrupt when logic 0 */
#define IRQC_HIGH               12U               /* ISF flag and Interrupt when logic 1 */
#define IRQC_RE                 9U                /* ISF flag and Interrupt on rising-edge */
#define IRQC_FE                 10U               /* ISF flag and Interrupt on falling-edge */
#define IRQC_EE                 11U               /* ISF flag and Interrupt on either edge */

/**
* @brief    Define PORT alternate function macro
*/
#define ALT_FUNC(x)				(x)

/**
* @brief    Define PORT alternate function macro
*/
#define ALT_FUNC(x)				(x)
/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPE
 *****************************************************************************/
/**
* @brief  This function enable global clock to PORT module
*/
extern void PORT_PeripheralClockConfig(PORT_TypeDef *pPORTx);

/**
* @brief  This function config GPIO pin as OUTPUT
*/
extern void PORT_Pin_Output_Config(PORT_TypeDef *pPORTx, GPIO_TypeDef *pGPIOx, uint32 PinNumber);

/**
* @brief  This function config GPIO pin as INPUT
*/
extern void PORT_Pin_Input_Config(PORT_TypeDef *pPORTx, GPIO_TypeDef *pGPIOx, uint32 PinNumber, uint8 PullUpDown);

/**
* @brief  This function config GPIO pin as Interrupt INPUT
*/
extern void PORT_Pin_Input_IT_Config(PORT_TypeDef *pPORTx, GPIO_TypeDef *pGPIOx, uint32 PinNumber, uint32 IQRCMode, uint8 PullUpDown);

/**
* @brief  This function configure specific MUX pin
*/
extern void PORT_Pin_Alt_Config(PORT_TypeDef *pPORTx, uint8 PinNumber, uint8 Alternate);

/**
* @brief  This function read data at GPIO pin
*/
extern uint8 GPIO_ReadFromInputPin(GPIO_TypeDef *pGPIOx, uint8 PinNumber);

/**
* @brief  This function read data at GPIO port
*/
extern uint32 GPIO_ReadFromInputPort(GPIO_TypeDef *pGPIOx);

/**
* @brief  This function write data at GPIO pin
*/
extern void GPIO_WriteToOutputPin(GPIO_TypeDef *pGPIOx, uint8 PinNumber, uint8 Value);

/**
* @brief  This function write data at GPIO port
*/
extern void GPIO_WriteToOutputPort(GPIO_TypeDef *pGPIOx, uint32 Value);

/**
* @brief  This function toggle data at GPIO pin
*/
extern void GPIO_ToggleOutputPin(GPIO_TypeDef *pGPIOx, uint8 PinNumber);

#endif /* DRIVERS_INC_GPIO_H_ */
