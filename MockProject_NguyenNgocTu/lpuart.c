/******************************************************************************
 * Project Name: LPUART DRIVER
 * File Name:   LPUART.c
 *
 * Description: Implementation of the LPUART
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex-M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "lpuart.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/

/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/

/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPE
 *****************************************************************************/
/**
 *   @brief      This function enable global clock, and configure functional clock to LPUART module.
 *
 *   @param[in]  LPUART_HandleType* LPUART                  Pointer to LPUART handler
 *
 *   @return     void                                       xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void LPUART_PeripheralClockConfig(LPUART_HandleType *LPUART)
{
    /* Enable global clock to LPUART 0 */
    if (LPUART->pLPUARTx == LPUART0)
    {
        PCC->PCC_LPUART0 |= (LPUART->LPUART_Config->ClockSource << PCC_PCS_SHIFT);
        PCC->PCC_LPUART0 |= (1 << PCC_CGC_SHIFT);
    }
    /* Enable global clock to LPUART 1 */
    else if (LPUART->pLPUARTx == LPUART1)
    {
        PCC->PCC_LPUART1 |= (LPUART->LPUART_Config->ClockSource << PCC_PCS_SHIFT);
        PCC->PCC_LPUART1 |= (1 << PCC_CGC_SHIFT);
    }
    /* Enable global clock to LPUART 2 */
    else if (LPUART->pLPUARTx == LPUART2)
    {
        PCC->PCC_LPUART2 |= (LPUART->LPUART_Config->ClockSource << PCC_PCS_SHIFT);
        PCC->PCC_LPUART2 |= (1 << PCC_CGC_SHIFT);
    }
}

/**
 *   @brief      This function configure Baudrate, dataframe to LPUART module.
 *
 *   @param[in]  LPUART_HandleType* LPUART                  Pointer to LPUART handler
 *
 *   @return     void                                       xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void LPUART_Init(LPUART_HandleType *LPUART)
{
    uint32 temp = 0U;
    /* Setting baud rate: Baud rate = baud clock / ((OSR+1) * SBR) */
    temp |= (LPUART->LPUART_Config->OSR << LPUART_BAUD_OSR_SHIFT); /* Oversampling ratio */
    temp |= (LPUART->LPUART_Config->SBR << LPUART_BAUD_SBR_SHIFT); /* Baudrate Modulo Divisor */

    /* Setting Frame*/
    temp |= (LPUART->LPUART_Config->NoStopBits << LPUART_BAUD_SBNS_SHIFT); /* SBNS bit field */
    LPUART->pLPUARTx->BAUD = temp;
    temp = 0U;

    temp |= (LPUART->LPUART_Config->WordLength << LPUART_CTRL_M_SHIFT);     /* M bit field */
    temp |= (LPUART->LPUART_Config->ParityControl << LPUART_CTRL_PE_SHIFT); /* Parity Enable bit field */

    /* If interrupt is used, then set defailt bus state */
    if (LPUART->LPUART_Config->InterruptControl == LPUART_IRQ_ENABLE)
    {
        LPUART->TxStatus = LPUART_READY;
        LPUART->TxStatus = LPUART_READY;
    }

    /* Enable Receiver */
    temp |= (1 << LPUART_CTRL_RE_SHIFT);

    /* Enable Transmiter */
    temp |= (1 << LPUART_CTRL_TE_SHIFT);

    LPUART->pLPUARTx->CTRL = temp;
}

