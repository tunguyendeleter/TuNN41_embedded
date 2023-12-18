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
* @brief  Define macros for Lpuart clock source
*/
#define LPUART_SOSCDIV2_CLK         1U
#define LPUART_SIRCDIV2_CLK         2U
#define LPUART_FIRCDIV2_CLK         3U
#define LPUART_SPLLDIV2_CLK         6U

/**
* @brief  Define macros for Stop Bit Number Select
*/
#define LPUART_ONEBIT_STOP          0U
#define LPUART_TWOBIT_STOP          1U

/**
* @brief  Define macros for 9-Bit or 8-Bit Mode Select
*/
#define LPUART_8BIT_DATA            0U
#define LPUART_9BIT_DATA            1U

/**
* @brief  Define macros for Parity Enable Select
*/
#define LPUART_DISABLE_PARITY       0U
#define LPUART_ENABLE_PARITY        1U

/**
* @brief  Define macros for Parity Type
*/
#define LPUART_EVEN_PARITY          0U
#define LPUART_ODD_PARITY           1U

/**
* @brief  Define macros for Receive, Transmit interrupt
*/
#define LPUART_DISABLE_INTERRUPT    1U
#define LPUART_ENABLE_INTERRUPT     1U
/**
* @brief  Define MASK for CTRL register  
*/
#define LPUART_CTRL_PT_MASK                      0x1U
#define LPUART_CTRL_PT_SHIFT                     0U
#define LPUART_CTRL_PE_MASK                      0x2U
#define LPUART_CTRL_PE_SHIFT                     1U
#define LPUART_CTRL_M_MASK                       0x10U
#define LPUART_CTRL_M_SHIFT                      4U
#define LPUART_CTRL_RE_MASK                      0x40000U
#define LPUART_CTRL_RE_SHIFT                     18U
#define LPUART_CTRL_TE_MASK                      0x80000U
#define LPUART_CTRL_TE_SHIFT                     19U
#define LPUART_CTRL_TIE_MASK                     0x800000U
#define LPUART_CTRL_TIE_SHIFT                    23U
#define LPUART_CTRL_RIE_MASK                     0x200000U
#define LPUART_CTRL_RIE_SHIFT                    21U

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
#define LPUART_BAUD_SBR(X)	(X)		          

/* Choose Oversampling Ratio */
#define LPUART_BAUD_OSR(X)	(X-1)		        

/**
* @brief  Define MASK for BAUD register  
*/
#define LPUART_IT_TR                            0U
#define LPUART_IT_RE                            1U
#define LPUART_IT_TR_RE                         2U

/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/
typedef struct 
{
    /* Pointer to LPUARTx module */
    LPUART_TypeDef *LPUARTx;
    /* Clock source setting */
    uint8 ClockSource;
    /* Baudrate setting */
    uint8 OSR;  /* Oversampling ratio */
    uint8 SBR;  /* Baudrate Modulo Divisor */
    /* Frame setting */
    uint8 SBNS; /* Stop bit: 1 or 2 stop bits */
    uint8 M;    /* 9-Bit or 8-Bit Mode Select */
    uint8 PE;   /* Parity Enable */
    /* Interrupt setting */
    uint8 RIE;  /* Receive interrupt */
} Lpuart_ConfigType;


/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPE
 *****************************************************************************/
/**
* @brief  This function configures LPUART module
*/
extern void LPUART_ConfigReceiveIT(LPUART_TypeDef *LPUARTx, uint32 SBR, uint32 OSR, uint32 Rx_Status, uint32 Tx_Status, uint8 Interrupt_Type);

extern void LPUART_TransmitChar(LPUART_TypeDef* LPUARTx, char TransmitData);

extern void LPUART_TransmitString(LPUART_TypeDef* LPUARTx, char TransmitString[]);

extern char LPUART_ReceiveString(LPUART_TypeDef* LPUARTx);

#endif /* DRIVERS_INC_LPUART_H_ */