

#ifndef CONFIG_H_
#define CONFIG_H_

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "S32K144xx.h"
#include "lpspi.h"
#include "port.h"
#include "lpit.h"
#include "clock.h"
#include "lpuart.h"
#include "nvic.h"
#include "adc.h"

/******************************************************************************
 *  LPUART CONFIGURATION
 *****************************************************************************/
/**
 * @brief    Declare params for LPUART2 configuration
 */
LPUART_ConfigType lpuart2_ConfigType =
    {
        /* @ClockOption: Peripheral Clock Source to LPUART module */
        LPUART_FIRCDIV2_CLK,

        /* @Oversamplingratio: Oversampling ratio */
        LPUART_BAUD_OSR(16U),

        /* @BaudrateDivisor: Baudrate Modulo Divisor */
        156U,

        /* @StopBitConfig: Stop bit: 1 or 2 stop bits */
        LPUART_ONEBIT_STOP,

        /* @Dataframe: 9-Bit or 8-Bit Mode Select */
        LPUART_8BIT_DATA,

        /* @ParityOption: Parity Enable */
        LPUART_DISABLE_PARITY,

        /* @InterruptOption: Interrupt control option */
        LPUART_IRQ_ENABLE};

/**
 * @brief    Declare params for LPUART2 hanlder
 */
LPUART_HandleType lpuart2 =
    {
        /* Pointer to LPUARTx module */
        LPUART2,

        /* LPUART configuration */
        &lpuart2_ConfigType,

        /* Pointer to TX buffer */
        NULL_PTR,

        /* Pointer to RX buffer */
        NULL_PTR,

        /* @Busstate: Status of TX bus */
        LPUART_READY,

        /* @Busstate: Status of RX bus */
        LPUART_READY,

        /* TX buffer length */
        0U,

        /* RX buffer length */
        0U};

/******************************************************************************
 *  LPIT CONFIGURATION
 *****************************************************************************/
/**
 * @brief    Declare params for LPIT configuration
 */
LPIT_ConfigType lpit_ConfigType =
    {
        /* @ClockOption: Peripheral Clock Source to LPIT module */
        LPIT_LPO128_CLK,

        /* Reload value of channels */
        {128000U},

        /* @ControlOption: Module Control Status: DBG_EN, DOZE_EN, SW_RST, M_CEN */
        LPIT_DEBUG_STOP | LPIT_DOZEN_STOP | LPIT_MODULE_ENABLE,

        /* @ModeOption: Timer Operation Mode */
        LPIT_32BIT_PERIODIC_MODE,

        /* @InterruptOption: Interrupt enable */
        LPIT_INTERRUPT_ENABLE,

        /* @ChannelOption: LPIT_CHANNELx */
        LPIT_CHANNEL0};

/**
 * @brief    Declare params for LPIT hanlder
 */
LPIT_HandleType lpit =
    {
        /* Pointer to LPITx module */
        LPIT,

        /* LPIT configuration */
        &lpit_ConfigType};

/******************************************************************************
 *  LPSPI CONFIGURATION
 *****************************************************************************/
/**
 * @brief    Declare params for LPSPI1 configuration
 */
LPSPI_ConfigType lpspi1_ConfigType =
    {
        /* @SPIModeOption: SPI mode */
        LPSPI_MASTER_MODE,

        /* @SPIClockSource: Peripheral Clock Source to LPSPI module */
        LPSPI_SPLLDIV2_CLK,

        /* @SPIClockDivider: Clock divider */
        LPSPI_CLKDIV(2),

        /* @SPIClockPrescaler: Clock prescaler */
        LPSPI_PRESCALE_DIV4,

        /* @SPIClockDelayControl: Clock delay between SCK and PCS */
        LPSPI_SCK2PCS_DELAY(3) | LPSPI_PCS2SCK_DELAY(3),

        /* @SPICPOL: Clock polarity: IDLE state of CLK */
        LPSPI_CPOL_LOW,

        /* @SPICPHA: Clock phase: Sampling at leading edge of SCK */
        LPSPI_CPHA_CAPTURE_FIRST,

        /* @SPIChipSelectControl: Select supported pin as PCS */
        LPSPI_PCS_PIN3,

        /* @SPITransmitOrder: Transmit LSB or MSB first */
        LPSPI_MSB_FIRST,

        /* Length of dataframe: 8, 16, 32, more will be divided in multiple words */
        15U,

        /* @SPIRxThreshold: Threshhold to indicate RX buffer full */
        LPSPI_RX_THRESHOLD(0),

        /* @SPITxThreshold: Threshhold to indicate TX buffer empty */
        LPSPI_TX_THRESHOLD(3),

        /* @SPIInterruptControl: Interrupt control option */
        LPSPI_IRQ_ENABLE};

/**
 * @brief    Declare params for LPSPI1 hanlder
 */
LPSPI_HandleType lpspi1 =
    {
        /* Pointer to LPSPIx module */
        LPSPI1,

        /* LPSPI configuration */
        &lpspi1_ConfigType,

        /* Pointer to TX buffer */
        NULL_PTR,

        /* Pointer to RX buffer */
        NULL_PTR,

        /* @Busstate: Status of TX bus */
        LPSPI_READY,

        /* @Busstate: Status of RX bus */
        LPSPI_READY,

        /* TX buffer length */
        0U,

        /* RX buffer length */
        0U};

/******************************************************************************
 *  ADC CONFIGURATION
 *****************************************************************************/
/**
 * @brief    Declare params for ADC configuration
 */
ADC_ConfigType adc_ConfigType =
    {
        /* @ADCClockSource: Peripheral Clock Source to ADC module */
        ADC_FIRCDIV2_CLK,

        /* @ADCClockDivider: Clock divider */
        ADC_CLKDIV_BY4,

        /* @ADCResolution: Resolution of ADC conversion output */
        ADC_12BIT_CONVERSION,

        /* Speed of ADC conversion: number of cycles */
        5U,
			
        /* @ADCADCMode: Operation mode: continue/one-shot */
        ADC_MODE_ONESHOT,

        /* @ADCReferSource: Reference voltage source */
        ADC_DEFAULT_REF,

        /* @ADCTriggerSource: Hardware trigger or Software trigger */
        ADC_SOFTWARE_TRIG,

        /* @ADCInterruptControl: Interrupt enable */
        ADC_INTERRUPT_DISABLE,

        /* Conversion input channel: 63 internal and external input channels */
        {12U},

        /* Number of Conversion channel: SCA - SCP */
        1U};

/**
 * @brief    Declare params for ADC0 handler
 */
ADC_HandleType adc0 =
    {
        /* Pointer to LPITx module */
        ADC0,

        /* LPIT configuration */
        &adc_ConfigType};

#endif /* CONFIG_H_ */
