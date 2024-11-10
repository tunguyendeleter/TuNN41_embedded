/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "usart.h"
#include "rcc.h"

/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/
void USART_PeriClockControl(USART_Type *pUSARTx, uint8 EnorDis)
{
    if (EnorDis == ENABLE)
    {
        if (pUSARTx == USART1)
            USART1_CLK_EN();
        else if (pUSARTx == USART2)
            USART2_CLK_EN();
        else if (pUSARTx == USART6)
            USART6_CLK_EN();
    }
    else if (EnorDis == DISABLE)
    {
        if (pUSARTx == USART1)
            USART1_CLK_DIS();
        else if (pUSARTx == USART2)
            USART2_CLK_DIS();
        else if (pUSARTx == USART6)
            USART6_CLK_DIS();
    }
}

void USART_Init(USART_Handle_Type *pUSARTHandle)
{
    // Temporary variable
    uint32 tempreg = 0;

    /******************************** Configuration of CR1******************************************/

    // Implement the code to enable the Clock for given USART peripheral
    if (pUSARTHandle->pUSARTx == USART1)
    {
        USART1_CLK_EN();
    }
    else if (pUSARTHandle->pUSARTx == USART2)
    {
        USART2_CLK_EN();
    }
    else if (pUSARTHandle->pUSARTx == USART6)
    {
        USART6_CLK_EN();
    }

    // Enable USART Tx and Rx engines according to the USART_Mode configuration item
    if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_RX)
    {
        // Implement the code to enable the Receiver bit field
        tempreg |= (1 << USART_CR1_RE_SHIFT);
    }
    else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_TX)
    {
        // Implement the code to enable the Transmitter bit field
        tempreg |= (1 << USART_CR1_TE_SHIFT);
    }
    else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TXRX)
    {
        // Implement the code to enable the both Transmitter and Receiver bit fields
        tempreg |= ((1 << USART_CR1_TE_SHIFT) | (1 << USART_CR1_RE_SHIFT));
    }

    // Implement the code to configure the Word length configuration item
    tempreg |= pUSARTHandle->USART_Config.USART_WordLength << USART_CR1_M_SHIFT;

    // Configuration of parity control bit fields
    if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_EVEN)
    {
        // Implement the code to enale the parity control
        tempreg |= (1 << USART_CR1_PCE_SHIFT);

        // Implement the code to enable EVEN parity
        tempreg &= ~(1 << USART_CR1_PS_SHIFT);

        // Not required because by default EVEN parity will be selected once you enable the parity control
    }
    else if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_ODD)
    {
        // Implement the code to enable the parity control
        tempreg |= (1 << USART_CR1_PCE_SHIFT);

        // Implement the code to enable ODD parity
        tempreg |= (1 << USART_CR1_PS_SHIFT);
    }

    // Program the CR1 register
    pUSARTHandle->pUSARTx->CR1 = tempreg;

    /******************************** Configuration of CR2******************************************/

    tempreg = 0;

    // Implement the code to configure the number of stop bits inserted during USART frame transmission
    tempreg |= pUSARTHandle->USART_Config.USART_NoOfStopBits << USART_CR2_STOP_SHIFT;

    // Program the CR2 register
    pUSARTHandle->pUSARTx->CR2 = tempreg;

    /******************************** Configuration of CR3******************************************/

    tempreg = 0;

    // Configuration of USART hardware flow control
    if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS)
    {
        // Implement the code to enable CTS flow control
        tempreg |= (1 << USART_CR3_CTSE_SHIFT);
    }
    else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS)
    {
        // Implement the code to enable RTS flow control
        tempreg |= (1 << USART_CR3_RTSE_SHIFT);
    }
    else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS)
    {
        // Implement the code to enable both CTS and RTS Flow control
        tempreg |= ((1 << USART_CR3_CTSE_SHIFT) | (1 << USART_CR3_RTSE_SHIFT));
    }

    pUSARTHandle->pUSARTx->CR3 = tempreg;

    /* Clear pointer to RX buffer */
    pUSARTHandle->pRxBuffer = NULL;
    /* Clear pointer to TX buffer */
    pUSARTHandle->pTxBuffer = NULL;

    /* Clear RX bus state */
    pUSARTHandle->RxStatus = USART_READY;
    /* Clear TX bus state */
    pUSARTHandle->TxStatus = USART_READY;

    /* Clear RX buffer length */
    pUSARTHandle->RxLen = 0;
    /* Clear TX buffer length */
    pUSARTHandle->TxLen = 0;
}

