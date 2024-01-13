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
#include "S32K144xx.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/**
 * @brief    Define LPIT MCR Module Enable
 */
#define LPIT_MCR_M_CEN_MASK                         0X1U
#define LPIT_MCR_M_CEN_SHIFT                        0U
#define LPIT_MCR_M_CEN_WIDTH                        1U

/**
 * @brief    Define LPIT MCR Debug Run Enable
 */
#define LPIT_MCR_DBG_EN_MASK                        0X8U
#define LPIT_MCR_DBG_EN_SHIFT                       3U
#define LPIT_MCR_DBG_EN_WIDTH                       1U

/**
 * @brief    Define LPIT MIER 0 Interrupt Enable
 */
#define LPIT_MIER_TIE0_MASK                         0X1U
#define LPIT_MIER_TIE0_SHIFT                        0U
#define LPIT_MIER_TIE0_WIDTH                        1U

/**
 * @brief    Define LPIT MIER 1 Interrupt Enable 
 */
#define LPIT_MIER_TIE1_MASK                         0X2U
#define LPIT_MIER_TIE1_SHIFT                        1U
#define LPIT_MIER_TIE1_WIDTH                        1U

/**
 * @brief    Define LPIT MIER 2 Interrupt Enable
 */
#define LPIT_MIER_TIE2_MASK                         0X4U
#define LPIT_MIER_TIE2_SHIFT                        2U
#define LPIT_MIER_TIE2_WIDTH                        1U

/**
 * @brief    Define LPIT MIER 3 Interrupt Enable
 */
#define LPIT_MIER_TIE3_MASK                         0X8U
#define LPIT_MIER_TIE3_SHIFT                        3U
#define LPIT_MIER_TIE3_WIDTH                        1U

/**
 * @brief    Define macros for LPIT channels
 * @ChannelOption 
 */
#define LPIT_CHANNEL0                               (uint8)(1 << 0)
#define LPIT_CHANNEL1                               (uint8)(1 << 1)
#define LPIT_CHANNEL2                               (uint8)(1 << 2)
#define LPIT_CHANNEL3                               (uint8)(1 << 3)

/**
 * @brief    Define macros for LPIT funational clock
 * @ClockOption 
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
 * @InterruptOption 
 */
#define LPIT_INTERRUPT_ENABLE                       1U  
#define LPIT_INTERRUPT_DISABLE                      0U  

/**
 * @brief    Define macros for Module Control Status 
 * @ControlOption 
 */
#define LPIT_DEBUG_STOP                             (uint8)(0 << 3)  
#define LPIT_DEBUG_RUN                              (uint8)(1 << 3)  
#define LPIT_DOZEN_STOP                             (uint8)(0 << 2)  
#define LPIT_DOZEN_RUN                              (uint8)(1 << 2)  
#define LPIT_MODULE_ENABLE                          (uint8)(1 << 0)  
#define LPIT_MODULE_DISABLE                         (uint8)(0 << 0)  


/**
 * @brief    Define macros for Module Control Status 
 * @ModeOption 
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
    uint8 ClockSource;                              /* @ClockOption: Peripheral Clock Source to LPIT module */
    uint32 ReloadValue[4];                          /* Reload value of channels */
    /* Timer mode operation */
    uint8 Status;                                   /* @ControlOption: Module Control Status: DBG_EN, DOZE_EN, SW_RST, M_CEN */
    uint8 OpMode;                                   /* @ModeOption: Timer Operation Mode */
    uint8 InterruptControl;                         /* @InterruptOption: Interrupt enable */
    /* Timer channels */
    uint8 Channel;                                  /* @ChannelOption: LPIT_CHANNELx */
} LPIT_ConfigType;

typedef struct 
{
    /* Pointer to LPITx module */
    LPIT_TypeDef *pLPITx;

    /* LPIT configuration */
    LPIT_ConfigType *LPIT_Config;
} LPIT_HandleType;

/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPE
 *****************************************************************************/
/**
* @brief  This function enable global clock, and configure functional clock to LPIT module
*/
extern void LPIT_PeripheralClockConfig(LPIT_HandleType *pLPIT_Handle);

/**
* @brief  This function configure reload value, timer channel, timer mode to LPIT module
*/
extern void LPIT_Init(LPIT_HandleType *pLPIT_Handle);

/**
* @brief  This function start timer on all configured channels of LPIT module
*/
extern void LPIT_StartTimer(LPIT_HandleType *pLPIT_Handle);

/**
* @brief  This function stop timer on all configured channels of LPIT module
*/
extern void LPIT_StopTimer(LPIT_HandleType *pLPIT_Handle);



#endif /* DRIVERS_INC_LPIT_H_ */
