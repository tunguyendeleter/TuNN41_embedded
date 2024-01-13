/******************************************************************************
 * Project Name: LPUART DRIVER
 * File Name:   lpuart.h
 *
 * Description: Implementation of the LPUART
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex-M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/
#ifndef DRIVERS_INC_LPUART_H_
#define DRIVERS_INC_LPUART_H_

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "S32K144xx.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/**
* @brief  Define macros for LPUART clock source
* @Clockoption 
*/
#define LPUART_SOSCDIV2_CLK                     1U
#define LPUART_SIRCDIV2_CLK                     2U
#define LPUART_FIRCDIV2_CLK                     3U
#define LPUART_SPLLDIV2_CLK                     6U

/**
* @brief  Define macros for Stop Bit Number Select
* @StopBitConfig 
*/
#define LPUART_ONEBIT_STOP                      0U
#define LPUART_TWOBIT_STOP                      1U

/**
* @brief  Define macros for 9-Bit or 8-Bit Mode Select
* @Dataframe 
*/
#define LPUART_8BIT_DATA                        0U
#define LPUART_9BIT_DATA                        1U

/**
* @brief  Define macros for Parity Enable Select
* @ParityOption 
*/
#define LPUART_DISABLE_PARITY                   0U
#define LPUART_ENABLE_PARITY                    1U

/**
* @brief  Define macros for Parity Type
* @Clockoption 
*/
#define LPUART_EVEN_PARITY                      0U
#define LPUART_ODD_PARITY                       1U

/**
* @brief  Define macros for Receive, Transmit interrupt
* @Clockoption 
*/
#define LPUART_DISABLE_INTERRUPT                1U
#define LPUART_ENABLE_INTERRUPT                 1U
/**
* @brief  Define MASK for CTRL register  
*/
#define LPUART_CTRL_PT_MASK                     0X1U
#define LPUART_CTRL_PT_SHIFT                    0U
#define LPUART_CTRL_PE_MASK                     0X2U
#define LPUART_CTRL_PE_SHIFT                    1U
#define LPUART_CTRL_M_MASK                      0X10U
#define LPUART_CTRL_M_SHIFT                     4U
#define LPUART_CTRL_RE_MASK                     0X40000U
#define LPUART_CTRL_RE_SHIFT                    18U
#define LPUART_CTRL_TE_MASK                     0X80000U
#define LPUART_CTRL_TE_SHIFT                    19U
#define LPUART_CTRL_TIE_MASK                    0X800000U
#define LPUART_CTRL_TIE_SHIFT                   23U
#define LPUART_CTRL_RIE_MASK                    0X200000U
#define LPUART_CTRL_RIE_SHIFT                   21u
#define LPUART_CTRL_TCIE_MASK                   0X400000U
#define LPUART_CTRL_TCIE_SHIFT                  22U

/**
* @brief  Define MASK for BAUD register  
*/
#define LPUART_BAUD_SBR_MASK                    0X1FFFU
#define LPUART_BAUD_SBR_SHIFT                   0U
#define LPUART_BAUD_OSR_MASK                    0X1F000000U
#define LPUART_BAUD_OSR_SHIFT                   24U
#define LPUART_BAUD_SBNS_MASK                   0X2000U
#define LPUART_BAUD_SBNS_SHIFT                  13U

/**
* @brief  Define macros for Baud Rate Modulo Divisor Ratio  
* @BaudrateDivisor
*/
#define LPUART_BAUD_SBR(X)	                    (X)		          

/**
* @brief  Define macros for Oversampling Ratio  
* @Oversamplingratio
*/
#define LPUART_BAUD_OSR(X)	                    (X-1)		        

/**
* @brief  Define MASK for BAUD register  
*/
#define LPUART_IT_TR                            0U
#define LPUART_IT_RE                            1U
#define LPUART_IT_TR_RE                         2U

/**
* @brief  Define SHIFT for STAT register  
*/
#define LPUART_STAT_MA2F_SHIFT                  14U
#define LPUART_STAT_MA1F_SHIFT                  15U
#define LPUART_STAT_PF_SHIFT                    16U
#define LPUART_STAT_FE_SHIFT                    17U
#define LPUART_STAT_NF_SHIFT                    18U
#define LPUART_STAT_OR_SHIFT                    19U
#define LPUART_STAT_IDLE_SHIFT                  20U
#define LPUART_STAT_RDRF_SHIFT                  21U
#define LPUART_STAT_TC_SHIFT                    22U
#define LPUART_STAT_TDRE_SHIFT                  23U
#define LPUART_STAT_RAF_SHIFT                   24U
#define LPUART_STAT_LBKDE_SHIFT                 25U
#define LPUART_STAT_BRK13_SHIFT                 26U
#define LPUART_STAT_RWUID_SHIFT                 27U
#define LPUART_STAT_RXINV_SHIFT                 28U
#define LPUART_STAT_MSBF_SHIFT                  29U
#define LPUART_STAT_RXEDGIF_SHIFT               30U
#define LPUART_STAT_LBKDIF_SHIFT                31U