void USART_SetBaudRate(USART_Handle_Type *pUSARTHandle)
{
    // Variable to hold the APB clock
    uint32_t PCLKx;

    uint32_t usartdiv;

    // variables to hold Mantissa and Fraction values
    uint32_t M_part, F_part;

    uint32_t tempreg = 0;

    // Get the value of APB bus clock in to the variable PCLKx
    if (pUSARTHandle->pUSARTx == USART1 || pUSARTHandle->pUSARTx == USART6)
    {
        // USART1 and USART6 are hanging on APB2 bus
        PCLKx = RCC_GetPCLK2Value();
    }
    else
    {
        PCLKx = RCC_GetPCLK1Value();
    }

    // Check for OVER8 configuration bit
    if (pUSARTHandle->pUSARTx->CR1 & (1 << USART_CR1_OVER8_SHIFT))
    {
        // OVER8 = 1 , over sampling by 8
        usartdiv = ((25 * PCLKx) / (2 * pUSARTHandle->USART_Config.USART_Baud));
    }
    else
    {
        // over sampling by 16
        usartdiv = ((25 * PCLKx) / (4 * pUSARTHandle->USART_Config.USART_Baud));
    }

    // Calculate the Mantissa part
    M_part = usartdiv / 100;

    // Place the Mantissa part in appropriate bit position . refer USART_BRR
    tempreg |= M_part << 4;

    // Extract the fraction part
    F_part = (usartdiv - (M_part * 100));

    // Calculate the final fractional
    if (pUSARTHandle->pUSARTx->CR1 & (1 << USART_CR1_OVER8_SHIFT))
    {
        // OVER8 = 1 , over sampling by 8
        F_part = (((F_part * 8) + 50) / 100) & ((uint8_t)0x07);
    }
    else
    {
        // over sampling by 16
        F_part = (((F_part * 16) + 50) / 100) & ((uint8_t)0x0F);
    }

    // Place the fractional part in appropriate bit position . refer USART_BRR
    tempreg |= F_part;

    // copy the value of tempreg in to BRR register
    pUSARTHandle->pUSARTx->BRR = tempreg;

    // Enable USART
    pUSARTHandle->pUSARTx->CR1 |= (1 << USART_CR1_UE_SHIFT);
}

uint8 USART_GetFlagStatus(USART_Type *pUSARTx, uint8 StatusFlagShift)
{
    uint8 temp;
    switch (StatusFlagShift)
    {
    case CTS_flag:
        /* Get flag status of CTS flag */
        temp = (pUSARTx->SR >> USART_SR_CTS_SHIFT) & 0X01U;
        break;
    case LBD_flag:
        /* Get flag status of LBD flag */
        temp = (pUSARTx->SR >> USART_SR_LBD_SHIFT) & 0X01U;
        break;
    case TXE_flag:
        /* Get flag status of TXE flag */
        temp = (pUSARTx->SR >> USART_SR_TXE_SHIFT) & 0X01U;
        break;
    case TC_flag:
        /* Get flag status of TC flag */
        temp = (pUSARTx->SR >> USART_SR_TC_SHIFT) & 0X01U;
        break;
    case RXNE_flag:
        /* Get flag status of RXNE flag */
        temp = (pUSARTx->SR >> USART_SR_RXNE_SHIFT) & 0X01U;
        break;
    case IDLE_flag:
        /* Get flag status of IDLE flag */
        temp = (pUSARTx->SR >> USART_SR_IDLE_SHIFT) & 0X01U;
        break;
    case ORE_flag:
        /* Get flag status of ORE flag */
        temp = (pUSARTx->SR >> USART_SR_ORE_SHIFT) & 0X01U;
        break;
    case NF_flag:
        /* Get flag status of NF flag */
        temp = (pUSARTx->SR >> USART_SR_NF_SHIFT) & 0X01U;
        break;
    case FE_flag:
        /* Get flag status of FE flag */
        temp = (pUSARTx->SR >> USART_SR_FE_SHIFT) & 0X01U;
        break;
    case PE_flag:
        /* Get flag status of PE flag */
        temp = (pUSARTx->SR >> USART_SR_PE_SHIFT) & 0X01U;
        break;
    default:
        break;
    }

    return temp;
}

