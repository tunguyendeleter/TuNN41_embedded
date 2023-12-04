#ifndef DRIVERS_INC_GPIO_H_
#define DRIVERS_INC_GPIO_H_

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "stm32f411xx.h"


/******************************************************************************
*   VERSION CHECK
 *****************************************************************************/


/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/**
* @GPIO_PIN_MODE
* @brief  GPIO pin modes
*/
#define GPIO_MODE_IN				0
#define GPIO_MODE_OUT				1
#define GPIO_MODE_ALT				2
#define GPIO_MODE_ANALOG			3
#define GPIO_MODE_IT_FE				4
#define GPIO_MODE_IT_RE   			5
#define GPIO_MODE_IT_EE				6

/**
* @GPIO_PIN_OP_MODE
* @brief  GPIO pin output types
*/
#define GPIO_OP_TYPE_PP				0
#define GPIO_OP_TYPE_OD				1

/**
* @GPIO_SPEED_MODE
* @brief  GPIO pin output speed modes
*/
#define GPIO_SPEED_LOW				0
#define GPIO_SPEED_MEDIUM			1
#define GPIO_SPEED_FAST				2
#define GPIO_SPEED_HIGH				3

/**
* @GPIO_PUPD_MODE
* @brief  GPIO pin pullup and pulldown
*/
#define GPIO_NO_PUPD				0
#define GPIO_PIN_PU					1
#define GPIO_PIN_PD					2

/**
* @brief  GPIO pin number
*/
#define GPIO_PIN_NUM(x)				x


/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/
/**
* @brief  structure of GPIO config mode
*/
typedef struct{
	uint8 GPIO_PinNumber;			/*pin number*/
	uint8 GPIO_PinMode;				/*pin mode 							@GPIO_PIN_MODE*/
	uint8 GPIO_PinSpeed;			/*pin speed 						@GPIO_SPEED_MODE*/
	uint8 GPIO_PinPuPdControl;		/*pin pull-up pull-down control 	@GPIO_PUPD_MODE*/
	uint8 GPIO_PinOPType;			/*pin output type					@GPIO_PIN_OP_MODE*/
	uint8 GPIO_PinAltFunMode;		/*pin alternate function mode*/
}GPIO_Config_Type;

/**
* @brief  structure of GPIO config registers
*/
typedef struct{
	GPIO_Type *pGPIOx;					/*This is a pointer to hold address of GPIO port to which the pins belong*/
	GPIO_Config_Type GPIO_PinConfig;	/*This holds GPIO pin configuation settings*/
}GPIO_Handle_t;



/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/
/**
* @brief  this function setup GPIO clock
*/
extern void GPIO_PeriClockControl(GPIO_Type *pGPIOx, uint8 EnorDis);

/**
* @brief  this function initialize and deinitialize GPIO
*/
extern void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
extern void GPIO_DeInit(GPIO_Type *pGPIOx);

/**
* @brief  this function read and write data at GPIO
*/
extern uint8 GPIO_ReadFromInputPin(GPIO_Type *pGPIOx, uint8 PinNumber);
extern uint16 GPIO_ReadFromInputPort(GPIO_Type *pGPIOx);
extern void GPIO_WriteToOutputPin(GPIO_Type *pGPIOx, uint8 PinNumber, uint8 Value);
extern void GPIO_WriteToOutputPort(GPIO_Type *pGPIOx, uint16 Value);
extern void GPIO_ToggleOutputPin(GPIO_Type *pGPIOx, uint8 PinNumber);

/**
* @brief  this function setup interrupt for GPIO
*/
extern void GPIO_IRQConfig(uint8 IRQNumber, uint8 IRQPriority, uint8 EnorDis);
extern void GPIO_IRQHandling(void);





#endif /* DRIVERS_INC_GPIO_H_ */
