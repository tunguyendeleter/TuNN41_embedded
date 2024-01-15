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
/**
 * @brief    Define macros for ADC Status and Control Register 1 
 */
#define ADC_SC1_ADCH_SHIFT                       0U
#define ADC_SC1_ADCH_MASK                        0X3FU
#define ADC_SC1_AIEN_SHIFT                       6U
#define ADC_SC1_COCO_SHIFT                       7U

/**
 * @brief    Define macros for ADC Configuration Register 1 
 */
#define ADC_CFG1_ADICLK_SHIFT                    0U
#define ADC_CFG1_MODE_SHIFT                      2U
#define ADC_CFG1_ADIV_SHIFT                      5U
#define ADC_CFG1_CLRLTRG_SHIFT                   8U

/**
 * @brief    Define macros for ADC Configuration Register 2 
 */
#define ADC_CFG2_SMPLTS_SHIFT                    0U
#define ADC_CFG2_SMPLTS(x)                       ((uint16)(x))

/**
 * @brief    Define macros for ADC Data Result Registers   
 */
#define ADC_R_D_SHIFT                            0U

/**
 * @brief    Define macros for Compare Value Registers  
 */
#define ADC_CV_CV_SHIFT                          0U

/**
 * @brief    Define macros for Status and Control Register 2  
 */
#define ADC_SC2_REFSEL_SHIFT                     0U
#define ADC_SC2_DMAEN_SHIFT                      2U
#define ADC_SC2_ACREN_SHIFT                      3U
#define ADC_SC2_ACFGT_SHIFT                      4U
#define ADC_SC2_ADTRG_SHIFT                      6U
#define ADC_SC2_ADACT_SHIFT                      7U
#define ADC_SC2_TRGPRNUM_SHIFT                   13U
#define ADC_SC2_TRGSTLAT_SHIFT                   16U
#define ADC_SC2_TRGSTERR_SHIFT                   24U

/**
 * @brief    Define macros for Status and Control Register 3
 */
#define ADC_SC3_AVGS_SHIFT                       0U
#define ADC_SC3_AVGE_SHIFT                       2U
#define ADC_SC3_ADCO_SHIFT                       3U
#define ADC_SC3_CAL_SHIFT                        7U

/**
 * @brief    Define macros for BASE Offset Register  
 */
#define ADC_BASE_OFS_BA_OFS_SHIFT                0U

/**
 * @brief    Define macros for ADC Offset Correction Register   
 */
#define ADC_OFS_OFS_SHIFT                        0U

/**
 * @brief    Define macros for USER Offset Correction Register  
 */
#define ADC_USR_OFS_USR_OFS_SHIFT                0U

/**
 * @brief    Define macros for ADC X Offset Correction Register   
 */
#define ADC_XOFS_XOFS_SHIFT                      0U

/**
 * @brief    Define macros for ADC Y Offset Correction Register   
 */
#define ADC_YOFS_YOFS_SHIFT                      0U

/**
 * @brief    Define macros for ADC Gain Register    
 */
#define ADC_G_G_SHIFT                            0U

/**
 * @brief    Define macros for ADC User Gain Register   
 */
#define ADC_UG_UG_SHIFT                          0U

/**
 * @brief    Define macros for ADC General Calibration Value Register S 
 */
#define ADC_CLPS_CLPS_SHIFT                      0U

/**
 * @brief    Define macros for ADC Plus-Side General Calibration Value Register 3 
 */
#define ADC_CLP3_CLP3_SHIFT                      0U

/**
 * @brief    Define macros for ADC Plus-Side General Calibration Value Register 2
 */
#define ADC_CLP2_CLP2_SHIFT                      0U

/**
 * @brief    Define macros for ADC Plus-Side General Calibration Value Register 1  
 */
#define ADC_CLP1_CLP1_SHIFT                      0U

/**
 * @brief    Define macros for ADC Plus-Side General Calibration Value Register 0 
 */
#define ADC_CLP0_CLP0_SHIFT                      0U

/**
 * @brief    Define macros for ADC Plus-Side General Calibration Value Register X  
 */
#define ADC_CLPX_CLPX_SHIFT                      0U

/**
 * @brief    Define macros for ADC Plus-Side General Calibration Value Register 9
 */
#define ADC_CLP9_CLP9_SHIFT                      0U

/**
 * @brief    Define macros for ADC General Calibration Offset Value Register S 
 */
#define ADC_CLPS_OFS_CLPS_OFS_SHIFT              0U

/**
 * @brief    Define macros for ADC Plus-Side General Calibration Offset Value Register 3
 */
#define ADC_CLP3_OFS_CLP3_OFS_SHIFT              0U

/**
 * @brief    Define macros for ADC Plus-Side General Calibration Offset Value Register 2
 */
#define ADC_CLP2_OFS_CLP2_OFS_SHIFT              0U