void USART_ClearFlagStatus(USART_Type *pUSARTx, uint8 StatusFlagShift)
{
    pUSARTx->SR &= ~(1 << StatusFlagShift);
}

void USART_Write(USART_Handle_Type *pUSARTHandle, uint8 *pTxBuffer, uint32 Len)
{
    uint8 *p_u8data;
    uint16 *p_u16data;
    // Loop over until "Len" number of bytes are transferred
    for (uint32_t i = 0; i < Len; i++)
    {
        // Implement the code to wait until TXE flag is set in the SR
        while (!USART_GetFlagStatus(pUSARTHandle->pUSARTx, TXE_flag))
            ;

        // Check the USART_WordLength item for 9BIT or 8BIT in a frame
        if (pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
        {
            // if 9BIT, load the DR with 2bytes masking the bits other than first 9 bits
            p_u16data = (uint16_t *)pTxBuffer;
            pUSARTHandle->pUSARTx->DR = (*(p_u16data + i) & (uint16_t)0x01FF);
        }
        else
        {
            // This is 8bit data transfer
            p_u8data = pTxBuffer;
            pUSARTHandle->pUSARTx->DR |= (*(p_u8data + i) & (uint8_t)0x00FF);
        }
    }

    // Implement the code to wait till TC flag is set in the SR
    while (!USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_SR_TC_SHIFT))
        ;
}

