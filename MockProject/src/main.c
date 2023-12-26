/******************************************************************************
 * Project Name:
 * File Name:   main.c
 *
 * Description: Implementation of a LPSPI
 *
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex-M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "sevenseg.h"
#include "Common_S32K144.h"
#include "lpspi.h"
#include "port.h"
#include "lpit.h"
#include "clock.h"
#include "lpuart.h"
#include "nvic.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
#define DISPLAY_TIME (uint8)(1 << 0)
#define DISPLAY_CLOCK (uint8)(1 << 1)

/******************************************************************************
 *  GLOBAL VARIABLE
 *****************************************************************************/
volatile uint8 u8Flag;
volatile uint8 u8Date;
volatile uint8 u8Month;
volatile uint16 u16Year;
volatile uint8 u8Hour;
volatile uint8 u8Minute;
volatile uint8 u8Second;
volatile uint8 Date[8] = {'0', '1' + 128U, '0', '1' + 128U, '1', '9', '7', '1'};
volatile uint8 Time[8] = {0};
Lpuart_HandleType lpuart2;
LPIT_HandleType lpit;
LPSPI_HandleType lpspi1;

/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *****************************************************************************/
void LPIT0_Ch0_IRQHandler(void);
void LPUART2_RxTx_IRQHandler(void);

/******************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *****************************************************************************/
uint16 STRLEN(uint8 *string);
void DateUpdate(void);
void TimeUpdate(void);

/******************************************************************************
 *  MAIN FUNCTION
 *****************************************************************************/

int main(void)
{
    uint8 hello[] = "xinchao\r\n";
    uint8 holla[8] = {0};
    u8Flag = 0U;
    u8Date = 0U;
    u8Month = 0U;
    u16Year = 0U;
    u8Hour = 0U;
    u8Minute = 0U;
    u8Second = 0U;

    /* SOSC config: 8MHz; DIVIDER1 = 8MHz; DIVIDER2 = 8MHz, RANGE = 3 */
    SOSC_ClockEnable(DIV1_BY_1, DIV1_BY_1, RANGE_MEDIUM_FREQUENCY, REFER_INTERNAL);

    /* SIRC config: 8MHz; DIVIDER1 = 8MHz; DIVIDER2 = 8MHz, RANGE = 1 */
    SIRC_ClockEnable(DIV1_BY_1, DIV1_BY_1, 1);

    /* FIRC config: 48MHz; DIVIDER1 = 24MHz; DIVIDER2 = 24MHz */
    FIRC_ClockEnable(DIV1_BY_2, DIV1_BY_2);

    /* Enable clock at PORTx */
    ClockEnable(PORTA_e);
    ClockEnable(PORTB_e);
    ClockEnable(PORTD_e);

    /* Configure LPSPI module */
    PORT_Pin_Alt_Config(PORTB, 16, ALT_FUNC(3)); /* LPSPI1_SOUT */
    PORT_Pin_Alt_Config(PORTB, 14, ALT_FUNC(3)); /* LPSPI1_SCK */
    PORT_Pin_Alt_Config(PORTB, 15, ALT_FUNC(3)); /* LPSPI1_SIN */
    PORT_Pin_Alt_Config(PORTB, 17, ALT_FUNC(3)); /* LPSPI1_PCS3 */

    lpspi1.pLPSPIx = LPSPI1;
    lpspi1.LPSPI_Config.SPIMode = LPSPI_MASTER_MODE;
    lpspi1.LPSPI_Config.ClockSource = LPSPI_FIRCDIV2_CLK;
    lpspi1.LPSPI_Config.ClockDivider = LPSPI_CLKDIV(2);
    lpspi1.LPSPI_Config.ClockDelayControl = LPSPI_SCK2PCS_DELAY(5) | LPSPI_PCS2SCK_DELAY(5);
    lpspi1.LPSPI_Config.ChipSelectControl = LPSPI_PCS_PIN3;
    lpspi1.LPSPI_Config.ClockPrescaler = LPSPI_PRESCALE_DIV4;
    lpspi1.LPSPI_Config.CPHA = LPSPI_CPHA_CAPTURE_FIRST;
    lpspi1.LPSPI_Config.CPOL = LPSPI_CPOL_LOW;
    lpspi1.LPSPI_Config.Wordlength = 16U;
    lpspi1.LPSPI_Config.TransmitOrder = LPSPI_MSB_FIRST;
    lpspi1.LPSPI_Config.RxThreshold = LPSPI_RX_THRESHOLD(0);
    lpspi1.LPSPI_Config.TxThreshold = LPSPI_TX_THRESHOLD(3);

    LPSPI_PeripheralClockConfig(&lpspi1);
    LPSPI_Init(&lpspi1);

    /* Configure LPUART2 module */
    PORT_Pin_Alt_Config(PORTA, 9, ALT_FUNC(2)); /* LPUART2_TX */
    PORT_Pin_Alt_Config(PORTA, 8, ALT_FUNC(2)); /* LPUART2_RX */

    lpuart2.pLPUARTx = LPUART2;
    lpuart2.LPUART_Config.ClockSource = LPUART_SOSCDIV2_CLK;
    lpuart2.LPUART_Config.NoStopBits = LPUART_ONEBIT_STOP;
    lpuart2.LPUART_Config.ParityControl = LPUART_DISABLE_PARITY;
    lpuart2.LPUART_Config.WordLength = LPUART_8BIT_DATA;
    lpuart2.LPUART_Config.OSR = LPUART_BAUD_OSR(16U);
    lpuart2.LPUART_Config.SBR = 52U;

    LPUART_PeripheralClockConfig(&lpuart2);
    LPUART_Init(&lpuart2);

    /* Configure LPIT timer at channel 0 */
    lpit.pLPITx = LPIT;
    lpit.LPIT_Config.Channel = LPIT_CHANNEL0;
    lpit.LPIT_Config.ClockSource = LPIT_LPO128_CLK;
    lpit.LPIT_Config.Status = LPIT_DEBUG_STOP | LPIT_DOZEN_STOP | LPIT_MODULE_ENABLE;
    lpit.LPIT_Config.OpMode = LPIT_32BIT_PERIODIC_MODE;
    lpit.LPIT_Config.ReloadValue[0] = 128000U;
    lpit.LPIT_Config.InterruptControl = LPIT_INTERRUPT_ENABLE;

    LPIT_PeripheralClockConfig(&lpit);
    LPIT_Init(&lpit);
    LPIT_StartTimer(&lpit);

    /* Configure NVIC */
    Interrupt_Enable(LPIT_CH0_IRQ_ID, 15);
    Interrupt_Enable(LPUART2_IRQ_ID, 15);

    /* Configure 7-Segment LED module */
    SevenSeg_Init();
    SevenSeg_PrintString(Date, STRLEN(Date));
    //    SevenSeg_ClearDisplay();
    LPUART_ReceiveIT(&lpuart2, holla, sizeof(holla));

    while (1)
    {
        if (u8Flag)
        {
            if (u8Flag & DISPLAY_TIME)
            {
                SevenSeg_PrintString(Time, STRLEN(Time));
                // LPUART_TransmitString(&lpuart2, hello);
                LPUART_TransmitIT(&lpuart2, hello, STRLEN(hello));
                u8Flag &= ~DISPLAY_TIME;
            }
        }
    }

    return 0;
}

