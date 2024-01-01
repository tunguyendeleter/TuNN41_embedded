/******************************************************************************
 * Project Name: LPSPI DRIVER
 * File Name:   lpspi.h
 *
 * Description: Implementation of the LPSPI
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex-M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/
#ifndef DRIVERS_INC_LPSPI_H_
#define DRIVERS_INC_LPSPI_H_

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "S32K144xx.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/* VERID Bit Fields */
#define LPSPI_VERID_FEATURE_SHIFT                   0U
#define LPSPI_VERID_MINOR_SHIFT                     16U
#define LPSPI_VERID_MAJOR_SHIFT                     24U
/* PARAM Bit Fields */
#define LPSPI_PARAM_TXFIFO_SHIFT                    0U
#define LPSPI_PARAM_RXFIFO_SHIFT                    8U
/* CR Bit Fields */
#define LPSPI_CR_MEN_SHIFT                          0U
#define LPSPI_CR_RST_SHIFT                          1U
#define LPSPI_CR_DOZEN_SHIFT                        2U
#define LPSPI_CR_DBGEN_SHIFT                        3U
#define LPSPI_CR_RTF_SHIFT                          8U
#define LPSPI_CR_RRF_SHIFT                          9U
/* SR Bit Fields */
#define LPSPI_SR_TDF_SHIFT                          0U
#define LPSPI_SR_RDF_SHIFT                          1U
#define LPSPI_SR_WCF_SHIFT                          8U
#define LPSPI_SR_FCF_SHIFT                          9U
#define LPSPI_SR_TCF_SHIFT                          10U
#define LPSPI_SR_TEF_SHIFT                          11U
#define LPSPI_SR_REF_SHIFT                          12U
#define LPSPI_SR_DMF_SHIFT                          13U
#define LPSPI_SR_MBF_SHIFT                          24U
/* IER Bit Fields */
#define LPSPI_IER_TDIE_SHIFT                        0U
#define LPSPI_IER_RDIE_SHIFT                        1U
#define LPSPI_IER_WCIE_SHIFT                        8U
#define LPSPI_IER_FCIE_SHIFT                        9U
#define LPSPI_IER_TCIE_SHIFT                        10U
#define LPSPI_IER_TEIE_SHIFT                        11U
#define LPSPI_IER_REIE_SHIFT                        12U
#define LPSPI_IER_DMIE_SHIFT                        13U
/* DER Bit Fields */
#define LPSPI_DER_TDDE_SHIFT                        0U
#define LPSPI_DER_RDDE_SHIFT                        1U
/* CFGR0 Bit Fields */
#define LPSPI_CFGR0_HREN_SHIFT                      0U
#define LPSPI_CFGR0_HRPOL_SHIFT                     1U
#define LPSPI_CFGR0_HRSEL_SHIFT                     2U
#define LPSPI_CFGR0_CIRFIFO_SHIFT                   8U
#define LPSPI_CFGR0_RDMO_SHIFT                      9U
/* CFGR1 Bit Fields */
#define LPSPI_CFGR1_MASTER_SHIFT                    0U
#define LPSPI_CFGR1_SAMPLE_SHIFT                    1U
#define LPSPI_CFGR1_AUTOPCS_SHIFT                   2U
#define LPSPI_CFGR1_NOSTALL_SHIFT                   3U
#define LPSPI_CFGR1_PCSPOL_SHIFT                    8U
#define LPSPI_CFGR1_MATCFG_SHIFT                    16U
#define LPSPI_CFGR1_PINCFG_SHIFT                    24U
#define LPSPI_CFGR1_OUTCFG_SHIFT                    26U
#define LPSPI_CFGR1_PCSCFG_SHIFT                    27U
/* DMR0 Bit Fields */
#define LPSPI_DMR0_MATCH0_SHIFT                     0U
/* DMR1 Bit Fields */
#define LPSPI_DMR1_MATCH1_SHIFT                     0U
/* CCR Bit Fields */
#define LPSPI_CCR_SCKDIV_SHIFT                      0U
#define LPSPI_CCR_DBT_SHIFT                         8U
#define LPSPI_CCR_PCSSCK_SHIFT                      16U
#define LPSPI_CCR_SCKPCS_SHIFT                      24U
/* FCR Bit Fields */
#define LPSPI_FCR_TXWATER_SHIFT                     0U
#define LPSPI_FCR_RXWATER_SHIFT                     16U
/* FSR Bit Fields */
#define LPSPI_FSR_TXCOUNT_SHIFT                     0U
#define LPSPI_FSR_RXCOUNT_SHIFT                     16U
/* TCR Bit Fields */
#define LPSPI_TCR_FRAMESZ_SHIFT                     0U
#define LPSPI_TCR_WIDTH_SHIFT                       16U
#define LPSPI_TCR_TXMSK_SHIFT                       18U
#define LPSPI_TCR_RXMSK_SHIFT                       19U
#define LPSPI_TCR_CONTC_SHIFT                       20U
#define LPSPI_TCR_CONT_SHIFT                        21U
#define LPSPI_TCR_BYSW_SHIFT                        22U
#define LPSPI_TCR_LSBF_SHIFT                        23U
#define LPSPI_TCR_PCS_SHIFT                         24U
#define LPSPI_TCR_PRESCALE_SHIFT                    27U
#define LPSPI_TCR_CPHA_SHIFT                        30U
#define LPSPI_TCR_CPOL_SHIFT                        31U
/* TDR Bit Fields */
#define LPSPI_TDR_DATA_SHIFT                        0U
/* RSR Bit Fields */
#define LPSPI_RSR_SOF_SHIFT                         0U
#define LPSPI_RSR_RXEMPTY_SHIFT                     1U
/* RDR Bit Fields */
#define LPSPI_RDR_DATA_SHIFT                        0U

