/******************************************************************************
 * Project Name: LPSPI DRIVER
 * File Name: lpspi.h
 *
 * Description: Implementation of the LPSPI
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex-M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "lpspi.h"

/******************************************************************************
 *   VERSION CHECK
 *****************************************************************************/

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/

/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *****************************************************************************/
/**
 *   @brief      This function enable global clock, and configure functional clock to LPSPI module.
 *
 *   @param[in]  LPSPI_HandleType*          Pointer to LPSPI handler
 *
 *   @return     void                       xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void LPSPI_PeripheralClockConfig(LPSPI_HandleType *pLPSPIHandler)
{
    if (pLPSPIHandler->pLPSPIx == LPSPI0)
    {

        PCC->PCC_LPSPI0 |= (pLPSPIHandler->LPSPI_Config->ClockSource << PCC_PCS_SHIFT);
        PCC->PCC_LPSPI0 |= (1 << PCC_CGC_SHIFT);
    }
    else if (pLPSPIHandler->pLPSPIx == LPSPI1)
    {
        PCC->PCC_LPSPI1 |= (pLPSPIHandler->LPSPI_Config->ClockSource << PCC_PCS_SHIFT);
        PCC->PCC_LPSPI1 |= (1 << PCC_CGC_SHIFT);
    }
    else if (pLPSPIHandler->pLPSPIx == LPSPI2)
    {
        PCC->PCC_LPSPI2 |= (pLPSPIHandler->LPSPI_Config->ClockSource << PCC_PCS_SHIFT);
        PCC->PCC_LPSPI2 |= (1 << PCC_CGC_SHIFT);
    }
}

/**
 *   @brief      This function configure SPI mode, transmition, dataframe, clock signal, chip select to LPSPI module.
 *
 *   @param[in]  LPSPI_HandleType*          Pointer to LPSPI handler
 *
 *   @return     void                       xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void LPSPI_Init(LPSPI_HandleType *pLPSPIHandler)
{
    uint32 temp = 0U;
    /* Setting Clock */
    temp |= pLPSPIHandler->LPSPI_Config->ClockDelayControl;
    temp |= pLPSPIHandler->LPSPI_Config->ClockDivider << LPSPI_CCR_SCKDIV_SHIFT;
    pLPSPIHandler->pLPSPIx->CCR = temp;
    temp = 0U;
    temp |= pLPSPIHandler->LPSPI_Config->ClockPrescaler << LPSPI_TCR_PRESCALE_SHIFT;

    /* Configures Clock Phase and Polarity */
    temp |= pLPSPIHandler->LPSPI_Config->CPHA << LPSPI_TCR_CPHA_SHIFT;
    temp |= pLPSPIHandler->LPSPI_Config->CPOL << LPSPI_TCR_CPOL_SHIFT;

    /* Setting Frame data */
    temp |= pLPSPIHandler->LPSPI_Config->Wordlength << LPSPI_TCR_FRAMESZ_SHIFT;
    temp |= pLPSPIHandler->LPSPI_Config->TransmitOrder << LPSPI_TCR_LSBF_SHIFT;

    /* Configures the peripheral chip select */
    temp |= pLPSPIHandler->LPSPI_Config->ChipSelectControl << LPSPI_TCR_PCS_SHIFT;
    pLPSPIHandler->pLPSPIx->TCR = temp;
    temp = 0U;

    /* Configures SPI mode */
    if (pLPSPIHandler->LPSPI_Config->SPIMode == LPSPI_MASTER_MODE)
    {
        temp |= (1 << LPSPI_CFGR1_NOSTALL_SHIFT);
    }
    temp |= (pLPSPIHandler->LPSPI_Config->SPIMode << LPSPI_CFGR1_MASTER_SHIFT);
    pLPSPIHandler->pLPSPIx->CFGR1 = temp;
    temp = 0U;

    /* Setting Transmit/Receive FIFO */
    temp |= (pLPSPIHandler->LPSPI_Config->RxThreshold << LPSPI_FCR_RXWATER_SHIFT);
    temp |= (pLPSPIHandler->LPSPI_Config->TxThreshold << LPSPI_FCR_TXWATER_SHIFT);
    pLPSPIHandler->pLPSPIx->FCR = temp;

    /* If interrupt is used, then set defailt bus state */
    if (pLPSPIHandler->LPSPI_Config->InterruptControl == LPSPI_IRQ_ENABLE)
    {
        pLPSPIHandler->TxStatus = LPSPI_READY;
        pLPSPIHandler->TxStatus = LPSPI_READY;
    }

    /* Enable LPSPI module */
    pLPSPIHandler->pLPSPIx->CR |= (1U << LPSPI_CR_DBGEN_SHIFT); /* Module enable => MEN = 1 */
    pLPSPIHandler->pLPSPIx->CR |= (1U << LPSPI_CR_MEN_SHIFT);   /* Module enable => MEN = 1 */
}

