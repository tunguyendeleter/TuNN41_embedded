/******************************************************************************
 * Project Name:
 * File Name:   main.c
 *
 * Description: Implementation of a LPUART
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
#include "string.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/**
 * @brief    Define Buffer length
 */
#define BUFFER_LEN 10U
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
 * @brief    Define LED order of G -> R -> B
 */
#define SWITCH_LED1(X) ((X == 0) ? (GREEN_LED) : ((X == 1) ? (RED_LED) : (BLUE_LED)))

/******************************************************************************
 *  GLOBAL VARIABLE
 *****************************************************************************/
volatile uint32 g_systick;
volatile char g_index = 0;
volatile char g_Buffer[BUFFER_LEN] = {0};
uint8 g_u8LedState = 0;
Lpuart_ConfigType Lpuart_Config;

/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *****************************************************************************/
void LPUART1_RxTx_IRQHandler(void);

/******************************************************************************
 *  MAIN FUNCTION
 *****************************************************************************/

int main(void)
{
    g_systick = 0;

    /*FIRC config: 48MHz; DIVIDER1 = 24MHz; DIVIDER2 = 24MHz*/
    FIRC_ClockEnable(DIV1_BY_2, DIV1_BY_2);

    SystemClockConfig(SCS_FIRC_CLK);

    /* Enable clock PORTC, LPUART1 */
    ClockEnable(PORTC_e);
    ClockEnable(PORTD_e);

    /*Config alternative funtion for pins Rx*/
    PORTC->PCR[6] |= (2 << PORT_PCR_MUX_SHIFT);
    /*Config alternative funtion for pins Tx*/
    PORTC->PCR[7] |= (2 << PORT_PCR_MUX_SHIFT);
    
    /* Set pin D0,D15,D16 as OUTPUT */
    PORT_Pin_Output_Config(PORTD, GPIOD, RED_LED);
    PORT_Pin_Output_Config(PORTD, GPIOD, BLUE_LED);
    PORT_Pin_Output_Config(PORTD, GPIOD, GREEN_LED);

    GPIO_WriteToOutputPin(GPIOD, RED_LED, SET);
    GPIO_WriteToOutputPin(GPIOD, BLUE_LED, SET);
    GPIO_WriteToOutputPin(GPIOD, GREEN_LED, SET);

    /* LPUART1 Clock config */
    PCC->PCC_LPUART1 |= (3U << 24); /*Bit 24th: select clock source; 3: FIRC; 2: SIRC; 1: SOSC*/

    ClockEnable(LPUART1_e);

    /* LPUART1 config, baudrate = 9600 */
    LPUART_ConfigReceiveIT(LPUART1, LPUART_BAUD_SBR(156), LPUART_BAUD_OSR(16), ENABLE, ENABLE, LPUART_IT_RE);

    /* Config NVIC for Receiving LPUART */
    Interrupt_Enable(33, 0);

    while (1)
    {
        if (strcmp("LEDON", g_Buffer) == 0)
        {
            GPIO_WriteToOutputPort(GPIOD, ~0);
            GPIO_WriteToOutputPin(GPIOD, SWITCH_LED1(g_u8LedState), RESET);
            memset(g_Buffer, 0, 10);
            g_u8LedState = (g_u8LedState == 2)?(0):(g_u8LedState + 1);
            g_index = 0;
        }
        else if (strcmp("LEDOFF", g_Buffer) == 0)
        {
            GPIO_WriteToOutputPort(GPIOD, ~0);
            memset(g_Buffer, 0, 10);
            g_index = 0;
        }
    }

    return 0;
}

void LPUART1_RxTx_IRQHandler(void)
{
    g_Buffer[g_index] = LPUART_ReceiveString(LPUART1);
    g_index++;
}
