/******************************************************************************
 * Project Name:
 * File Name:   main.c
 *
 * Description: Implementation of a LPIT
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

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/**
 * @brief    Define PORTA IQRNumber
 */
#define RED_LED                     15

/**
 * @brief    Define PORTA IQRNumber
 */
#define BLUE_LED 					0

/**
 * @brief    Define PORTB IQRNumber
 */
#define GREEN_LED                   16
/******************************************************************************
 *  GLOBAL VARIABLE
 *****************************************************************************/

/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *****************************************************************************/

/******************************************************************************
 *  MAIN FUNCTION
 *****************************************************************************/
int main(void)
{
    /*FIRC config: 48MHz; DIVIDER1 = 24MHz; DIVIDER2 = 24MHz*/
    FIRC_ClockEnable(DIV1_BY_2, DIV1_BY_2);

    SystemClockConfig(SCS_FIRC_CLK);

    /* Enable clock PORTD */
    PCC->PORT[PORTD_INDEX] |= PCC_CGC_MASK;

	/* Set pin D0 as OUTPUT */
	PORT_Pin_Output_Config(PORTD, GPIOD, GREEN_LED);

    /* Choose peripheral clock LPIT */
    PCC->PCC_LPIT |= (3 << 24);
    /* Enable clock LPIT */
    PCC->PCC_LPIT |= (1 << 30);

    LPIT_CH0_Init(24000000);   
    LPIT_StartTimer(0);
    
    /* Set only green LED is ON */
    GPIO_WriteToOutputPin(GPIOD, GREEN_LED, RESET);
    
    Interrupt_Enable(48, 15);
    while (1)
    {
        
    }

    return 0;
}

void LPIT0_Ch0_IRQHandler(void)
{
    if ((LPIT->MSR >> 0) & 0X01U)
    {
        LPIT->MSR |= (1 << 0);   
        if (GPIO_ReadFromInputPin(GPIOD, GREEN_LED))
        {
            GPIO_WriteToOutputPin(GPIOD, GREEN_LED, RESET);
        }else
        {
            GPIO_WriteToOutputPin(GPIOD, GREEN_LED, SET);
        }     
    }
}