/**
 *   @brief      This function receive data and copy to buffer with LPSPI module.
 *
 *   @param[in]  LPSPI_HandleType*          Pointer to LPSPI handler
 *   @param[in]  uint8*                     Pointer to RX buffer
 *   @param[in]  uint8*                     Length of the buffer
 *
 *   @return     void                       xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void LPSPI_Receive(LPSPI_HandleType *LPSPI, uint8 *Rxbuffer, uint8 Len)
{
    uint8 i;
    uint16 *u16Data;
    uint32 *u32Data;
    if (Len > 0)
    {
        /* If data frame is less than 9 BIT, we receive 8 bits */
        if (LPSPI->LPSPI_Config->Wordlength < 9)
        {
            for (i = 0; i < Len; i++)
            {
                /* Pulling for RX buffer to be full */
                while (((LPSPI->pLPSPIx->SR >> LPSPI_SR_RDF_SHIFT) & 0X01U) == 0)
                {
                }

                /* Receive data to RX buffer */
                *(Rxbuffer + i) = LPSPI->pLPSPIx->RDR & (uint8)0XFF;
            }
        }
        /* If data frame is less than 16 BIT, we receive 16 bits */
        else if (LPSPI->LPSPI_Config->Wordlength < 17)
        {
            for (i = 0; i < Len; i++)
            {
                /* Pulling for RX buffer to be full */
                while (((LPSPI->pLPSPIx->SR >> LPSPI_SR_RDF_SHIFT) & 0X01U) == 0)
                {
                }

                /* Receive data to RX buffer */
                u16Data = (uint16 *)Rxbuffer;
                *(u16Data + i) = LPSPI->pLPSPIx->RDR & (uint16)0XFFFF;
            }
        }
        /* If data frame is less than or more than 32 BIT, we receive 32 bits */
        else if (LPSPI->LPSPI_Config->Wordlength >= 17)
        {
            for (i = 0; i < Len; i++)
            {
                /* Pulling for RX buffer to be full */
                while (((LPSPI->pLPSPIx->SR >> LPSPI_SR_RDF_SHIFT) & 0X01U) == 0)
                {
                }

                /* Receive data to RX buffer */
                u32Data = (uint32 *)Rxbuffer;
                *(u32Data + i) = LPSPI->pLPSPIx->RDR & (uint32)0XFFFFFFFF;
            }
        }
    }
}