/**
 *   @brief      This function returns status flag of LPUART module.
 *
 *   @param[in]  LPUART_HandleType* pLPUARTx                Pointer to LPUART handler
 *   @param[in]  uint8 StatusFlagShift                      Flag position
 *
 *   @return     void                                       xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
uint8 LPUART_GetFlagStatus(LPUART_TypeDef *pLPUARTx, uint8 StatusFlagShift)
{
    uint8 temp;
    temp = (pLPUARTx->STAT >> StatusFlagShift) & 0X01U;
    return temp;
}

/**
 *   @brief      This function clears status flag of LPUART module.
 *
 *   @param[in]  LPUART_HandleType* pLPUARTx                Pointer to LPUART handler
 *   @param[in]  uint8 StatusFlagShift                      Flag position
 *
 *   @return     void                                       xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void LPUART_ClearFlagStatus(LPUART_TypeDef *pLPUARTx, uint8 StatusFlagShift)
{
    pLPUARTx->STAT |= (1 << StatusFlagShift);
}

/**
 *   @brief      This function transmit data from buffer with LPUART module.
 *
 *   @param[in]  LPUART_HandleType*         Pointer to LPUART handler
 *   @param[in]  uint8*                     Pointer to TX buffer
 *   @param[in]  uint8*                     Length of the buffer
 *
 *   @return     void                       xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void LPUART_Transmit(LPUART_HandleType *LPUART, uint8 *Txbuffer, uint8 Len)
{
    uint8 i;
    uint16 *u16Data;
    if (Len > 0)
    {
        for (i = 0; i < Len; i++)
        {
            /* If data frame is 9 BIT, we send 16 bits */
            if (LPUART->LPUART_Config->WordLength == LPUART_9BIT_DATA)
            {
                /* Pulling for TX buffer to be empty */
                while (((LPUART->pLPUARTx->STAT >> LPUART_STAT_TDRE_SHIFT) & 0X01U) == 0)
                {
                }

                /* Send data to TX buffer */
                u16Data = (uint16 *)Txbuffer;
                LPUART->pLPUARTx->DATA = (*(u16Data + i) & (uint16)0X1FF);
            }
            /* If data frame is 8 BIT, we send 8 bits */
            else if (LPUART->LPUART_Config->WordLength == LPUART_8BIT_DATA)
            {
                /* Pulling for TX buffer to be empty */
                while (((LPUART->pLPUARTx->STAT >> LPUART_STAT_TDRE_SHIFT) & 0X01U) == 0)
                {
                }

                /* Send data to TX buffer */
                LPUART->pLPUARTx->DATA = (*(Txbuffer + i) & (uint8)0XFF);
            }
        }
    }
}

/**
 *   @brief      This function transmit data with newline character from buffer with LPUART module.
 *
 *   @param[in]  LPUART_HandleType*         Pointer to LPUART handler
 *   @param[in]  uint8*                     Pointer to TX buffer
 *
 *   @return     void                       xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void LPUART_TransmitString(LPUART_HandleType *LPUART, uint8 *Txbuffer)
{
    uint8 i = 0U;
    uint16 *u16Data;
    do
    {
        /* If data frame is 9 BIT, we send 16 bits */
        if (LPUART->LPUART_Config->WordLength == LPUART_9BIT_DATA)
        {
            /* Pulling for TX buffer to be empty */
            while (((LPUART->pLPUARTx->STAT >> LPUART_STAT_TDRE_SHIFT) & 0X01U) == 0)
            {
            }

            /* Send data to TX buffer */
            u16Data = (uint16 *)Txbuffer;
            LPUART->pLPUARTx->DATA = (*(u16Data + i) & (uint16)0X1FF);
        }
        /* If data frame is 8 BIT, we send 8 bits */
        else if (LPUART->LPUART_Config->WordLength == LPUART_8BIT_DATA)
        {
            /* Pulling for TX buffer to be empty */
            while (((LPUART->pLPUARTx->STAT >> LPUART_STAT_TDRE_SHIFT) & 0X01U) == 0)
            {
            }

            /* Send data to TX buffer */
            LPUART->pLPUARTx->DATA = (*(Txbuffer + i) & (uint8)0XFF);
        }
        /* Check for a new line character */
    } while (Txbuffer[i++] != '\n');
}

/**
 *   @brief      This function receive data and copy to buffer with LPUART module.
 *
 *   @param[in]  LPUART_HandleType*         Pointer to LPUART handler
 *   @param[in]  uint8*                     Pointer to RX buffer
 *   @param[in]  uint8*                     Length of the buffer
 *
 *   @return     void                       xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void LPUART_Receive(LPUART_HandleType *LPUART, uint8 *Rxbuffer, uint8 Len)
{
    uint8 i;
    if (Len > 0)
    {
        for (i = 0; i < Len; i++)
        {
            /* If data frame is 9 BIT, we receive 16 bits */
            if (LPUART->LPUART_Config->WordLength == LPUART_9BIT_DATA)
            {
                /* Pulling for RX buffer to be full */
                while (((LPUART->pLPUARTx->STAT >> LPUART_STAT_RDRF_SHIFT) & 0X01U) == 0)
                {
                }

                /* Receive data from RX buffer */
                *(Rxbuffer + i) = (uint16)(LPUART->pLPUARTx->DATA & (uint16)0X1FF);
            }
            /* If data frame is 8 BIT, we receive 8 bits */
            else if (LPUART->LPUART_Config->WordLength == LPUART_8BIT_DATA)
            {
                /* Pulling for RX buffer to be full */
                while (((LPUART->pLPUARTx->STAT >> LPUART_STAT_RDRF_SHIFT) & 0X01U) == 0)
                {
                }

                /* Receive data from RX buffer */
                *(Rxbuffer + i) = (uint8)(LPUART->pLPUARTx->DATA & (uint8)0XFF);
            }
        }
    }
}

