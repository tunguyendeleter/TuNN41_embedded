/******************************************************************************
 * Project Name:
 * File Name:   eg3_lpit.c
 *
 * Description: Implementation of a WATCHER using LPIT
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
#include "port.h"
#include "nvic.h"
#include "systick.h"
#include "lpuart.h"
#include "clock.h"
#include "lpit.h"
#include "stdio.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/**
 * @brief    Define PORTA IQRNumber
 */
#define RED_LED 15

/**
 * @brief    Define PORTA IQRNumber
 */
#define BLUE_LED 0

/**
 * @brief    Define PORTB IQRNumber
 */
#define GREEN_LED 16

/**
 * @brief    Define PORTB IQRNumber
 */
#define UPDATE_SECOND 2

/**
 * @brief    Define PORTB IQRNumber
 */
#define UPDATE_MIN 3

/**
 * @brief    Define PORTB IQRNumber
 */
#define UPDATE_HOUR 4

/**
 * @brief    Define PORTB IQRNumber
 */
#define RUN_WATCHER 1
/******************************************************************************
 *  GLOBAL VARIABLE
 *****************************************************************************/
volatile uint8 g_second, g_min, g_hour;
volatile uint8 flag;
volatile uint8 g_input[10];
volatile uint8 g_inputIndex;

/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *****************************************************************************/

/******************************************************************************
 *  MAIN FUNCTION
 *****************************************************************************/
int main(void)
{
    /* Initialize global variables */
    flag = UPDATE_HOUR;
    g_second = 30;
    g_min = 59;
    g_hour = 23;

    /*============== CLOCK ==============*/
    /*FIRC config: 48MHz; DIVIDER1 = 24MHz; DIVIDER2 = 24MHz*/
    FIRC_ClockEnable(DIV1_BY_2, DIV1_BY_2);

    /* Choose system clock */
    SystemClockConfig(SCS_FIRC_CLK);

    /*============== PORTD ==============*/
    /* Enable clock PORTD, PORTC */
    ClockEnable(PORTD_e);
    ClockEnable(PORTC_e);

    /*Config alternative funtion for pins Rx*/
    PORTC->PCR[6] |= (2 << PORT_PCR_MUX_SHIFT);
    /*Config alternative funtion for pins Tx*/
    PORTC->PCR[7] |= (2 << PORT_PCR_MUX_SHIFT);

    /* Set pin D0 as OUTPUT */
    PORT_Pin_Output_Config(PORTD, GPIOD, GREEN_LED);

    /*============== LPUART ==============*/
    /* LPUART1 Clock config */
    PCC->PCC_LPUART1 |= (3U << 24); /*Bit 24th: select clock source; 3: FIRC; 2: SIRC; 1: SOSC*/

    /* Enable clock LPUART1 */
    ClockEnable(LPUART1_e);

    /* LPUART1 config, baudrate = 9600 */
    LPUART_ConfigReceiveIT(LPUART1, LPUART_BAUD_SBR(156), LPUART_BAUD_OSR(16), ENABLE, ENABLE, LPUART_IT_RE);

    /* Config NVIC for Receiving LPUART */
    Interrupt_Enable(33, 0);

    /*============== LPIT ================*/
    /* Choose peripheral clock LPIT */
    PCC->PCC_LPIT |= (7 << 24);

    /* Enable clock LPIT */
    ClockEnable(LPIT_e);

    /* LPIT CH0 timer config tick = 128000 */
    LPIT_CH0_Init(128000);
    // LPIT_StartTimer(0);

    /* Config NVIC LPUART */
    Interrupt_Enable(48, 15);
    while (1)
    {
        if (flag == RUN_WATCHER)
        {
            if (g_second == 60)
            {
                g_second = 0;
                g_min++;
            }
            if (g_min == 60)
            {
                g_min = 0;
                g_hour++;
            }
            if (g_hour == 24)
            {
                g_hour = 0;
            }
            char data[20];
            sprintf(data, "%d : %d : %d\r\n", g_hour, g_min, g_second);
            LPUART_TransmitString(LPUART1, data);
            flag = 0;
        }
    }

    return 0;
}

void LPIT0_Ch0_IRQHandler(void)
{
    if ((LPIT->MSR >> 0) & 0X01U)
    {
        LPIT->MSR |= (1 << 0);
        g_second++;
        flag = 1;
        LPIT->MSR |= (1 << 0);
        if (GPIO_ReadFromInputPin(GPIOD, GREEN_LED))
        {
            GPIO_WriteToOutputPin(GPIOD, GREEN_LED, RESET);
        }
        else
        {
            GPIO_WriteToOutputPin(GPIOD, GREEN_LED, SET);
        }
    }
}

void LPUART1_RxTx_IRQHandler(void)
{
    g_input[g_inputIndex] = LPUART_ReceiveString(LPUART1);
    if (g_input[g_inputIndex] == '\n' || g_inputIndex == sizeof(g_input) / sizeof(g_input[0]))
    {
        uint8 i;
        if (flag == UPDATE_HOUR)
        {
            g_hour = (g_input[0] - 48) * 10 + (g_input[1] - 48);
            flag--;
        }
        else if (flag == UPDATE_MIN)
        {
            g_min = (g_input[0] - 48) * 10 + (g_input[1] - 48);
            flag--;
        }
        else if (flag == UPDATE_SECOND)
        {
            g_second = (g_input[0] - 48) * 10 + (g_input[1] - 48);
            flag--;
            LPIT_StartTimer(0);
        }
        for (i = 0; i < sizeof(g_input) / sizeof(g_input[0]); i++)
        {
            g_input[i] = 0;
        }
    }
    g_inputIndex = (g_inputIndex < sizeof(g_input) / sizeof(g_input[0])) ? (g_inputIndex + 1) : (0);
}