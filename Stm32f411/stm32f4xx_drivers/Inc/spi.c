/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "spi.h"
#include "stm32f411xx.h"

/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/
void SPI_PeriClockControl(SPI_Type *pSPIx, uint8 EnorDis)
{
    if (EnorDis == ENABLE)
    {
        if (pSPIx == SPI1)
            SPI1_CLK_EN();
        else if (pSPIx == SPI2)
            SPI2_CLK_EN();
        else if (pSPIx == SPI3)
            SPI3_CLK_EN();
        else if (pSPIx == SPI4)
            SPI4_CLK_EN();
        else if (pSPIx == SPI5)
            SPI5_CLK_EN();
    }
    else if (EnorDis == DISABLE)
    {
        if (pSPIx == SPI1)
            SPI1_CLK_DIS();
        else if (pSPIx == SPI2)
            SPI2_CLK_DIS();
        else if (pSPIx == SPI3)
            SPI3_CLK_DIS();
        else if (pSPIx == SPI4)
            SPI4_CLK_DIS();
        else if (pSPIx == SPI5)
            SPI5_CLK_DIS();
    }
}

void SPI_Init(SPI_Handle_Type *pSPIHandle)
{
    uint32 tempreg = 0;
    /* Configure first the SPI control register */

    /* 1. Master selection */
    if (pSPIHandle->SPIConfig.DeviceMode == SPI_DEVICE_MODE_MASTER)
    {
        tempreg |= (pSPIHandle->SPIConfig.DeviceMode << SPI_CR1_MSTR_SHIFT);
        tempreg |= (1 << SPI_CR1_SSI_SHIFT);
    }
    else if (pSPIHandle->SPIConfig.DeviceMode == SPI_DEVICE_MODE_SLAVE)
    {
        tempreg |= (pSPIHandle->SPIConfig.DeviceMode << SPI_CR1_MSTR_SHIFT);
    }

    /* 2. Software slave management */
    tempreg |= (pSPIHandle->SPIConfig.SSM << SPI_CR1_SSM_SHIFT);

    /* 3. Baud rate control */
    tempreg |= (pSPIHandle->SPIConfig.SclkSpeed << SPI_CR1_BR_SHIFT);

    /* 4. CPOL: Clock polarity */
    tempreg |= (pSPIHandle->SPIConfig.CPOL << SPI_CR1_CPOL_SHIFT);

    /* 5. CPHA: Clock phase */
    tempreg |= (pSPIHandle->SPIConfig.CPHA << SPI_CR1_CPHA_SHIFT);

    /* 6. Master selection */
    if (pSPIHandle->SPIConfig.BusConfig == SPI_BUS_CONFIG_FD)
    {
        /* 2-line unidirectional data, FULL-DUPLEX */
        tempreg &= ~(1 << SPI_CR1_BIDIMODE_SHIFT);

        /* Receive only */
        tempreg &= ~(1 << SPI_CR1_RXONLY_SHIFT);
    }
    else if (pSPIHandle->SPIConfig.BusConfig == SPI_BUS_CONFIG_HD)
    {
        /* 1-line bidirectional data , HALF-DUPLEX */
        tempreg |= (1 << SPI_CR1_BIDIMODE_SHIFT);

        /* receive-only mode */
        // tempreg |= (1 << SPI_CR1_RXONLY_SHIFT);
    }
    else if (pSPIHandle->SPIConfig.BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
    {
        /* 2-line unidirectional data, SIMPLEX */
        tempreg &= ~(1 << SPI_CR1_BIDIMODE_SHIFT);

        /* Receive only */
        tempreg |= (1 << SPI_CR1_RXONLY_SHIFT);
    }

    /* 7. Data frame format */
    tempreg |= (pSPIHandle->SPIConfig.DFF << SPI_CR1_RXONLY_SHIFT);

    /* 8. Enable SPI */
    tempreg |= (1 << SPI_CR1_SPE_SHIFT);

    pSPIHandle->pSPIx->CR1 = tempreg;
}

void SPI_Write(SPI_Handle_Type *pSPIHandle, uint8 *pTxBuffer, uint32 Len)
{
    uint8 *p_u8data;
    uint16 *p_u16data;
    uint32 i;

    /* Check if buffer length to read is not 0 */
    if (Len != 0)
    {
        /* Loop over until "Len" number of bytes are transferred */
        for (i = 0; i < Len; i++)
        {
            /* Implement the code to wait until TXE flag is set in the SR */
            while (!SPI_GetFlagStatus(pSPIHandle->pSPIx, SPI_TXE_flag))
                ;

            /* Check the SPI_WordLength item for 9BIT or 8BIT in a frame */
            if (pSPIHandle->SPIConfig.DFF == SPI_DFF_16BITS)
            {
                /* if 16BIT, load the DR with 2bytes masking */
                p_u16data = (uint16 *)pTxBuffer;
                pSPIHandle->pSPIx->DR = (*(p_u16data + i) & (uint16)0XFFFF);
            }
            else
            {
                /* if 8BIT, load the DR with 1byte masking */
                p_u8data = pTxBuffer;
                pSPIHandle->pSPIx->DR |= (*(p_u8data + i) & (uint8)0XFF);
            }
        }
    }
}

void SPI_Read(SPI_Handle_Type *pSPIHandle, uint8 *pRxBuffer, uint32 Len)
{
    uint8 *p_u8data;
    uint16 *p_u16data;
    uint32 i;

    /* Check if buffer length to read is not 0 */
    if (Len != 0)
    {
        for (i = 0; i < Len; i++)
        {
            // Implement the code to wait until TXE flag is set in the SR
            while (!SPI_GetFlagStatus(pSPIHandle->pSPIx, SPI_RXNE_flag))
                ;

            // Check the SPI_WordLength item for 9BIT or 8BIT in a frame
            if (pSPIHandle->SPIConfig.DFF == SPI_DFF_16BITS)
            {
                // if 9BIT, load the DR with 2bytes masking the bits other than first 9 bits
                p_u16data = (uint16 *)pRxBuffer;
                *(p_u16data + i) = (uint16)(pSPIHandle->pSPIx->DR & (uint16)0XFFFFU);
            }
            else
            {
                // This is 8bit data receive
                p_u8data = pRxBuffer;
                *(p_u8data + i) = (uint8)(pSPIHandle->pSPIx->DR & (uint8)0XFFU);
            }
        }
    }
}

uint8 SPI_GetFlagStatus(SPI_Type *pSPIx, uint8 StatusFlagShift)
{
    uint8 temp;
    temp = (pSPIx->SR >> StatusFlagShift) & 0X01U;
    return temp;
}
