/******************************************************************************
 * Project Name:
 * File Name:   main.c
 *
 * Description: Implementation of a LPSPI assignment
 *
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex-M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "S32K144xx.h"
#include "lpspi.h"
#include "port.h"
#include "clock.h"
#include "nvic.h"
#include "lpit.h"
#include "lpuart.h"
#include "stdio.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/

/******************************************************************************
 *  GLOBAL VARIABLE
 *****************************************************************************/
/**
* @brief  This handler contain configuration parameters for LPIT modules
*/
LPIT_HandleType lpit;

/**
* @brief  This handler contain configuration parameters for LPUART1 modules
*/
LPUART_HandleType lpuart1;

/**
* @brief  This handler contain configuration parameters for LPSPI0 modules
*/
LPSPI_HandleType lpspi0;

/**
* @brief  This handler contain configuration parameters for LPSPI2 modules
*/
LPSPI_HandleType lpspi2;

/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *****************************************************************************/
void LPIT0_Ch0_IRQHandler(void);

/******************************************************************************
 *  MAIN FUNCTION
 *****************************************************************************/

int main(void)
{
	/*---------------------------------------------------------Clock Config ------------------------------------------------------------*/
	
    /* SOSC config: 8MHz; DIVIDER1 = 8MHz; DIVIDER2 = 8MHz, RANGE = 3 */
    SOSC_ClockEnable(DIV1_BY_1, DIV1_BY_1, RANGE_MEDIUM_FREQUENCY, REFER_INTERNAL);

    /* SIRC config: 8MHz; DIVIDER1 = 8MHz; DIVIDER2 = 8MHz, RANGE = 1 */
    SIRC_ClockEnable(DIV1_BY_1, DIV1_BY_1, 1);

    /* FIRC config: 48MHz; DIVIDER1 = 24MHz; DIVIDER2 = 24MHz */
    FIRC_ClockEnable(DIV1_BY_2, DIV1_BY_2);

	/*--------------------------------------------------------PORT module---------------------------------------------------------------*/
	
    /* Enable clock at PORTx */
    PORT_PeripheralClockConfig(PORTB);
    PORT_PeripheralClockConfig(PORTC);
    PORT_PeripheralClockConfig(PORTD);

	/*--------------------------------------------------------LPSPI0 Config ------------------------------------------------------------*/
	
    /* Configure LPSPI0 module for MASTER */
    lpspi0.pLPSPIx = LPSPI0;
    /* Configure SPI master or slave */
    lpspi0.LPSPI_Config.SPIMode = LPSPI_MASTER_MODE;
    /* Configure Clock setting */
    lpspi0.LPSPI_Config.ClockPrescaler = LPSPI_PRESCALE_DIV4;
    lpspi0.LPSPI_Config.ClockSource = LPSPI_FIRCDIV2_CLK;
    lpspi0.LPSPI_Config.ClockDivider = LPSPI_CLKDIV(6);
    lpspi0.LPSPI_Config.ClockDelayControl = LPSPI_SCK2PCS_DELAY(5) | LPSPI_PCS2SCK_DELAY(5);
    /* Configure SPI Signal */
    lpspi0.LPSPI_Config.CPHA = LPSPI_CPHA_CAPTURE_FIRST;
    lpspi0.LPSPI_Config.CPOL = LPSPI_CPOL_LOW;
    lpspi0.LPSPI_Config.TransmitOrder = LPSPI_MSB_FIRST;
    lpspi0.LPSPI_Config.ChipSelectControl = LPSPI_PCS_PIN0;
    /* Configure data frame */
    lpspi0.LPSPI_Config.Wordlength = 9U;
    /* Configure data buffer detection */
    lpspi0.LPSPI_Config.RxThreshold = LPSPI_RX_THRESHOLD(0);
    lpspi0.LPSPI_Config.TxThreshold = LPSPI_TX_THRESHOLD(0);

    PORT_Pin_Alt_Config(PORTB, 1, ALT_FUNC(3)); 	/* LPSPI0_SOUT */
    PORT_Pin_Alt_Config(PORTB, 2, ALT_FUNC(3)); 	/* LPSPI0_SCK */
    PORT_Pin_Alt_Config(PORTB, 3, ALT_FUNC(3)); 	/* LPSPI0_SIN */
    PORT_Pin_Alt_Config(PORTB, 0, ALT_FUNC(3)); 	/* LPSPI0_PCS0 */
    LPSPI_PeripheralClockConfig(&lpspi0);
    LPSPI_Init(&lpspi0);
	
	/*--------------------------------------------------------LPSPI2 Config ------------------------------------------------------------*/
	
    /* Configure LPSPI2 module for SLAVE */
    lpspi2.pLPSPIx = LPSPI2;
    /* Configure SPI master or slave */
    lpspi2.LPSPI_Config.SPIMode = LPSPI_SLAVE_MODE;
    /* Clock setting */
    lpspi2.LPSPI_Config.ClockPrescaler = LPSPI_PRESCALE_DIV4;
    lpspi2.LPSPI_Config.ClockSource = LPSPI_FIRCDIV2_CLK;
    lpspi2.LPSPI_Config.ClockDivider = LPSPI_CLKDIV(6);
    lpspi2.LPSPI_Config.ClockDelayControl = LPSPI_SCK2PCS_DELAY(5) | LPSPI_PCS2SCK_DELAY(5);
    /* Configure SPI Signal */
    lpspi2.LPSPI_Config.CPHA = LPSPI_CPHA_CAPTURE_FIRST;
    lpspi2.LPSPI_Config.CPOL = LPSPI_CPOL_LOW;
    lpspi2.LPSPI_Config.TransmitOrder = LPSPI_MSB_FIRST;
    lpspi2.LPSPI_Config.ChipSelectControl = LPSPI_PCS_PIN0;
    /* Configure data frame */
    lpspi2.LPSPI_Config.Wordlength = 9U;
    /* Configure data buffer detection */
    lpspi2.LPSPI_Config.RxThreshold = LPSPI_RX_THRESHOLD(0);
    lpspi2.LPSPI_Config.TxThreshold = LPSPI_TX_THRESHOLD(0);

    PORT_Pin_Alt_Config(PORTC, 1, ALT_FUNC(3)); 	/* LPSPI2_SOUT */
    PORT_Pin_Alt_Config(PORTC, 0, ALT_FUNC(3)); 	/* LPSPI2_SIN */
    PORT_Pin_Alt_Config(PORTC, 15, ALT_FUNC(3)); 	/* LPSPI2_SCK */
    PORT_Pin_Alt_Config(PORTC, 14, ALT_FUNC(3)); 	/* LPSPI2_PCS0 */
    LPSPI_PeripheralClockConfig(&lpspi2);
    LPSPI_Init(&lpspi2);
		
	/*-------------------------------------------------------LPUART2 Config ------------------------------------------------------------*/
	
    /* Configure LPUART1 module */
    lpuart1.pLPUARTx = LPUART1;
    /* Clock source setting */
    lpuart1.LPUART_Config.ClockSource = LPUART_SOSCDIV2_CLK;
    /* Baudrate setting */
    lpuart1.LPUART_Config.OSR = LPUART_BAUD_OSR(16U);
    lpuart1.LPUART_Config.SBR = 52U;
    /* Frame setting */
    lpuart1.LPUART_Config.NoStopBits = LPUART_ONEBIT_STOP;
    lpuart1.LPUART_Config.ParityControl = LPUART_DISABLE_PARITY;
    lpuart1.LPUART_Config.WordLength = LPUART_8BIT_DATA;

    PORT_Pin_Alt_Config(PORTC, 6, ALT_FUNC(2)); 	/* LPUART1_RX */
    PORT_Pin_Alt_Config(PORTC, 7, ALT_FUNC(2)); 	/* LPUART1_TX */
    LPUART_PeripheralClockConfig(&lpuart1);
    LPUART_Init(&lpuart1);
		
	/*-------------------------------------------------------LPIT TIMER Config ---------------------------------------------------------*/
	
    /* Configure LPIT timer at channel 0 */
    lpit.pLPITx = LPIT;
    /* Timer clock setting */
    lpit.LPIT_Config.ClockSource = LPIT_LPO128_CLK;
    lpit.LPIT_Config.ReloadValue[0] = 128000U;
    /* Timer mode operation */
    lpit.LPIT_Config.Status = LPIT_DEBUG_STOP | LPIT_DOZEN_STOP | LPIT_MODULE_ENABLE;
    lpit.LPIT_Config.OpMode = LPIT_32BIT_PERIODIC_MODE;
    lpit.LPIT_Config.InterruptControl = LPIT_INTERRUPT_ENABLE;
    /* Timer channels */
    lpit.LPIT_Config.Channel = LPIT_CHANNEL0;

    LPIT_PeripheralClockConfig(&lpit);
    LPIT_Init(&lpit);
    LPIT_StartTimer(&lpit);
		
	/*--------------------------------------------------------NVIC module---------------------------------------------------------------*/

    /* Configure NVIC */
    Interrupt_Enable(LPIT_CH0_IRQ_ID, 15);
		
		
    while (1)
    {
    }

    return 0;
}


void LPIT0_Ch0_IRQHandler(void)
{
    /* Check timer flag channel 0 */
    if (LPIT->MSR & (uint32)LPIT_CHANNEL0)
    {
        LPIT->MSR |= (uint32)LPIT_CHANNEL0; /* Clear flag */

        uint8 u8StringLen = 13U;
        uint8 pTransmit[14] = "Hello World\r\n";
        uint8 pRecieve[14] = {0};
        uint8 i;
        /* Copy data from transmit buffer to receive buffer using LPSPI0 and LPSPI2 */
        for (i = 0; i < u8StringLen; i++)
        {
            /* Copy each character */
            LPSPI_Transmit(&lpspi0, &pTransmit[i], 1U);
            LPSPI_Receive(&lpspi2, &pRecieve[i], 1U);
        }
        /* Print HollaWorld over LPUART1 */
        LPUART_TransmitString(&lpuart1, pRecieve);
    }
}

