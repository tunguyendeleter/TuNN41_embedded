/******************************************************************************
 * Project Name:
 * File Name:   main.c
 *
 * Description: Implementation of a ADC
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
#include "clock.h"
#include "lpuart.h"
#include "adc.h"
#include "lpit.h"
#include "nvic.h"
#include "stdio.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/

/******************************************************************************
 *  GLOBAL VARIABLE
 *****************************************************************************/
volatile uint32 adc_result_pre;
volatile uint32 adc_result;
volatile uint32 flag;
volatile char data[15] = {0};

/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *****************************************************************************/

/******************************************************************************
 *  MAIN FUNCTION
 *****************************************************************************/

int main(void)
{
    /* Intialize global variables */
    adc_result_pre = 0;
    adc_result = 0;
    flag = 0;
    
    /***************************** CLOCK SOURCE: SIRC, FIRC*************************/
    /* SIRC config: 8MHz; DIVIDER1 = 4MHz; DIVIDER2 = 4MHz */
    SIRC_ClockEnable(DIV1_BY_1, DIV1_BY_1, 1);

    /* FIRC config: 48MHz; DIVIDER1 = 24MHz; DIVIDER2 = 24MHz */
    FIRC_ClockEnable(DIV1_BY_2, DIV1_BY_2);

    SystemClockConfig(SCS_FIRC_CLK);

    /***************************** GPIO: PORTC, PORTD ******************************/
    /* Enable clock PORTC, PORTD */
    ClockEnable(PORTC_e);
    ClockEnable(PORTD_e);

    /* Config RED led to display 1s */
    PORT_Pin_Output_Config(PORTD, GPIOD, 15);

    /***************************** LPUART: LPUART1 *********************************/
    /* Config alternative funtion for pins Rx */
    PORTC->PCR[6] |= (2 << PORT_PCR_MUX_SHIFT);
    /* Config alternative funtion for pins Tx */
    PORTC->PCR[7] |= (2 << PORT_PCR_MUX_SHIFT);

    /* LPUART1 Clock config */
    PCC->PCC_LPUART1 |= (3U << PCC_PCS_SHIFT); /*Bit 24th: select clock source; 3: FIRC; 2: SIRC; 1: SOSC*/

    /* Enable clock LPUART1 */
    ClockEnable(LPUART1_e);

    /* LPUART1 config, baudrate = 9600 */
    // LPUART_ConfigReceiveIT(LPUART1, LPUART_BAUD_SBR(156), LPUART_BAUD_OSR(16), ENABLE, ENABLE, LPUART_IT_RE);

    /***************************** LPIT: LPIT CH0 *********************************/
    /* LPIT Clock config : FIRCDIV2 */
    PCC->PCC_LPIT |= (3 << PCC_PCS_SHIFT);

    /* Enable clock LPIT */
    ClockEnable(LPIT_e);

    /* Config LPIT CH0 timer config tick = 24000000 */
    LPIT_CH0_Init(24000000);
    LPIT_StartTimer(0);

    /***************************** ADC: ADC0 **************************************/
    /* Config Clock source to ADC0: FIRC */
    PCC->PCC_ADC0 |= (3 << PCC_PCS_SHIFT);

    /* Enable clock ADC0 */
    ClockEnable(ADC0_e);

    /* Config ADC for convert potentiameter input at CH12*/
    ADC_Init(ADC0);

    /***************************** NVIC: LPUART, ADC0 ************************-****/
    /* Config NVIC for Receiving LPUART */
    // Interrupt_Enable(33, 15);
    Interrupt_Enable(48, 15);
    while (1)
    {
        /* Enable channel 0 ADC0 */
        ADC0->SC1[0] = (12 << 0);

        volatile uint32 i = 0xffff;
        while (i--)
        {
        }

        while ((ADC0->SC1[0] >> 7) == 0)
        {
        }

        /* Read ADC0 */
        adc_result = ADC0->R[0];
    }

    return 0;
}

void LPIT0_Ch0_IRQHandler(void)
{
    if ((LPIT->MSR >> 0) & 0X01U)
    {
        LPIT->MSR |= (1 << 0);
        if (GPIO_ReadFromInputPin(GPIOD, 15))
        {
            GPIO_WriteToOutputPin(GPIOD, 15, RESET);

            /* Transmit converted data to LPUART*/
            if (adc_result != adc_result_pre)
            {
                adc_result_pre = adc_result;
                flag = 1;
            }
            if (flag == 1)
            {
                // sprintf((char *)data, "Data : %d\r\n", adc_result);
                // LPUART_TransmitString(LPUART1, (char *)data);
                flag = 0;
            }
        }
        else
        {
            GPIO_WriteToOutputPin(GPIOD, 15, SET);
        }
    }
}
