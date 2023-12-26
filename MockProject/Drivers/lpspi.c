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
void LPSPI_PeripheralClockConfig(LPSPI_HandleType *pLPSPIHandler)
{
    if (pLPSPIHandler->pLPSPIx == LPSPI0)
    {

        PCC->PCC_LPSPI0 |= (pLPSPIHandler->LPSPI_Config.ClockSource << PCC_PCS_SHIFT);
        PCC->PCC_LPSPI0 |= (1 << PCC_CGC_SHIFT);
    }
    else if (pLPSPIHandler->pLPSPIx == LPSPI1)
    {
        PCC->PCC_LPSPI1 |= (pLPSPIHandler->LPSPI_Config.ClockSource << PCC_PCS_SHIFT);
        PCC->PCC_LPSPI1 |= (1 << PCC_CGC_SHIFT);
    }
    else if (pLPSPIHandler->pLPSPIx == LPSPI2)
    {
        PCC->PCC_LPSPI2 |= (pLPSPIHandler->LPSPI_Config.ClockSource << PCC_PCS_SHIFT);
        PCC->PCC_LPSPI2 |= (1 << PCC_CGC_SHIFT);
    }
}

void LPSPI_Init(LPSPI_HandleType *pLPSPIHandler)
{
    uint32 temp = 0U;
    /* Setting Clock */
    temp |= pLPSPIHandler->LPSPI_Config.ClockDelayControl;
    temp |= pLPSPIHandler->LPSPI_Config.ClockDivider << LPSPI_CCR_SCKDIV_SHIFT;
    pLPSPIHandler->pLPSPIx->CCR = temp;
    temp = 0U;
    temp |= pLPSPIHandler->LPSPI_Config.ClockPrescaler << LPSPI_TCR_PRESCALE_SHIFT;

    /* Configures Clock Phase and Polarity */
    temp |= pLPSPIHandler->LPSPI_Config.CPHA << LPSPI_TCR_CPHA_SHIFT;
    temp |= pLPSPIHandler->LPSPI_Config.CPOL << LPSPI_TCR_CPOL_SHIFT;

    /* Setting Frame data */
    temp |= pLPSPIHandler->LPSPI_Config.Wordlength << LPSPI_TCR_FRAMESZ_SHIFT;
    temp |= pLPSPIHandler->LPSPI_Config.TransmitOrder << LPSPI_TCR_LSBF_SHIFT;

    /* Configures the peripheral chip select */
    temp |= pLPSPIHandler->LPSPI_Config.ChipSelectControl << LPSPI_TCR_PCS_SHIFT;
    pLPSPIHandler->pLPSPIx->TCR = temp;
    temp = 0U;

    /* Configures SPI mode */
    if (pLPSPIHandler->LPSPI_Config.SPIMode == LPSPI_MASTER_MODE)
    {
        temp |= (1 << LPSPI_CFGR1_NOSTALL_SHIFT);
    }
    temp |= (pLPSPIHandler->LPSPI_Config.SPIMode << LPSPI_CFGR1_MASTER_SHIFT);
    pLPSPIHandler->pLPSPIx->CFGR1 = temp;
    temp = 0U;

    /* Setting Transmit/Receive FIFO */
    temp |= (pLPSPIHandler->LPSPI_Config.RxThreshold << LPSPI_FCR_RXWATER_SHIFT);
    temp |= (pLPSPIHandler->LPSPI_Config.TxThreshold << LPSPI_FCR_TXWATER_SHIFT);
    pLPSPIHandler->pLPSPIx->FCR = temp;

    /* Enable LPSPI module */
    pLPSPIHandler->pLPSPIx->CR |= (1U << LPSPI_CR_DBGEN_SHIFT); /* Module enable => MEN = 1 */
    pLPSPIHandler->pLPSPIx->CR |= (1U << LPSPI_CR_MEN_SHIFT);   /* Module enable => MEN = 1 */
}