/**
 * @brief    Define option macros for Clock divider 
 */

/* LPSPI_CLKDIV cannot be less than 2 */
#define LPSPI_CLKDIV(x)                             (uint8)(x - 2)

/**
 * @brief    Define option macros for Clock prescaler 
 */
#define LPSPI_PRESCALE_DIV1                         0
#define LPSPI_PRESCALE_DIV2                         1
#define LPSPI_PRESCALE_DIV4                         2
#define LPSPI_PRESCALE_DIV8                         3
#define LPSPI_PRESCALE_DIV16                        4
#define LPSPI_PRESCALE_DIV32                        5
#define LPSPI_PRESCALE_DIV64                        6
#define LPSPI_PRESCALE_DIV128                       7

/**
 * @brief    Define option macros for Clock delay between SCK and PCS 
 */

/* LPSPI_SCK2PCS_DELAY cannot be less than 1 */
#define LPSPI_SCK2PCS_DELAY(x)                      ((uint32)((uint32)(x - 1) << LPSPI_CCR_SCKPCS_SHIFT))
/* LPSPI_PCS2SCK_DELAY cannot be less than 1 */
#define LPSPI_PCS2SCK_DELAY(x)                      ((uint32)((uint32)(x - 1) << LPSPI_CCR_PCSSCK_SHIFT))
/* LPSPI_DBT_DELAY cannot be less than 2 */
#define LPSPI_DBT_DELAY(x)                          ((uint32)((uint32)(x - 2) << LPSPI_CCR_DBT_SHIFT))

/**
 * @brief    Define option macros for Clock polarity 
 */
#define LPSPI_CPOL_LOW                              0
#define LPSPI_CPOL_HIGH                             1

/**
 * @brief    Define option macros for Clock phase 
 */
#define LPSPI_CPHA_CAPTURE_FIRST                    0
#define LPSPI_CPHA_CAPTURE_AFTER                    1

/**
 * @brief    Define option macros for Select supported pin as PCS 
 */
#define LPSPI_PCS_PIN0                              0  
#define LPSPI_PCS_PIN1                              1  
#define LPSPI_PCS_PIN2                              2  
#define LPSPI_PCS_PIN3                              3                                  

/**
 * @brief    Define option macros for Transmit LSB or MSB first 
 */ 
#define LPSPI_MSB_FIRST                             0   
#define LPSPI_LSB_FIRST                             1        

/**
 * @brief    Define option macros for Transmit LSB or MSB first 
 */ 
#define LPSPI_FRAMESIZE(x)                          ((uint16)(x - 1))        

/**
 * @brief    Define option macros for Threshhold to indicate RX buffer full 
 */ 
#define LPSPI_RX_THRESHOLD(x)                       ((uint32)x)    

/**
 * @brief    Define option macros for Threshhold to indicate TX buffer empty 
 */ 
#define LPSPI_TX_THRESHOLD(x)                       ((uint32)x)       

/**
 * @brief    Define option macros for SPI mode 
 */ 
#define LPSPI_MASTER_MODE                           1U
#define LPSPI_SLAVE_MODE                            0U

/**
* @brief  Define macros for LPSPI clock source
*/
#define LPSPI_SOSCDIV2_CLK                          1U
#define LPSPI_SIRCDIV2_CLK                          2U
#define LPSPI_FIRCDIV2_CLK                          3U
#define LPSPI_SPLLDIV2_CLK                          6U

/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/
typedef struct 
{
    /* Configure SPI master or slave */
    uint8 SPIMode;              /* SPI mode */
    /* Clock setting */
    uint8 ClockSource;          /* Peripheral Clock Source to LPSPI module */
    uint8 ClockDivider;         /* Clock divider */
    uint8 ClockPrescaler;       /* Clock prescaler */
    uint32 ClockDelayControl;   /* Clock delay between SCK and PCS */
    /* Configure SPI Signal */
    uint8 CPOL;                 /* Clock polarity: IDLE state of CLK */
    uint8 CPHA;                 /* Clock phase: Sampling at leading edge of SCK */
    uint8 ChipSelectControl;    /* Select supported pin as PCS */  
    uint8 TransmitOrder;        /* Transmit LSB or MSB first */
    /* Configure data frame */
    uint16 Wordlength;          /* Length of dataframe: 8, 16, 32, more will be divided in multiple words */
    /* Configure data buffer detection */
    uint8 RxThreshold;          /* Threshhold to indicate RX buffer full */
    uint8 TxThreshold;          /* Threshhold to indicate TX buffer empty */
} LPSPI_ConfigType;

typedef struct 
{
    /* Pointer to LPSPIx module */
    LPSPI_TypeDef *pLPSPIx;

    /* LPSPI configuration */
    LPSPI_ConfigType LPSPI_Config;
} LPSPI_HandleType;

/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPE
 *****************************************************************************/
/**
 * @brief    This function enable global clock, and configure functional clock to LPSPI module
 */
extern void LPSPI_PeripheralClockConfig(LPSPI_HandleType *pLPSPIHandler);

/**
 * @brief    This function configure SPI mode, transmition, dataframe, clock signal, chip select to LPSPI module
 */
extern void LPSPI_Init(LPSPI_HandleType *pLPSPIHandler);

/**
 * @brief    This function transmit data from buffer with LPSPI module
 */
extern void LPSPI_Transmit(LPSPI_HandleType *LPSPI, uint8 *Txbuffer, uint8 Len);

/**
 * @brief    This function receive data and copy to buffer with LPSPI module
 */
extern void LPSPI_Receive(LPSPI_HandleType *LPSPI, uint8 *Rxbuffer, uint8 Len);

#endif /* DRIVERS_INC_LPSPI_H_ */