/**
 *   @brief      This function transmit data from buffer with LPSPI module.
 *
 *   @param[in]  LPSPI_HandleType*          Pointer to LPSPI handler
 *   @param[in]  uint8*                     Pointer to TX buffer
 *   @param[in]  uint8*                     Length of the buffer
 *
 *   @return     void                       xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void LPSPI_Transmit(LPSPI_HandleType *LPSPI, uint8 *Txbuffer, uint8 Len)
{
    uint8 i;
    uint16 *u16Data;
    uint32 *u32Data;
    if (Len > 0)
    {
        /* If data frame is less than 9 BIT, we send 8 bits */
        if (LPSPI->LPSPI_Config->Wordlength < 9)
        {
            for (i = 0; i < Len; i++)
            {
                /* Pulling for TX buffer to be empty */
                while (((LPSPI->pLPSPIx->SR >> LPSPI_SR_TDF_SHIFT) & 0X01U) == 0)
                {
                }

                /* Send data to TX buffer */
                LPSPI->pLPSPIx->TDR = (*(Txbuffer + i) & (uint8)0XFF);
            }
        }
        /* If data frame is less than 16 BIT, we send 16 bits */
        else if (LPSPI->LPSPI_Config->Wordlength < 17)
        {
            for (i = 0; i < Len; i++)
            {
                /* Pulling for TX buffer to be empty */
                while (((LPSPI->pLPSPIx->SR >> LPSPI_SR_TDF_SHIFT) & 0X01U) == 0)
                {
                }

                /* Send data to TX buffer */
                u16Data = (uint16 *)Txbuffer;
                LPSPI->pLPSPIx->TDR = (*(u16Data + i) & (uint16)0XFFFF);
                i += 1;
            }
        }
        /* If data frame is less than or more than 32 BIT, we send 32 bits */
        else if (LPSPI->LPSPI_Config->Wordlength >= 17)
        {
            for (i = 0; i < Len; i++)
            {
                /* Pulling for TX buffer to be empty */
                while (((LPSPI->pLPSPIx->SR >> LPSPI_SR_TDF_SHIFT) & 0X01U) == 0)
                {
                }

                /* Send data to TX buffer */
                u32Data = (uint32 *)Txbuffer;
                LPSPI->pLPSPIx->TDR = (*(u32Data + i) & (uint32)0XFFFFFFFF);
                i += 3;
            }
        }
    }
}

/**
 *   @brief      This function setups interrupt transmition with LPSPI module.
 *
 *   @param[in]  LPSPI_HandleType*          Pointer to LPSPI handler
 *   @param[in]  uint8*                     Pointer to TX buffer
 *   @param[in]  uint8*                     Length of the buffer
 *
 *   @return     void                       xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void LPSPI_TransmitIT(LPSPI_HandleType *LPSPI, uint8 *Txbuffer, uint8 Len)
{
    /* Check TX bus state */
    if (LPSPI->TxStatus == LPSPI_READY)
    {
        if (Len > 0)
        {
            LPSPI->pTxBuffer = Txbuffer;

            /* Setup TX bus state */
            LPSPI->TxStatus = LPSPI_BUSY_IN_TX;

            /* Setup TX buffer length */
            LPSPI->TxLen = Len;

            /* Enable Transmit interrupt */
            LPSPI->pLPSPIx->IER |= (1 << LPSPI_IER_TDIE_SHIFT);
            LPSPI->pLPSPIx->IER |= (1 << LPSPI_IER_TCIE_SHIFT);

            /* Enable Transmit */
            if ((LPSPI->pLPSPIx->CR & LPSPI_CR_MEN_SHIFT) == 0)
            {
                LPSPI->pLPSPIx->CR |= LPSPI_CR_MEN_SHIFT;
            }
        }
    }
}

/**
 *   @brief      This function setups interrupt reception with LPSPI module.
 *
 *   @param[in]  LPSPI_HandleType*          Pointer to LPSPI handler
 *   @param[in]  uint8*                     Pointer to TX buffer
 *   @param[in]  uint8*                     Length of the buffer
 *
 *   @return     void                       xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void LPSPI_ReceiveIT(LPSPI_HandleType *LPSPI, uint8 *Rxbuffer, uint8 Len)
{
    /* Check TX bus state */
    if (LPSPI->RxStatus == LPSPI_READY)
    {
        if (Len > 0)
        {
            LPSPI->pRxBuffer = Rxbuffer;

            /* Setup TX bus state */
            LPSPI->RxStatus = LPSPI_BUSY_IN_TX;

            /* Setup TX buffer length */
            LPSPI->RxLen = Len;

            /* Enable Transmit interrupt */
            LPSPI->pLPSPIx->IER |= (1 << LPSPI_IER_REIE_SHIFT);
            LPSPI->pLPSPIx->IER |= (1 << LPSPI_IER_TCIE_SHIFT);

            /* Enable Transmit */
            if ((LPSPI->pLPSPIx->CR & LPSPI_CR_MEN_SHIFT) == 0)
            {
                LPSPI->pLPSPIx->CR |= LPSPI_CR_MEN_SHIFT;
            }
        }
    }
}