void LPSPI_ConfigMaster(LPSPI_TypeDef *pLPSPIx)
{

    volatile uint32 temp = 0;

    /* 3. Setting Clock */
    pLPSPIx->CCR |= (1 << LPSPI_CCR_SCKDIV_SHIFT);
    temp |= (1 << LPSPI_TCR_PRESCALE_SHIFT);
    pLPSPIx->CCR |= (4u << LPSPI_CCR_SCKPCS_SHIFT); /*SCK-to-PCS Delay*/
    pLPSPIx->CCR |= (4u << LPSPI_CCR_PCSSCK_SHIFT); /*PCS-to-SCK Delay*/

    /* 4. Configures Clock Phase and Polarity */
    temp |= (0 << LPSPI_TCR_CPOL_SHIFT);
    temp |= (0 << LPSPI_TCR_CPHA_SHIFT);

    /* 5. Setting Frame data */
    temp |= (15 << LPSPI_TCR_FRAMESZ_SHIFT);
    temp |= (0 << LPSPI_TCR_LSBF_SHIFT);

    /* 6. Configures the peripheral chip select */
    temp |= (3 << LPSPI_TCR_PCS_SHIFT);

    pLPSPIx->TCR = temp;
    temp = 0U;

    /* 7. Setting Transmit/Receive FIFO */
    temp |= (0 << LPSPI_FCR_RXWATER_SHIFT);
    temp |= (3 << LPSPI_FCR_TXWATER_SHIFT);

    pLPSPIx->FCR |= temp;
    temp = 0U;

    temp |= (1 << LPSPI_CFGR1_NOSTALL_SHIFT);

    /* 8. Configures LPSPI mode */
    temp |= (1 << LPSPI_CFGR1_MASTER_SHIFT);

    pLPSPIx->CFGR1 |= temp;
    temp = 0U;

    /* 9. Enable LPSPI module */
    pLPSPIx->CR |= (1U << LPSPI_CR_DBGEN_SHIFT); /*Module enable => MEN = 1*/
    pLPSPIx->CR |= (1U << LPSPI_CR_MEN_SHIFT);   /*Module enable => MEN = 1*/
}

void LPSPI_ConfigSlave(LPSPI_TypeDef *pLPSPIx)
{

    volatile uint32 temp = 0;

    /* 3. Setting Clock */
    pLPSPIx->CCR |= (1 << LPSPI_CCR_SCKDIV_SHIFT);
    temp |= (1 << LPSPI_TCR_PRESCALE_SHIFT);
    pLPSPIx->CCR |= (4u << LPSPI_CCR_SCKPCS_SHIFT); /*SCK-to-PCS Delay*/
    pLPSPIx->CCR |= (4u << LPSPI_CCR_PCSSCK_SHIFT); /*PCS-to-SCK Delay*/

    /* 4. Configures Clock Phase and Polarity */
    temp |= (0 << LPSPI_TCR_CPOL_SHIFT);
    temp |= (0 << LPSPI_TCR_CPHA_SHIFT);

    /* 5. Setting Frame data */
    temp |= (15 << LPSPI_TCR_FRAMESZ_SHIFT);
    temp |= (0 << LPSPI_TCR_LSBF_SHIFT);

    /* 6. Configures the peripheral chip select */
    temp |= (3 << LPSPI_TCR_PCS_SHIFT);

    pLPSPIx->TCR = temp;
    temp = 0U;

    /* 7. Setting Transmit/Receive FIFO */
    temp |= (0 << LPSPI_FCR_RXWATER_SHIFT);
    temp |= (3 << LPSPI_FCR_TXWATER_SHIFT);

    pLPSPIx->FCR |= temp;
    temp = 0U;

    // temp |= (1 << LPSPI_CFGR1_NOSTALL_SHIFT);

    /* 8. Configures LPSPI mode */
    // temp |= (1 << LPSPI_CFGR1_MASTER_SHIFT);

    pLPSPIx->CFGR1 |= temp;
    temp = 0U;

    /* 9. Enable LPSPI module */
    pLPSPIx->CR |= (1U << LPSPI_CR_DBGEN_SHIFT); /*Module enable => MEN = 1*/
    pLPSPIx->CR |= (1U << LPSPI_CR_MEN_SHIFT);   /*Module enable => MEN = 1*/
}

void LPSPI_Transmit(LPSPI_TypeDef *pLPSPIx, uint16 sendData)
{
    while (!(pLPSPIx->SR & (1U << 0)))
    {
    }

    pLPSPIx->TDR = sendData; /* Transmit data*/
    pLPSPIx->SR |= (1U << 0);
}

uint16 LPSPI_Receive(LPSPI_TypeDef *pLPSPIx)
{
    while (!(pLPSPIx->SR & (1U << 1)))
    {
    } /*Wait until the buffer is empty*/

    uint16 data = pLPSPIx->RDR;
    pLPSPIx->SR |= (1U << 1);
    return data;
}

/*---------------------- End of File ----------------------------------------*/