void USART_Read(USART_Handle_Type *pUSARTHandle, uint8 *pRxBuffer, uint32 Len)
{
    uint8 *p_u8data;
    uint16 *p_u16data;
    uint32 i;

    // Loop over until "Len" number of bytes are transferred
    for (i = 0; i < Len; i++)
    {
        // Implement the code to wait until TXE flag is set in the SR
        while (!USART_GetFlagStatus(pUSARTHandle->pUSARTx, RXNE_flag))
            ;

        // Check the USART_WordLength item for 9BIT or 8BIT in a frame
        if (pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
        {
            // if 9BIT, load the DR with 2bytes masking the bits other than first 9 bits
            p_u16data = (uint16 *)pRxBuffer;
            *(p_u16data + i) = (uint16)(pUSARTHandle->pUSARTx->DR & (uint16)0X1FFU);
        }
        else
        {
            // This is 8bit data receive
            p_u8data = pRxBuffer;
            *(p_u8data + i) = (uint8)(pUSARTHandle->pUSARTx->DR & (uint8)0XFFU);
        }
    }
}

uint8 USART_WriteIT(USART_Handle_Type *pUSARTHandle, uint8 *pTxBuffer, uint32 Len)
{
    uint8 TXState = pUSARTHandle->TxStatus;
    if (TXState != USART_BUSY_IN_TX)
    {
        if (Len > 0)
        {
            /* Setup UE to disable USARTx in CR1 */
            // pUSARTHandle->pUSARTx->CR1 &= ~(1 << USART_CR1_UE_SHIFT);

            /* Setup pointer to TX buffer */
            pUSARTHandle->pTxBuffer = pTxBuffer;

            /* Setup TX bus state */
            pUSARTHandle->TxStatus = USART_BUSY_IN_TX;

            /* Setup TX buffer length */
            pUSARTHandle->TxLen = Len;

            /* Setup TXEIE to enbble TXE interrupt request from SR register */
            pUSARTHandle->pUSARTx->CR1 |= (1 << USART_CR1_TXEIE_SHIFT);

            /* Setup TCIE to enbble TC interrupt request from SR register */
            pUSARTHandle->pUSARTx->CR1 |= (1 << USART_CR1_TCIE_SHIFT);

            /* Setup UE to enable USARTx in CR1 */
            pUSARTHandle->pUSARTx->CR1 |= (1 << USART_CR1_UE_SHIFT);
        }
    }
    return TXState;
}

uint8 USART_ReadIT(USART_Handle_Type *pUSARTHandle, uint8 *pRxBuffer, uint32 Len)
{
    uint8 RXState = pUSARTHandle->RxStatus;
    if (RXState != USART_BUSY_IN_RX)
    {
        if (Len > 0)
        {
            /* Setup UE to disable USARTx in CR1 */
            // pUSARTHandle->pUSARTx->CR1 &= ~(1 << USART_CR1_UE_SHIFT);

            /* Setup pointer to RX buffer */
            // *pRxBuffer = NULL;
            pUSARTHandle->pRxBuffer = pRxBuffer;

            /* Setup RX bus state */
            pUSARTHandle->RxStatus = USART_BUSY_IN_RX;

            /* Setup RX buffer length */
            pUSARTHandle->RxLen = Len;

            /* Setup RXNEIE to enbble RXNE interrupt request from SR register */
            pUSARTHandle->pUSARTx->CR1 |= (1 << USART_CR1_RXNEIE_SHIFT);

            /* Setup UE to enable USARTx in CR1 */
            if (!(pUSARTHandle->pUSARTx->CR1 & (1 << USART_CR1_UE_SHIFT)))
            {
                pUSARTHandle->pUSARTx->CR1 |= (1 << USART_CR1_UE_SHIFT);
            }
        }
    }
    return RXState;
}

void USART_IRQHandling(USART_Handle_Type *pUSARTHandle)
{
    uint16 *p_u16data = NULL;
    /* Check interrupt request flag */
    /********************************** TC FLAG *************************************/
    if (USART_GetFlagStatus(pUSARTHandle->pUSARTx, TC_flag))
    {
        /* Check TX bus state */
        if (pUSARTHandle->TxStatus == USART_BUSY_IN_TX)
        {
            if (pUSARTHandle->TxLen == 0)
            {
                /* Clear TC flag to avoid pending */
                USART_ClearFlagStatus(pUSARTHandle->pUSARTx, TC_flag);

                /* Clear TCIE control bit to disable interrupt request flag from TXE */
                pUSARTHandle->pUSARTx->CR1 &= ~(1 << USART_CR1_TCIE_SHIFT);

                /* Clear TXEIE control bit to disable interrupt request flag from TXE */
                pUSARTHandle->pUSARTx->CR1 &= ~(1 << USART_CR1_TXEIE_SHIFT);

                /* Clear TX buffer */
                pUSARTHandle->pTxBuffer = NULL;

                /* Clear TX status  */
                pUSARTHandle->TxStatus = USART_READY;

                pUSARTHandle->TxLen = 0;

                /* Setup TXEIE and ICIE to disable transmit */
                pUSARTHandle->pUSARTx->CR1 &= ~((1 << USART_CR1_TXEIE_SHIFT) | (1 << USART_CR1_TCIE_SHIFT));
            }
        }
    }

    /********************************** TXE FLAG ************************************/
    if (USART_GetFlagStatus(pUSARTHandle->pUSARTx, TXE_flag))
    {
        /* Check TX bus state */
        if (pUSARTHandle->TxStatus == USART_BUSY_IN_TX)
        {
            if (pUSARTHandle->TxLen > 0)
            {
                /* If transmit 9 BIT */
                if (pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
                {
                    /* if 9BIT, load the DR with 2bytes masking the bits other than first 9 bits */
                    p_u16data = (uint16 *)pUSARTHandle->pTxBuffer;
                    pUSARTHandle->pUSARTx->DR = (*(p_u16data) & (uint16_t)0x01FF);

                    /* If parity control is used in buffer */
                    if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
                    {
                        /* Increment the pointer to TX buffer */
                        pUSARTHandle->pTxBuffer++;
                        pUSARTHandle->pTxBuffer++;
                    }
                    else
                    {
                        /* Increment the pointer to TX buffer */
                        pUSARTHandle->pTxBuffer++;
                    }

                    /* decrement TX buffer length */
                    pUSARTHandle->TxLen -= 2;
                }
                /* If transmit 8 bit */
                else
                {
                    // This is 8bit data transfer
                    pUSARTHandle->pUSARTx->DR = (*(pUSARTHandle->pTxBuffer) & (uint8_t)0xFF);

                    /* Increment the pointer to TX buffer */
                    pUSARTHandle->pTxBuffer++;

                    /* decrement TX buffer length */
                    pUSARTHandle->TxLen--;
                }
            }
            else if (pUSARTHandle->TxLen == 0)
            {
                /* Clear TXEIE control bit to disable interrupt request flag from TXE */
                pUSARTHandle->pUSARTx->CR1 &= ~(1 << USART_CR1_TXEIE_SHIFT);
            }
        }
    }

    /********************************** RXNE FLAG **********************************/
    if (USART_GetFlagStatus(pUSARTHandle->pUSARTx, RXNE_flag))
    {
        if (pUSARTHandle->RxStatus == USART_BUSY_IN_RX)
        {
            if (pUSARTHandle->RxLen > 0)
            {
                /* Clear RXNE flag to avoid pending interrupt */
                // USART_ClearFlagStatus(pUSARTHandle->pUSARTx, RXNE_flag);

                /* Check the USART_WordLength item for 9BIT or 8BIT in a frame */
                if (pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
                {

                    /* If parity control is used in buffer */
                    if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
                    {
                        /* if 9BIT, load the DR with 2bytes masking the bits other than first 9 bits */
                        *((uint16 *)pUSARTHandle->pRxBuffer) = (uint16)(pUSARTHandle->pUSARTx->DR & (uint16)0X1FFU);
                        /* Increment the pointer to RX buffer */
                        pUSARTHandle->pRxBuffer++;
                        pUSARTHandle->pRxBuffer++;

                        /* decrement RX buffer length */
                        pUSARTHandle->RxLen -= 2;
                    }
                    else
                    {
                        /* if 8BIT, load the DR with 1bytes masking */
                        *(pUSARTHandle->pRxBuffer) = (uint8)(pUSARTHandle->pUSARTx->DR & (uint8)0XFFU);

                        /* Increment the pointer to RX buffer */
                        pUSARTHandle->pRxBuffer++;

                        /* decrement RX buffer length */
                        pUSARTHandle->RxLen--;
                    }
                }
                else
                {
                    /* If parity control is used in buffer */
                    if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
                    {
                        /* if 8BIT, load the DR with 1bytes masking */
                        *(pUSARTHandle->pRxBuffer) = (uint8)(pUSARTHandle->pUSARTx->DR & (uint8)0XFFU);
                    }
                    else
                    {
                        /* if 7BIT, load the DR with 1bytes masking the bits other than first 8 bits */
                        *(pUSARTHandle->pRxBuffer) = (uint8)(pUSARTHandle->pUSARTx->DR & (uint8)0X7FU);
                    }

                    /* Increment the pointer to RX buffer */
                    pUSARTHandle->pRxBuffer++;

                    /* decrement RX buffer length */
                    pUSARTHandle->RxLen--;
                }
            }
            if (pUSARTHandle->RxLen == 0)
            {
                if (pUSARTHandle->RxStatus == USART_BUSY_IN_RX)
                {
                    /* Clear RXNE flag to avoid pending interrupt */
                    // USART_ClearFlagStatus(pUSARTHandle->pUSARTx, RXNE_flag);

                    /* Clear pointer to RX buffer */
                    pUSARTHandle->pRxBuffer = NULL;

                    /* Clear RX bus state */
                    pUSARTHandle->RxStatus = USART_READY;

                    /* Clear RX buffer length */
                    pUSARTHandle->RxLen = 0;

                    /* Clear RXNEIE to disable RXNE interrupt request from SR register */
                    pUSARTHandle->pUSARTx->CR1 &= ~(1 << USART_CR1_RXNEIE_SHIFT);

                    /* Clear UE to disable USARTx in CR1 */
                    // pUSARTHandle->pUSARTx->CR1 &= ~(1 << USART_CR1_UE_SHIFT);
                }
            }
        }
    }
}
