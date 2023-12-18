#ifndef RCC_H_
#define RCC_H_

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "stm32f411xx.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/


/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/


/******************************************************************************
 *  GLOBAL VARIABLES
 *****************************************************************************/


/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/
uint32 RCC_GetPLLValue(void);
uint32 RCC_GetPCLK1Value(void);
uint32 RCC_GetPCLK2Value(void);

#endif /* RCC_H_ */
