/******************************************************************************
 * Project Name: LPIT DRIVER
 * File Name:   lpit.h
 *
 * Description: Implementation of the LPIT
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex-M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/
#ifndef DRIVERS_INC_LPIT_H_
#define DRIVERS_INC_LPIT_H_

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "Common_S32K144.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/**
 * @brief    Define LPIT MCR Module Enable
 */
#define LPIT_MCR_M_CEN_MASK                         0x1u
#define LPIT_MCR_M_CEN_SHIFT                        0u
#define LPIT_MCR_M_CEN_WIDTH                        1u

/**
 * @brief    Define LPIT MCR Debug Run Enable
 */
#define LPIT_MCR_DBG_EN_MASK                        0x8u
#define LPIT_MCR_DBG_EN_SHIFT                       3u
#define LPIT_MCR_DBG_EN_WIDTH                       1u

/**
 * @brief    Define LPIT MIER 0 Interrupt Enable
 */
#define LPIT_MIER_TIE0_MASK                         0x1u
#define LPIT_MIER_TIE0_SHIFT                        0u
#define LPIT_MIER_TIE0_WIDTH                        1u

/**
 * @brief    Define LPIT MIER 1 Interrupt Enable 
 */
#define LPIT_MIER_TIE1_MASK                         0x2u
#define LPIT_MIER_TIE1_SHIFT                        1u
#define LPIT_MIER_TIE1_WIDTH                        1u

/**
 * @brief    Define LPIT MIER 2 Interrupt Enable
 */
#define LPIT_MIER_TIE2_MASK                         0x4u
#define LPIT_MIER_TIE2_SHIFT                        2u
#define LPIT_MIER_TIE2_WIDTH                        1u

/**
 * @brief    Define LPIT MIER 3 Interrupt Enable
 */
#define LPIT_MIER_TIE3_MASK                         0x8u
#define LPIT_MIER_TIE3_SHIFT                        3u
#define LPIT_MIER_TIE3_WIDTH                        1u

/**
 * @brief    Define macros for LPIT channels
 */
#define LPIT_CHANNEL0                               (uint8)(1 << 0)
#define LPIT_CHANNEL1                               (uint8)(1 << 1)
#define LPIT_CHANNEL2                               (uint8)(1 << 2)
#define LPIT_CHANNEL3                               (uint8)(1 << 3)

/**
 * @brief    Define macros for LPIT funational clock
 */
#define LPIT_SOSCDIV2_CLK                           1U  
#define LPIT_SIRCDIV2_CLK                           2U  
#define LPIT_FIRCDIV2_CLK                           3U  
#define LPIT_SPLLDIV2_CLK                           6U  
#define LPIT_LPO128_CLK                             7U

/**
 * @brief    Define macros for Timer Control Register
 */
#define LPIT_TCTRL_MODE_SHIFT                       2U  
#define LPIT_TCTRL_TEN_SHIFT                        0U  
#define LPIT_TCTRL_TSOT_SHIFT                       16U  
#define LPIT_TCTRL_TSOI_SHIFT                       17U  
#define LPIT_TCTRL_CHAIN_SHIFT                      1U  
#define LPIT_TCTRL_TROT_SHIFT                       18U  
#define LPIT_TCTRL_TRGSRC_SHIFT                     23U  
#define LPIT_TCTRL_TRCSEL_SHIFT                     24U  

/**
 * @brief    Define macros for interrupt control 
 */
#define LPIT_INTERRUPT_ENABLE                       1U  
#define LPIT_INTERRUPT_DISABLE                      0U  

/**
 * @brief    Define macros for Module Control Status 
 */
#define LPIT_DEBUG_STOP                             (uint8)(0 << 3)  
#define LPIT_DEBUG_RUN                              (uint8)(1 << 3)  
#define LPIT_DOZEN_STOP                             (uint8)(0 << 2)  
#define LPIT_DOZEN_RUN                              (uint8)(1 << 2)  
#define LPIT_MODULE_ENABLE                          (uint8)(1 << 0)  
#define LPIT_MODULE_DISABLE                         (uint8)(0 << 0)  


/**
 * @brief    Define macros for Module Control Status 
 */
#define LPIT_32BIT_PERIODIC_MODE                    0U  
#define LPIT_DUAL_16BIT_PERIODIC_MODE               1U  
#define LPIT_32BIT_TRIGGER_ACCUMULATOR_MODE         2U  
#define LPIT_32BIT_TRIGGER_INPUTCAPTURE_MODE        3U  

/**
* @brief  LPUART IRQ number
*/
#define LPIT_CH0_IRQ_ID                             48U
#define LPIT_CH1_IRQ_ID                             49U
#define LPIT_CH2_IRQ_ID                             50U
#define LPIT_CH3_IRQ_ID                             51U

/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/
typedef struct 
{
    /* Timer clock setting */
    uint8 ClockSource;
    uint32 ReloadValue[4];
    /* Timer mode operation */
    uint8 Status;
    uint8 OpMode;
    uint8 InterruptControl;
    /* Timer channels */
    uint8 Channel;
} LPIT_ConfigType;

typedef struct 
{
    /* Pointer to LPITx module */
    LPIT_TypeDef *pLPITx;

    /* LPIT configuration */
    LPIT_ConfigType LPIT_Config;
} LPIT_HandleType;

/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPE
 *****************************************************************************/
/**
* @brief  This function enable global clock to LPIT module
*/
extern void LPIT_PeripheralClockConfig(LPIT_HandleType *pLPIT_Handle);

/**
* @brief  This function configures LPIT module
*/
extern void LPIT_Init(LPIT_HandleType *pLPIT_Handle);

/**
* @brief  This function enable LPIT module
*/
extern void LPIT_StartTimer(LPIT_HandleType *pLPIT_Handle);

/**
* @brief  This function stop LPIT module
*/
extern void LPIT_StopTimer(LPIT_HandleType *pLPIT_Handle);



#endif /* DRIVERS_INC_LPIT_H_ */
