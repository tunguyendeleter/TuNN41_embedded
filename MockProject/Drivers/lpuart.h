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
#include "Common_S32K144.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/**
* @brief  Define macros for Lpuart clock source
*/
#define LPUART_SOSCDIV2_CLK                     1U
#define LPUART_SIRCDIV2_CLK                     2U
#define LPUART_FIRCDIV2_CLK                     3U
#define LPUART_SPLLDIV2_CLK                     6U

/**
* @brief  Define macros for Stop Bit Number Select
*/
#define LPUART_ONEBIT_STOP                      0U
#define LPUART_TWOBIT_STOP                      1U

/**
* @brief  Define macros for 9-Bit or 8-Bit Mode Select
*/
#define LPUART_8BIT_DATA                        0U
#define LPUART_9BIT_DATA                        1U

/**
* @brief  Define macros for Parity Enable Select
*/
#define LPUART_DISABLE_PARITY                   0U
#define LPUART_ENABLE_PARITY                    1U

/**
* @brief  Define macros for Parity Type
*/
#define LPUART_EVEN_PARITY                      0U
#define LPUART_ODD_PARITY                       1U

/**
* @brief  Define macros for Receive, Transmit interrupt
*/
#define LPUART_DISABLE_INTERRUPT                1U
#define LPUART_ENABLE_INTERRUPT                 1U
/**
* @brief  Define MASK for CTRL register  
*/
#define LPUART_CTRL_PT_MASK                     0x1U
#define LPUART_CTRL_PT_SHIFT                    0U
#define LPUART_CTRL_PE_MASK                     0x2U
#define LPUART_CTRL_PE_SHIFT                    1U
#define LPUART_CTRL_M_MASK                      0x10U
#define LPUART_CTRL_M_SHIFT                     4U
#define LPUART_CTRL_RE_MASK                     0x40000U
#define LPUART_CTRL_RE_SHIFT                    18U
#define LPUART_CTRL_TE_MASK                     0x80000U
#define LPUART_CTRL_TE_SHIFT                    19U
#define LPUART_CTRL_TIE_MASK                    0x800000U
#define LPUART_CTRL_TIE_SHIFT                   23U
#define LPUART_CTRL_RIE_MASK                    0x200000U
#define LPUART_CTRL_RIE_SHIFT                   21u
#define LPUART_CTRL_TCIE_MASK                   0x400000U
#define LPUART_CTRL_TCIE_SHIFT                  22U

/**
* @brief  Define MASK for BAUD register  
*/
#define LPUART_BAUD_SBR_MASK                     0x1FFFU
#define LPUART_BAUD_SBR_SHIFT                    0U
#define LPUART_BAUD_OSR_MASK                     0x1F000000U
#define LPUART_BAUD_OSR_SHIFT                    24U
#define LPUART_BAUD_SBNS_MASK                    0x2000U
#define LPUART_BAUD_SBNS_SHIFT                   13U

/* Choose Baud Rate Modulo Divisor Ratio */
#define LPUART_BAUD_SBR(X)	                    (X)		          

/* Choose Oversampling Ratio */
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
#define LPUART_STAT_MA2F_SHIFT                   14u
#define LPUART_STAT_MA1F_SHIFT                   15u
#define LPUART_STAT_PF_SHIFT                     16u
#define LPUART_STAT_FE_SHIFT                     17u
#define LPUART_STAT_NF_SHIFT                     18u
#define LPUART_STAT_OR_SHIFT                     19u
#define LPUART_STAT_IDLE_SHIFT                   20u
#define LPUART_STAT_RDRF_SHIFT                   21u
#define LPUART_STAT_TC_SHIFT                     22u
#define LPUART_STAT_TDRE_SHIFT                   23u
#define LPUART_STAT_RAF_SHIFT                    24u
#define LPUART_STAT_LBKDE_SHIFT                  25u
#define LPUART_STAT_BRK13_SHIFT                  26u
#define LPUART_STAT_RWUID_SHIFT                  27u
#define LPUART_STAT_RXINV_SHIFT                  28u
#define LPUART_STAT_MSBF_SHIFT                   29u
#define LPUART_STAT_RXEDGIF_SHIFT                30u
#define LPUART_STAT_LBKDIF_SHIFT                 31u

/**
* @brief  LPUART application states  
*/
#define LPUART_READY			                0U
#define LPUART_BUSY_IN_TX	                    1U
#define LPUART_BUSY_IN_RX	                    2U

/**
* @brief  LPUART IRQ number
*/
#define LPUART0_IRQ_ID                          31U
#define LPUART1_IRQ_ID                          33U
#define LPUART2_IRQ_ID                          35U
/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/
typedef struct 
{
    /* Clock source setting */
    uint8 ClockSource;
    /* Baudrate setting */
    uint8 OSR;  /* Oversampling ratio */
    uint8 SBR;  /* Baudrate Modulo Divisor */
    /* Frame setting */
    uint8 NoStopBits; /* Stop bit: 1 or 2 stop bits */
    uint8 WordLength;    /* 9-Bit or 8-Bit Mode Select */
    uint8 ParityControl;   /* Parity Enable */
} Lpuart_ConfigType;

typedef struct 
{
    /* Pointer to LPUARTx module */
    LPUART_TypeDef *pLPUARTx;

    /* LPUART configuration */
    Lpuart_ConfigType LPUART_Config;

    uint8* pTxBuffer;                   /*Pointer to TX buffer*/
    uint8* pRxBuffer;                   /*Pointer to RX buffer*/
    uint8 TxStatus;                     /*Status of TX bus*/
    uint8 RxStatus;                     /*Status of RX bus*/
    uint32 TxLen;                       /*TX buffer length*/
    uint32 RxLen;                       /*RX buffer length*/
} Lpuart_HandleType;



/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPE
 *****************************************************************************/
/**
* @brief  This function enable global clock to LPUART module
*/
extern void LPUART_PeripheralClockConfig(Lpuart_HandleType *LPUART);

/**
* @brief  This function configures LPUART module
*/
extern void LPUART_Init(Lpuart_HandleType *LPUART);
extern void LPUART_Transmit(Lpuart_HandleType *LPUART, uint8 *Txbuffer, uint8 Len);
extern uint8 LPUART_GetFlagStatus(LPUART_TypeDef *pLPUARTx, uint8 StatusFlagShift);
extern void LPUART_ClearFlagStatus(LPUART_TypeDef *pLPUARTx, uint8 StatusFlagShift);
extern void LPUART_ReceiveIT(Lpuart_HandleType *LPUART, uint8 *Rxbuffer, uint8 Len);
extern void LPUART_TransmitIT(Lpuart_HandleType *LPUART, uint8 *Txbuffer, uint8 Len);
extern void LPUART_IRQHandling(Lpuart_HandleType *LPUART);
/**
* @brief  This function configures LPUART module
*/
extern void LPUART_TransmitChar(LPUART_TypeDef* LPUARTx, char TransmitData);

/**
* @brief  This function configures LPUART module
*/
extern void LPUART_TransmitString(Lpuart_HandleType *LPUART, uint8 *Txbuffer);

/**
* @brief  This function configures LPUART module
*/
extern char LPUART_ReceiveString(LPUART_TypeDef* LPUARTx);

#endif /* DRIVERS_INC_LPUART_H_ */