/**
 *   @brief      This function receive data and copy to buffer with LPUART module using interrupt.
 *
 *   @param[in]  LPUART_HandleType*         Pointer to LPUART handler
 *   @param[in]  uint8*                     Pointer to RX buffer
 *   @param[in]  uint8*                     Length of the buffer
 *
 *   @return     void                       xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void LPUART_ReceiveIT(LPUART_HandleType *LPUART, uint8 *Rxbuffer, uint8 Len)
{
    /* Check TX bus state */
    if (LPUART->RxStatus == LPUART_READY)
    {
        if (Len > 0)
        {
            LPUART->pRxBuffer = Rxbuffer;

            /* Setup RX bus state */
            LPUART->RxStatus = LPUART_BUSY_IN_RX;

            /* Setup RX buffer length */
            LPUART->RxLen = Len;

            /* Enable Receive interrupt */
            LPUART->pLPUARTx->CTRL |= (1 << LPUART_CTRL_RIE_SHIFT);

            /* Enable Receive */
            if ((LPUART->pLPUARTx->CTRL & LPUART_CTRL_RE_MASK) == 0)
            {
                LPUART->pLPUARTx->CTRL |= LPUART_CTRL_RE_MASK;
            }
        }
    }
}

/**
 *   @brief      This function transmit data from buffer with LPUART module using interrupt.
 *
 *   @param[in]  LPUART_HandleType*         Pointer to LPUART handler
 *   @param[in]  uint8*                     Pointer to TX buffer
 *   @param[in]  uint8*                     Length of the buffer
 *
 *   @return     void                       xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void LPUART_TransmitIT(LPUART_HandleType *LPUART, uint8 *Txbuffer, uint8 Len)
{
    /* Check TX bus state */
    if (LPUART->TxStatus == LPUART_READY)
    {
        if (Len > 0)
        {
            LPUART->pTxBuffer = Txbuffer;

            /* Setup TX bus state */
            LPUART->TxStatus = LPUART_BUSY_IN_TX;

            /* Setup TX buffer length */
            LPUART->TxLen = Len;

            /* Enable Transmit interrupt */
            LPUART->pLPUARTx->CTRL |= (1 << LPUART_CTRL_TIE_SHIFT);

            /* Enable Transmit */
            if ((LPUART->pLPUARTx->CTRL & LPUART_CTRL_TE_MASK) == 0)
            {
                LPUART->pLPUARTx->CTRL = LPUART_CTRL_TE_MASK;
            }
        }
    }
}

/**
 *   @brief      This function handle interrupt status of LPUART module.
 *
 *   @param[in]  LPUART_HandleType*         Pointer to LPUART handler
 *
 *   @return     void                       xxxxxxxx
 *
 *   @note       Driver should be called in LPUART interrupt handler function.
 *
 */