/**
 *   @brief      This function function returns status flag of LPSPI module.
 *
 *   @param[in]  LPSPI_TypeDef*             Pointer to typedef structure of LPSPI
 *   @param[in]  uint8                      Position of flag in register
 *
 *   @return     void                       xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
uint8 LPSPI_GetFlagStatus(LPSPI_TypeDef *pLPSPIx, uint8 StatusFlagShift)
{
    uint8 temp;
    temp = (pLPSPIx->SR >> StatusFlagShift) & 0X01U;
    return temp;
}

/**
 *   @brief      This function function clears status flag of LPSPI module.
 *
 *   @param[in]  LPSPI_TypeDef*             Pointer to typedef structure of LPSPI
 *   @param[in]  uint8                      Position of flag in register
 *
 *   @return     void                       xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void LPSPI_ClearFlagStatus(LPSPI_TypeDef *pLPSPIx, uint8 StatusFlagShift)
{
    pLPSPIx->SR |= (1 << StatusFlagShift);
}

/**
 *   @brief      This function handle interrupt status of LPSPI module.
 *
 *   @param[in]  LPSPI_HandleType*          Pointer to LPSPI handler
 *
 *   @return     void                       xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void LPSPI_IRQHandling(LPSPI_HandleType *LPSPI)
{
    uint16 *pu16data = NULL;
    uint32 *pu32data = NULL;
    /* Check interrupt request flag */
    /********************************** TC FLAG *************************************/
    if (LPSPI_GetFlagStatus(LPSPI->pLPSPIx, LPSPI_SR_TCF_SHIFT))
    {
        /* Check TX bus state */
        if (LPSPI->TxStatus == LPSPI_BUSY_IN_TX)
        {
            if (LPSPI->TxLen == 0)
            {
                /* Clear TC flag to avoid pending */
                LPSPI_ClearFlagStatus(LPSPI->pLPSPIx, LPSPI_SR_TCF_SHIFT);
                LPSPI_ClearFlagStatus(LPSPI->pLPSPIx, LPSPI_SR_TDF_SHIFT);

                /* Clear TCIE control bit to disable interrupt request flag from TX */
                if (LPSPI->pLPSPIx->IER & (1 << LPSPI_IER_TCIE_SHIFT))
                    LPSPI->pLPSPIx->IER &= ~(1 << LPSPI_IER_TCIE_SHIFT);

                /* Clear TDIE control bit to disable interrupt request flag from TX */
                if (LPSPI->pLPSPIx->IER & (1 << LPSPI_IER_TDIE_SHIFT))
                    LPSPI->pLPSPIx->IER &= ~(1 << LPSPI_IER_TDIE_SHIFT);

                /* Clear TX buffer */
                LPSPI->pTxBuffer = NULL;

                /* Clear TX status  */
                LPSPI->TxStatus = LPSPI_READY;

                LPSPI->TxLen = 0;
            }
        }
    }

    /********************************** TXE FLAG ************************************/
    if (LPSPI_GetFlagStatus(LPSPI->pLPSPIx, LPSPI_SR_TDF_SHIFT))
    {
        /* Check TX bus state */
        if (LPSPI->TxStatus == LPSPI_BUSY_IN_TX)
        {
            if (LPSPI->TxLen > 0)
            {
                /* If data frame is less than 9 BIT, we send 8 bits */
                if (LPSPI->LPSPI_Config->Wordlength < 9)
                {
                    /* Send data to TX buffer with size of 8 bits */
                    LPSPI->pLPSPIx->TDR = (*(LPSPI->pTxBuffer) & (uint8)0XFF);

                    /* Increment the pointer to TX buffer */
                    LPSPI->pTxBuffer++;

                    /* decrement TX buffer length */
                    LPSPI->TxLen--;
                }
                /* If data frame is less than 16 BIT, we send 16 bits */
                else if (LPSPI->LPSPI_Config->Wordlength < 17)
                {
                    /* Send data to TX buffer with size of 16 bits */
                    pu16data = (uint16 *)LPSPI->pTxBuffer;
                    LPSPI->pLPSPIx->TDR = (*(pu16data) & (uint16)0XFFFF);

                    /* Increment the pointer to TX buffer */
                    LPSPI->pTxBuffer += 2;

                    /* decrement TX buffer length */
                    LPSPI->TxLen -= 2;
                }
                /* If data frame is less than or more than 32 BIT, we send 32 bits */
                else
                {
                    /* Send data to TX buffer with size of 32 bits */
                    pu32data = (uint32 *)LPSPI->pTxBuffer;
                    LPSPI->pLPSPIx->TDR = (*(pu32data) & (uint32)0XFFFFFFFF);

                    /* Increment the pointer to TX buffer */
                    LPSPI->pTxBuffer += 4;

                    /* decrement TX buffer length */
                    LPSPI->TxLen -= 4;
                }
            }
            else if (LPSPI->TxLen == 0)
            {
                LPSPI_ClearFlagStatus(LPSPI->pLPSPIx, LPSPI_SR_TDF_SHIFT);
            }
        }
    }

    /********************************** RXNE FLAG **********************************/
    if (LPSPI_GetFlagStatus(LPSPI->pLPSPIx, LPSPI_SR_RDF_SHIFT))
    {
        /* Check RX bus state */
        if (LPSPI->RxStatus == LPSPI_BUSY_IN_RX)
        {
            if (LPSPI->RxLen > 0)
            {
                /* If data frame is less than 9 BIT, we receive 8 bits */
                if (LPSPI->LPSPI_Config->Wordlength < 9)
                {
                    /* Send data to RX buffer with size of 8 bits */
                    *(LPSPI->pRxBuffer) = (uint8)(LPSPI->pLPSPIx->RDR & (uint8)0XFF);

                    /* Increment the pointer to RX buffer */
                    LPSPI->pRxBuffer++;

                    /* decrement RX buffer length */
                    LPSPI->RxLen--;
                }
                /* If data frame is less than 16 BIT, we receive 16 bits */
                else if (LPSPI->LPSPI_Config->Wordlength < 17)
                {
                    /* Send data to RX buffer with size of 16 bits */
                    *((uint16 *)LPSPI->pRxBuffer) = (uint16)(LPSPI->pLPSPIx->RDR & (uint16)0XFFFF);

                    /* Increment the pointer to RX buffer */
                    LPSPI->pRxBuffer += 2;

                    /* decrement RX buffer length */
                    LPSPI->RxLen -= 2;
                }
                /* If data frame is less than or more than 32 BIT, we receive 32 bits */
                else
                {
                    /* Send data to RX buffer with size of 32 bits */
                    *((uint32 *)LPSPI->pRxBuffer) = (uint32)(LPSPI->pLPSPIx->RDR & (uint32)0XFFFFFFFF);

                    /* Increment the pointer to RX buffer */
                    LPSPI->pRxBuffer += 4;

                    /* decrement RX buffer length */
                    LPSPI->RxLen -= 4;
                }
            }
            if (LPSPI->RxLen == 0)
            {
                if (LPSPI->RxStatus == LPSPI_BUSY_IN_RX)
                {
                    /* Clear pointer to RX buffer */
                    LPSPI->pRxBuffer = NULL;

                    /* Clear RX bus state */
                    LPSPI->RxStatus = LPSPI_READY;

                    /* Clear RX buffer length */
                    LPSPI->RxLen = 0;

                    /* Clear RXNEIE to disable RXNE interrupt request from SR register */
                    LPSPI->pLPSPIx->IER |= (1 << LPSPI_IER_REIE_SHIFT);
                }
            }
        }
    }
}

/*---------------------- End of File ----------------------------------------*/
