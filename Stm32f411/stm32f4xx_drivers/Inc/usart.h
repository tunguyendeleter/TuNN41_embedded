#ifndef DRIVERS_INC_USART_H_
#define DRIVERS_INC_USART_H_

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "stm32f411xx.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/**
* @brief  Define Status register bit macros
*/
#define USART_SR_CTS_SHIFT                      9U
#define CTS_flag                                (USART_SR_CTS_SHIFT)
#define USART_SR_LBD_SHIFT                      8U
#define LBD_flag                                (USART_SR_LBD_SHIFT)
#define USART_SR_TXE_SHIFT                      7U
#define TXE_flag                                (USART_SR_TXE_SHIFT)
#define USART_SR_TC_SHIFT                       6U
#define TC_flag                                 (USART_SR_TC_SHIFT)
#define USART_SR_RXNE_SHIFT                     5U
#define RXNE_flag                               (USART_SR_RXNE_SHIFT)
#define USART_SR_IDLE_SHIFT                     4U
#define IDLE_flag                               (USART_SR_IDLE_SHIFT)
#define USART_SR_ORE_SHIFT                      3U
#define ORE_flag                                (USART_SR_ORE_SHIFT)
#define USART_SR_NF_SHIFT                       2U
#define NF_flag                                 (USART_SR_NF_SHIFT)
#define USART_SR_FE_SHIFT                       1U
#define FE_flag                                 (USART_SR_FE_SHIFT)
#define USART_SR_PE_SHIFT                       0U
#define PE_flag                                 (USART_SR_PE_SHIFT)

/**
* @brief  Define Data register bit macros
*/
#define USART_DR_MASK                           0X000001FFU

/**
* @brief  Define Baud rate register bit macros
*/
#define USART_BRR_DIV_MANTISSA_SHIFT            0U
#define USART_BRR_DIV_MANTISSA_MASK             0X0000FFF0U
#define USART_BRR_DIV_FRACTION_SHIFT            4U
#define USART_BRR_DIV_FRACTION_MASK             0X0000000FU

/**
* @brief  Define Control register 1 bit macros
*/
#define USART_CR1_OVER8_SHIFT                   15U
#define USART_CR1_UE_SHIFT                      13U
#define USART_CR1_M_SHIFT                       12U
#define USART_CR1_WAKE_SHIFT                    11U
#define USART_CR1_PCE_SHIFT                     10U
#define USART_CR1_PS_SHIFT                      9U
#define USART_CR1_PEIE_SHIFT                    8U
#define USART_CR1_TXEIE_SHIFT                   7U
#define USART_CR1_TCIE_SHIFT                    6U
#define USART_CR1_RXNEIE_SHIFT                  5U
#define USART_CR1_IDLEIE_SHIFT                  4U
#define USART_CR1_TE_SHIFT                      3U
#define USART_CR1_RE_SHIFT                      2U
#define USART_CR1_RWU_SHIFT                     1U
#define USART_CR1_SBK_SHIFT                     0U

/**
* @brief  Define Control register 2 bit macros
*/
#define USART_CR2_LINEN_SHIFT                   14U
#define USART_CR2_STOP_SHIFT                    12U
#define USART_CR2_CLKEN_SHIFT                   11U
#define USART_CR2_CPOL_SHIFT                    10U
#define USART_CR2_CPHA_SHIFT                    9U
#define USART_CR2_LBCL_SHIFT                    8U
#define USART_CR2_LBDIE_SHIFT                   6U
#define USART_CR2_LBDL_SHIFT                    5U
#define USART_CR2_ADD_SHIFT                     0U

/**
* @brief  Define Control register 3 bit macros
*/
#define USART_CR3_ONEBIT_SHIFT                  11U
#define USART_CR3_CTSIE_SHIFT                   10U
#define USART_CR3_CTSE_SHIFT                    9U
#define USART_CR3_RTSE_SHIFT                    8U
#define USART_CR3_DMAT_SHIFT                    7U
#define USART_CR3_DMAR_SHIFT                    6U
#define USART_CR3_SCEN_SHIFT                    5U
#define USART_CR3_NACK_SHIFT                    4U
#define USART_CR3_HDSEL_SHIFT                   3U
#define USART_CR3_IRLP_SHIFT                    2U
#define USART_CR3_IREN_SHIFT                    1U
#define USART_CR3_EIE_SHIFT                     0U

/*
 *@USART_Mode
 *Possible options for USART_Mode
 */
#define USART_MODE_ONLY_TX 0
#define USART_MODE_ONLY_RX 1
#define USART_MODE_TXRX  2

