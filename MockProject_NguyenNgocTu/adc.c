/******************************************************************************
 * Project Name: ADC DRIVER
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
/**
 *   @brief      This function enable global clock, and configure functional clock to ADC module.
 *
 *   @param[in]  ADC_HandleType* pADCHandler            Pointer to ADC handler
 *
 *   @return     void                                   xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void ADC_PeripheralClockConfig(ADC_HandleType *pADCHandler)
{
    /* Enable global clock to ADC 0 */
    if (pADCHandler->pADCx == ADC0)
    {
        PCC->PCC_ADC0 |= (pADCHandler->ADC_Config->ClockSource << PCC_PCS_SHIFT);
        PCC->PCC_ADC0 |= (1 << PCC_CGC_SHIFT);
    }
    /* Enable global clock to ADC 1 */
    else if (pADCHandler->pADCx == ADC1)
    {
        PCC->PCC_ADC1 |= (pADCHandler->ADC_Config->ClockSource << PCC_PCS_SHIFT);
        PCC->PCC_ADC1 |= (1 << PCC_CGC_SHIFT);
    }
}

/**
 *   @brief      This function function configure Clocksource, resolution, sampling time, mode of all ADC channels.
 *
 *   @param[in]  ADC_HandleType* pADCHandler            Pointer to ADC handler
 *
 *   @return     void                                   xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void ADC_Init(ADC_HandleType *pADCHandler)
{
    uint32 temp = 0U;
    uint8 i;
    uint8 NumOfChannel = pADCHandler->ADC_Config->NumOfChannel;

    /* Disable for all channels */
    for (i = 0; i < NumOfChannel; i++)
    {
        pADCHandler->pADCx->SC1[0] |= ADC_SC1_ADCH_MASK;
    }

    /* Configure ADC Clock */
    temp |= (pADCHandler->ADC_Config->ClockDivider << ADC_CFG1_ADIV_SHIFT);

    /* Select Conversion resolution */
    temp |= (pADCHandler->ADC_Config->Resolution << ADC_CFG1_MODE_SHIFT);
    pADCHandler->pADCx->CFG1 = temp;
    temp = 0U;

    /* Select Conversion sampling time */
    temp |= (pADCHandler->ADC_Config->SamplingRatio << ADC_CFG2_SMPLTS_SHIFT);
    pADCHandler->pADCx->CFG2 = temp;
    temp = 0U;

    /* Select Conversion Mode */
    temp |= (pADCHandler->ADC_Config->TriggerSource << ADC_SC2_ADTRG_SHIFT);
    temp |= (pADCHandler->ADC_Config->ReferSource << ADC_SC2_REFSEL_SHIFT);
    pADCHandler->pADCx->SC2 = temp;
    temp = 0;

    if (pADCHandler->ADC_Config->ADCMode == ADC_MODE_CONTINUOUS)
    {
        temp |= (pADCHandler->ADC_Config->ADCMode << ADC_SC3_ADCO_SHIFT);
        pADCHandler->pADCx->SC3 = temp;
        temp = 0U;
    }
}

/**
 *   @brief      This function start a one-shot conversion for all channels.
 *
 *   @param[in]  ADC_HandleType* pADCHandler            Pointer to ADC handler
 *
 *   @return     void                                   xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void ADC_StartConversion(ADC_HandleType *pADCHandler)
{
    uint8 i;
    uint8 NumOfChannel = pADCHandler->ADC_Config->NumOfChannel;
    uint32 temp = 0U;

    /* Loop for all channels */
    for (i = 0; i < NumOfChannel; i++)
    {
        /* Interrupt control */
        temp |= (pADCHandler->ADC_Config->InterruptControl << ADC_SC1_AIEN_SHIFT);

        /* Select conversion input channel control */
        temp |= (pADCHandler->ADC_Config->InputChannel[i] << ADC_SC1_ADCH_SHIFT);
        pADCHandler->pADCx->SC1[i] &= ~ADC_SC1_ADCH_MASK;
        pADCHandler->pADCx->SC1[i] = temp;
        temp = 0U;
    }
}

/**
 *   @brief      This function returns conversion value of a specific channel.
 *
 *   @param[in]  ADC_HandleType* pADCHandler            Pointer to ADC handler
 *   @param[in]  uint8 Channel                          Channel ID
 *
 *   @return     void                                   xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
uint16 ADC_ReadConversion(ADC_HandleType *pADCHandler, uint8 Channel)
{
    uint16 temp = 0U;
    temp = (uint16)pADCHandler->pADCx->R[Channel];
    return temp;
}

/**
 *   @brief      This function gets status of conversion channel.
 *
 *   @param[in]  ADC_HandleType* pADCHandler            Pointer to ADC handler
 *   @param[in]  uint8 Channel                          Channel ID
 *
 *   @return     void                                   xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
uint8 ADC_GetStatus(ADC_HandleType *pADCHandler, uint8 Channel)
{
    uint8 status = 0U;
    status = (uint8)((pADCHandler->pADCx->SC1[Channel] >> ADC_SC1_COCO_SHIFT) & (uint32)0X01);
    return status;
}

/*---------------------- End of File ----------------------------------------*/
