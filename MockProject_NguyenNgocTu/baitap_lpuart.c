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

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
#define BUFFER_LEN          10U

/******************************************************************************
 *  GLOBAL VARIABLE
 *****************************************************************************/
volatile uint32 g_systick;
volatile char g_index = 0;
volatile char g_Buffer[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
// volatile char g_Data[10];
Lpuart_ConfigType Lpuart_Config;

/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *****************************************************************************/
int STRCMP(char *str1, char *str2);
int STRLEN(char *str);
void LPUART1_RxTx_IRQHandler(void);
void SysTick_Handler(void);

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

    /*Config alternative funtion for pins Rx*/
    PORTC->PCR[6] |= (2 << PORT_PCR_MUX_SHIFT);
    /*Config alternative funtion for pins Tx*/
    PORTC->PCR[7] |= (2 << PORT_PCR_MUX_SHIFT);

    /* LPUART1 Clock config */
    PCC->PCC_LPUART1 |= (3U << 24); /*Bit 24th: select clock source; 3: FIRC; 2: SIRC; 1: SOSC*/

    ClockEnable(LPUART1_e);

    /* LPUART1 config, baudrate = 9600 */
    LPUART_ConfigReceiveIT(LPUART1, LPUART_BAUD_SBR(156), LPUART_BAUD_OSR(16), ENABLE, ENABLE, LPUART_IT_RE);

    /* Config NVIC for Receiving LPUART */
    Interrupt_Enable(33, 0);

    /* Config SysTick */
    SysTick_Init(4799999);
    SysTick_StartTimer();

    while (1)
    {
        if (STRCMP("LEDON", g_Buffer) == 0)
        {
            if (g_systick >= 10)
            {
                LPUART_TransmitString(LPUART1, "HELLO WORLD\r\n");
                g_systick = 0;
            }
        }
    }

    return 0;
}

int STRLEN(char *str)
{
    int dem = 0;
    while (str[dem++] != '\0')
    {
    }
    return dem - 1;
}

int STRCMP(char *str1, char *str2)
{
    int len = STRLEN(str1) < STRLEN(str2) ? STRLEN(str1) : STRLEN(str1);
    for (int i = 0; i < len; i++)
    {
        if (str1[i] > str2[i])
        {
            return 1;
        }
        else if (str1[i] < str2[i])
        {
            return -1;
        }
    }
    if (str1[len] == '\0')
    {
        if (str2[len] != '\0')
        {
            return -1;
        }
    }
    if (str2[len] == '\0')
    {
        if (str1[len] != '\0')
        {
            return 1;
        }
    }
    return 0;
}

void LPUART1_RxTx_IRQHandler(void)
{
    g_Buffer[g_index] = LPUART_ReceiveString(LPUART1);
    g_index++;
}

void SysTick_Handler(void)
{
    g_systick++;
}