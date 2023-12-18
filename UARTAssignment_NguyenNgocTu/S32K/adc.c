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

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "adc.h"

/******************************************************************************
 *   VERSION CHECK
 *****************************************************************************/

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/

/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *****************************************************************************/
void ADC_PeripheralClockConfig(uint8 ClockSource)
{
    PCC->PCC_ADC0 |= (1 << PCC_PCS_SHIFT);
    PCC->PCC_ADC0 |= (ClockSource << PCC_CGC_SHIFT);
}

void ADC_Init(ADC_TypeDef *pADCx)
{
    uint32 temp = 0U;

    /* Select CLock Source */
    temp &= ~(3 << 0);

    /* Select CLock Prescaler */
    temp |= (0 << 5);

    /* Select Conversion resolution = 12bit */
    temp |= (1 << 2);

    pADCx->CFG1 = temp;
    temp = 0;

    /* Configure Sampling time = 13 */
    temp |= (12 << 0);

    pADCx->CFG2 = temp;
    temp = 0;

    /* Select trigger mode */
    temp |= (0 << 6);

    pADCx->SC2 = temp;
    temp = 0;

    /* Select Conversion Mode */
    temp |= (1 << 3);

    pADCx->SC3 = temp;
    temp = 0;

    /* Configure channel */
    temp |= (12 << 0);

    pADCx->SC1[0] = temp;
}

uint8 ADC_ConversionComplete(ADC_TypeDef *pADCx)
{
    return ((pADCx->SC1[0] & (uint32)(1 << 7)) >> 7);
}

/*---------------------- End of File ----------------------------------------*/