/**
* @brief  LPUART application states 
* @Busstate 
*/
#define LPUART_READY                            0U
#define LPUART_BUSY_IN_TX	                    1U
#define LPUART_BUSY_IN_RX	                    2U

/**
* @brief  LPUART IRQ number
*/
#define LPUART0_IRQ_ID                          31U
#define LPUART1_IRQ_ID                          33U
#define LPUART2_IRQ_ID                          35U

/**
* @brief  Interrupt Control macros
* @InterruptOption 
*/
#define LPUART_IRQ_ENABLE                       ENABLE
#define LPUART_IRQ_DISABLE                      DISABLE
/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/
typedef struct 
{
    /* Clock source setting */
    uint8 ClockSource;                  /* @ClockOption: Peripheral Clock Source to LPUART module */
    /* Baudrate setting */
    uint8 OSR;                          /* @Oversamplingratio: Oversampling ratio */
    uint8 SBR;                          /* @BaudrateDivisor: Baudrate Modulo Divisor */
    /* Frame setting */
    uint8 NoStopBits;                   /* @StopBitConfig: Stop bit: 1 or 2 stop bits */
    uint8 WordLength;                   /* @Dataframe: 9-Bit or 8-Bit Mode Select */
    uint8 ParityControl;                /* @ParityOption: Parity Enable */
    /* Interrupt setting */
    uint8 InterruptControl;             /* @InterruptOption: Interrupt control option */
} LPUART_ConfigType;

typedef struct 
{
    /* Pointer to LPUARTx module */
    LPUART_TypeDef *pLPUARTx;

    /* LPUART configuration */
    LPUART_ConfigType *LPUART_Config;

    /* LPUART interrupt transmition parameters */
    uint8* pTxBuffer;                   /*Pointer to TX buffer*/
    uint8* pRxBuffer;                   /*Pointer to RX buffer*/
    uint8 TxStatus;                     /* @Busstate: Status of TX bus*/
    uint8 RxStatus;                     /* @Busstate: Status of RX bus*/
    uint32 TxLen;                       /*TX buffer length*/
    uint32 RxLen;                       /*RX buffer length*/
} LPUART_HandleType;

/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPE
 *****************************************************************************/
/**
* @brief  This function enable global clock, and configure functional clock to LPUART module
*/
extern void LPUART_PeripheralClockConfig(LPUART_HandleType *LPUART);

/**
* @brief  This function configure Baudrate, dataframe to LPUART module
*/
extern void LPUART_Init(LPUART_HandleType *LPUART);

/**
* @brief  This function receive data and copy to buffer with LPUART module
*/
extern void LPUART_Receive(LPUART_HandleType *LPUART, uint8 *Rxbuffer, uint8 Len);

/**
* @brief  This function transmit data from buffer with LPUART module
*/
extern void LPUART_Transmit(LPUART_HandleType *LPUART, uint8 *Txbuffer, uint8 Len);

/**
* @brief  This function transmit data with newline character from buffer with LPUART module
*/
extern void LPUART_TransmitString(LPUART_HandleType *LPUART, uint8 *Txbuffer);

/**
* @brief  This function returns status flag of LPUART module
*/
extern uint8 LPUART_GetFlagStatus(LPUART_TypeDef *pLPUARTx, uint8 StatusFlagShift);

/**
* @brief  This function clears status flag of LPUART module
*/
extern void LPUART_ClearFlagStatus(LPUART_TypeDef *pLPUARTx, uint8 StatusFlagShift);

/**
* @brief  This function receive data and copy to buffer with LPUART module using interrupt
*/
extern void LPUART_ReceiveIT(LPUART_HandleType *LPUART, uint8 *Rxbuffer, uint8 Len);

/**
* @brief  This function transmit data from buffer with LPUART module using interrupt
*/
extern void LPUART_TransmitIT(LPUART_HandleType *LPUART, uint8 *Txbuffer, uint8 Len);

/**
* @brief  This function handle interrupt status of LPUART module
*/
extern void LPUART_IRQHandling(LPUART_HandleType *LPUART);

extern void LPUART_RX_Callback(void);

#endif /* DRIVERS_INC_LPUART_H_ */