uint16 STRLEN(uint8 *string)
{
    uint16 count = 0U;
    while (string[count] != '\0')
    {
        count++;
    }
    return count;
}

void DateUpdate(void)
{
    uint8 i;
    uint16 temp;
    /* Format date */
    Date[0] = u8Date / 10 + 48U;
    Date[1] = u8Date % 10 + 176U;

    /* Format month */
    Date[2] = u8Month / 10 + 48U;
    Date[3] = u8Month % 10 + 176U;

    /* Format year */
    temp = u16Year;
    for (i = 0; i < 4; i++)
    {
        Date[7 - i] = temp % 10 + 48U;
        temp /= 10;
    }
}

void TimeUpdate(void)
{
    /* Update time */
    u8Second += 1;
    if (u8Second == 60)
    {
        u8Second = 0;
        u8Minute += 1;
    }
    if (u8Minute == 60)
    {
        u8Minute = 0;
        u8Hour += 1;
    }
    if (u8Hour == 24)
    {
        u8Hour = 0;
    }

    /* Format Hours */
    Time[0] = u8Hour / 10 + 48;
    Time[1] = u8Hour % 10 + 48;
    Time[2] = 0XAU + 48;

    /* Format Minutes */
    Time[3] = u8Minute / 10 + 48;
    Time[4] = u8Minute % 10 + 48;
    Time[5] = 0XAU + 48;

    /* Format Seconds */
    Time[6] = u8Second / 10 + 48;
    Time[7] = u8Second % 10 + 48;
}

void LPIT0_Ch0_IRQHandler(void)
{
    /* Check timer flag channel 0 */
    if (LPIT->MSR & (uint32)LPIT_CHANNEL0)
    {
        LPIT->MSR |= (uint32)LPIT_CHANNEL0; /* Clear flag */

        /* Update date */
        DateUpdate();

        /* Update time */
        TimeUpdate();

        /* Update flag */
        u8Flag = 1U;
    }
}

void LPUART2_RxTx_IRQHandler(void)
{
    LPUART_IRQHandling(&lpuart2);
}
