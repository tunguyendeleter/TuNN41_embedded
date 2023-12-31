/******************************************************************************
 * Project Name: FRESHER  MCAL
 * File Name: adc.h
 *
 * Description: Implementation of the ADC
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex-M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/

#ifndef DRIVERS_INC_ADC_H_
#define DRIVERS_INC_ADC_H_

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "S32K144xx.h"

/******************************************************************************
 *   VERSION CHECK
 *****************************************************************************/

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/

/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *****************************************************************************/
extern void ADC_PeripheralClockConfig(uint8 ClockSource);

extern void ADC_Init(ADC_TypeDef *pADCx);

extern uint8 ADC_ConversionComplete(ADC_TypeDef *pADCx);

#endif /* DRIVERS_INC_ADC_H_ */

/*---------------------- End of File ----------------------------------------*/