void LPUART_IRQHandling(LPUART_HandleType *LPUART)
{
    uint16 *p_u16data = NULL;
    /* Check interrupt request flag */
    /********************************** TC FLAG *************************************/
    if (LPUART_GetFlagStatus(LPUART->pLPUARTx, LPUART_STAT_TC_SHIFT))
    {
        /* Check TX bus state */
        if (LPUART->TxStatus == LPUART_BUSY_IN_TX)
        {
            if (LPUART->TxLen == 0)
            {
                /* Clear TC flag to avoid pending */
                LPUART_ClearFlagStatus(LPUART->pLPUARTx, LPUART_STAT_TC_SHIFT);

                /* Clear TCIE control bit to disable interrupt request flag from TX */
                LPUART->pLPUARTx->CTRL &= ~(1 << LPUART_CTRL_TCIE_SHIFT);

                /* Clear TIE control bit to disable interrupt request flag from TX */
                LPUART->pLPUARTx->CTRL &= ~(1 << LPUART_CTRL_TIE_SHIFT);

                /* Clear TX buffer */
                LPUART->pTxBuffer = NULL;

                /* Clear TX status  */
                LPUART->TxStatus = LPUART_READY;

                LPUART->TxLen = 0;
            }
        }
    }

    /********************************** TXE FLAG ************************************/
    if (LPUART_GetFlagStatus(LPUART->pLPUARTx, LPUART_STAT_TDRE_SHIFT))
    {
        /* Check TX bus state */
        if (LPUART->TxStatus == LPUART_BUSY_IN_TX)
        {
            if (LPUART->TxLen > 0)
            {
                /* If transmit 9 BIT */
                if (LPUART->LPUART_Config->WordLength == LPUART_9BIT_DATA)
                {
                    /* if 9BIT, load the DR with 2bytes masking the bits other than first 9 bits */
                    p_u16data = (uint16 *)LPUART->pTxBuffer;
                    LPUART->pLPUARTx->DATA = (*(p_u16data) & (uint16)0x1FF);

                    /* Increment the pointer to TX buffer */
                    LPUART->pTxBuffer++;
                    LPUART->pTxBuffer++;

                    /* decrement TX buffer length */
                    LPUART->TxLen -= 2;
                }
                /* If transmit 8 bit */
                else
                {
                    // This is 8bit data transfer
                    LPUART->pLPUARTx->DATA = (*(LPUART->pTxBuffer) & (uint8)0xFF);

                    /* Increment the pointer to TX buffer */
                    LPUART->pTxBuffer++;

                    /* decrement TX buffer length */
                    LPUART->TxLen--;
                }
            }
            else if (LPUART->TxLen == 0)
            {
                /* Clear TXEIE control bit to disable interrupt request flag from TX */
                LPUART->pLPUARTx->CTRL &= ~(1 << LPUART_CTRL_TIE_SHIFT);
            }
        }
    }

    /********************************** RXNE FLAG **********************************/
    if (LPUART_GetFlagStatus(LPUART->pLPUARTx, LPUART_STAT_RDRF_SHIFT))
    {
        if (LPUART->RxStatus == LPUART_BUSY_IN_RX)
        {
            if (LPUART->RxLen > 0)
            {

                /* Check the LPUART_WordLength item for 9BIT or 8BIT in a frame */
                if (LPUART->LPUART_Config->WordLength == LPUART_9BIT_DATA)
                {

                    /* if 8BIT, load the DR with 1bytes masking */
                    *((uint16 *)LPUART->pRxBuffer) = (uint16)(LPUART->pLPUARTx->DATA & (uint16)0X1FFU);

                    /* Increment the pointer to RX buffer */
                    LPUART->pRxBuffer++;
                    LPUART->pRxBuffer++;

                    /* decrement RX buffer length */
                    LPUART->RxLen -= 2;
                }
                else
                {
                    /* if 8BIT, load the DR with 1bytes masking */
                    *(LPUART->pRxBuffer) = (uint8)(LPUART->pLPUARTx->DATA & (uint8)0XFFU);

                    /* Increment the pointer to RX buffer */
                    LPUART->pRxBuffer++;

                    /* decrement RX buffer length */
                    LPUART->RxLen--;
                }
            }
            if (LPUART->RxLen == 0)
            {
                if (LPUART->RxStatus == LPUART_BUSY_IN_RX)
                {
                    /* Add null character at the end of string */
                    // *(LPUART->pRxBuffer) = '\0';

                    /* Clear pointer to RX buffer */
                    LPUART->pRxBuffer = NULL;

                    /* Clear RX bus state */
                    LPUART->RxStatus = LPUART_READY;

                    /* Clear RX buffer length */
                    LPUART->RxLen = 0;

                    /* Clear RXNEIE to disable RXNE interrupt request from SR register */
                    LPUART->pLPUARTx->CTRL &= ~(1 << LPUART_CTRL_RIE_SHIFT);

                    /* Perform a RX callback function before return to thread state */
                    LPUART_RX_Callback();
                }
            }
        }
    }
}