/**
 * @brief    Define macros for ADC Plus-Side General Calibration Offset Value Register 1
 */
#define ADC_CLP1_OFS_CLP1_OFS_SHIFT              0U

/**
 * @brief    Define macros for ADC Plus-Side General Calibration Offset Value Register 0
 */
#define ADC_CLP0_OFS_CLP0_OFS_SHIFT              0U

/**
 * @brief    Define macros for ADC Plus-Side General Calibration Offset Value Register X 
 */
#define ADC_CLPX_OFS_CLPX_OFS_SHIFT              0U

/**
 * @brief    Define macros for ADC Plus-Side General Calibration Offset Value Register 9
 */
#define ADC_CLP9_OFS_CLP9_OFS_SHIFT              0U

/**
 * @brief    Define macros for ADC Operation mode: continue/one-shot
 * @ADCADCMode
 */
#define ADC_MODE_ONESHOT                         0U
#define ADC_MODE_CONTINUOUS                      1U

/**
 * @brief    Define macros for Resolution of ADC conversion output
 * @ADCResolution
 */
#define ADC_8BIT_CONVERSION                      0U
#define ADC_12BIT_CONVERSION                     1U
#define ADC_10BIT_CONVERSION                     2U

/**
 * @brief    Define macros for ADC Clock divider
 * @ADCClockDivider
 */
#define ADC_CLKDIV_BY1                           0U
#define ADC_CLKDIV_BY2                           1U
#define ADC_CLKDIV_BY4                           2U
#define ADC_CLKDIV_BY8                           3U

/**
 * @brief    Define macros for ADC Reference voltage source
 * @ADCReferSource
 */
#define ADC_DEFAULT_REF                          0U
#define ADC_ALTERNATE_REF                        1U

/**
 * @brief    Define macros for ADC Peripheral Clock Source
 * @ADCClockSource
 */
#define ADC_SOSCDIV2_CLK                         1U
#define ADC_SIRCDIV2_CLK                         2U
#define ADC_FIRCDIV2_CLK                         3U
#define ADC_SPLLDIV2_CLK                         6U

/**
 * @brief    Define macros for ADC Hardware trigger or Software trigger
 * @ADCTriggerSource
 */
#define ADC_SOFTWARE_TRIG                        0U
#define ADC_HARDWARE_TRIG                        1U

/**
 * @brief    Define macros for interrupt control
 * @ADCInterruptControl
 */
#define ADC_INTERRUPT_ENABLE                     1U
#define ADC_INTERRUPT_DISABLE                    0U

/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/
typedef struct 
{
    /* Configure ADC Clock */
    uint8 ClockSource;                              /* @ADCClockSource: Peripheral Clock Source to ADC module */
    uint32 ClockDivider;                            /* @ADCClockDivider: Clock divider */
    /* Configures ADC resolution and sampling */
    uint8 Resolution;                               /* @ADCResolution: Resolution of ADC conversion output */
    uint8 SamplingRatio;                            /* Speed of ADC conversion: number of cycles */
    /* Configures mode */
    uint8 ADCMode;                                  /* @ADCADCMode: Operation mode: continue/one-shot */
    uint8 ReferSource;                              /* @ADCReferSource: Reference voltage source */
    uint8 TriggerSource;                            /* @ADCTriggerSource: Hardware trigger or Software trigger */
    uint8 InterruptControl;                         /* @ADCInterruptControl: Interrupt enable */
    /* Conversion channel input */
    uint8 InputChannel[16];                         /* Conversion input channel: 63 internal and external input channels */
    /* Conversion channel */
    uint8 NumOfChannel;                             /* Number of Conversion channel: SCA - SCP */
} ADC_ConfigType;

typedef struct 
{
    /* Pointer to ADCx module */
    ADC_TypeDef *pADCx;

    /* ADC configuration */
    ADC_ConfigType *ADC_Config;
} ADC_HandleType;

/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *****************************************************************************/
/**
* @brief  This function enable global clock, and configure functional clock to ADC module
*/
extern void ADC_PeripheralClockConfig(ADC_HandleType *pADCHandler);

/**
* @brief  This function function configure Clocksource, resolution, sampling time, mode of all ADC channels
*/
extern void ADC_Init(ADC_HandleType *pADCHandler);

/**
* @brief  This function start a one-shot conversion for all channels
*/
extern void ADC_StartConversion(ADC_HandleType *pADCHandler);

/**
* @brief  This function returns conversion value of a specific channel
*/
extern uint16 ADC_ReadConversion(ADC_HandleType *pADCHandler, uint8 Channel);

/**
* @brief  This function gets status of conversion channel
*/
extern uint8 ADC_GetStatus(ADC_HandleType *pADCHandler, uint8 Channel);

#endif /* DRIVERS_INC_ADC_H_ */

/*---------------------- End of File ----------------------------------------*/