/*
 *@USART_Baud
 *Possible options for USART_Baud
 */
#define USART_STD_BAUD_1200					1200
#define USART_STD_BAUD_2400					400
#define USART_STD_BAUD_9600					9600
#define USART_STD_BAUD_19200 				19200
#define USART_STD_BAUD_38400 				38400
#define USART_STD_BAUD_57600 				57600
#define USART_STD_BAUD_115200 				115200
#define USART_STD_BAUD_230400 				230400
#define USART_STD_BAUD_460800 				460800
#define USART_STD_BAUD_921600 				921600
#define USART_STD_BAUD_2M 					2000000
#define SUART_STD_BAUD_3M 					3000000

/*
 *@USART_ParityControl
 *Possible options for USART_ParityControl
 */
#define USART_PARITY_EN_ODD             2
#define USART_PARITY_EN_EVEN            1
#define USART_PARITY_DISABLE            0

/*
 *@USART_WordLength
 *Possible options for USART_WordLength
 */
#define USART_WORDLEN_8BITS             0
#define USART_WORDLEN_9BITS             1

/*
 *@USART_NoOfStopBits
 *Possible options for USART_NoOfStopBits
 */
#define USART_STOPBITS_1                0
#define USART_STOPBITS_0_5              1
#define USART_STOPBITS_2                2
#define USART_STOPBITS_1_5              3

/*
 *@USART_HWFlowControl
 *Possible options for USART_HWFlowControl
 */
#define USART_HW_FLOW_CTRL_NONE         0
#define USART_HW_FLOW_CTRL_CTS          1
#define USART_HW_FLOW_CTRL_RTS          2
#define USART_HW_FLOW_CTRL_CTS_RTS	    3

/*
 * USART application states
 */
#define USART_READY			0
#define USART_BUSY_IN_TX	1
#define USART_BUSY_IN_RX	2

/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/
/**
* @brief  structure of USART config mode
*/
typedef struct 
{
    uint8 USART_Mode;                   /*Transmit mode or Receive mode or Both modes*/
    uint32 USART_Baud;                  /*Baud rate*/
    uint8 USART_NoOfStopBits;           /*Number of stop bits*/
    uint8 USART_WordLength;             /*Length of data frame*/
    uint8 USART_ParityControl;          /*Parity odd or even (if included)*/
    uint8 USART_HWFlowControl;          /*Hardware flowcontrol detail*/
}USART_Config_Type;

/**
* @brief  structure of USART config handle
*/
typedef struct 
{
    USART_Type* pUSARTx;                /*This is a pointer to hold address of USART port to which the pins belong*/
    USART_Config_Type USART_Config;     /*This holds USART pin configuation settings*/
    uint8* pTxBuffer;                   /*Pointer to TX buffer*/
    uint8* pRxBuffer;                   /*Pointer to RX buffer*/
    uint8 TxStatus;                     /*Status of TX bus*/
    uint8 RxStatus;                     /*Status of RX bus*/
    uint32 TxLen;                       /*TX buffer length*/
    uint32 RxLen;                       /*RX buffer length*/
}USART_Handle_Type;


/******************************************************************************
 *  GLOBAL VARIABLES
 *****************************************************************************/


/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/
/**
* @brief  this function setup global clock to USART
*/
extern void USART_PeriClockControl(USART_Type *pUSARTx, uint8 EnorDis);

/**
* @brief  this function configures USART dataframe
*/
extern void USART_Init(USART_Handle_Type* pUSARTHandle);

/**
* @brief  this function configures USART baudrate
*/
void USART_SetBaudRate(USART_Handle_Type *pUSARTHandle);

/**
* @brief  this function write and read data
*/
extern void USART_Write(USART_Handle_Type* pUSARTHandle, uint8* pTxBuffer, uint32 Len);
extern void USART_Read(USART_Handle_Type *pUSARTHandle, uint8 *pRxBuffer, uint32 Len);

/**
* @brief  this function write and read data with interrupt
*/
extern uint8 USART_WriteIT(USART_Handle_Type *pUSARTHandle, uint8 *pTxBuffer, uint32 Len);
extern uint8 USART_ReadIT(USART_Handle_Type *pUSARTHandle, uint8 *pRxBuffer, uint32 Len);
extern void USART_IRQHandling(USART_Handle_Type *pUSARTHandle);

/**
* @brief  this function gets and clears status flag
*/
extern uint8 USART_GetFlagStatus(USART_Type *pUSARTx, uint8 StatusFlagShift);
extern void USART_ClearFlagStatus(USART_Type *pUSARTx, uint8 StatusFlagShift);

#endif /* DRIVERS_INC_USART_H_ */
