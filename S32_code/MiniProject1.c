/******************************************************************************
 * Project Name: BLINKLED
 * File Name:   main.c
 *
 * Description: Implementation of a blinkled assignment
 *
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex-M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "port.h"
#include "nvic.h"
#include "systick.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/**
 * @brief    Define PORTA IQRNumber
 */
#define RED_LED 					15

/**
 * @brief    Define PORTA IQRNumber
 */
#define BLUE_LED 					0

/**
 * @brief    Define PORTB IQRNumber
 */
#define GREEN_LED 				16

/**
 * @brief    Define LED order of G -> R -> B
 */
#define SWITCH_LED1(X) ((X == 0) ? (GREEN_LED) : ((X == 1) ? (RED_LED) : (BLUE_LED)))

/**
 * @brief    Define LED order of B -> R -> G
 */
#define SWITCH_LED2(X) ((X == 0) ? (BLUE_LED) : ((X == 1) ? (RED_LED) : (GREEN_LED)))

/**
 * @brief    Define PORTA IQRNumber
 */
#define PORTA_IQRNumber 	59

/**
 * @brief    Define PORTB IQRNumber
 */
#define PORTB_IQRNumber 	60

/******************************************************************************
 *  GLOBAL VARIABLE
 *****************************************************************************/
/**
 * @brief    Define global variable to store led state, order state, systick value
 */
volatile uint8 g_u8ButtonState = 0;
volatile uint8 g_u8LedOrder = 1;
volatile uint32 g_systick = 0;
uint8 g_u8LedState = 0;

/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *****************************************************************************/
void PORTA_IRQHandler(void);
void PORTB_IRQHandler(void);
void SysTick_Handler(void);

/******************************************************************************
 *  MAIN FUNCTION
 *****************************************************************************/
int main(void)
{
    /* Update reset value of global variables */
    g_u8ButtonState = 0;
    g_u8LedState = 0;
    g_u8LedOrder = 1;
    g_systick = 0;

    /* Enable clock PORTA, PORTB, PORTC, PORTD */
    PCC->PORT[PORTA_INDEX] |= PCC_CGC_MASK;
    PCC->PORT[PORTB_INDEX] |= PCC_CGC_MASK;
    PCC->PORT[PORTC_INDEX] |= PCC_CGC_MASK;
    PCC->PORT[PORTD_INDEX] |= PCC_CGC_MASK;

    /* Set pin A3, B8 as INPUT */
    PORT_Pin_Input_IT_Config(PORTA, GPIOA, 3, IRQC_FE, PIN_PULLDOWN);
    PORT_Pin_Input_IT_Config(PORTB, GPIOB, 8, IRQC_FE, PIN_PULLDOWN);

    /* Set pin D0,D15,D16 as OUTPUT */
    PORT_Pin_Output_Config(PORTD, GPIOD, RED_LED);
    PORT_Pin_Output_Config(PORTD, GPIOD, BLUE_LED);
    PORT_Pin_Output_Config(PORTD, GPIOD, GREEN_LED);

    /* Set only green LED is ON */
		GPIO_WriteToOutputPin(GPIOD, RED_LED, SET);
		GPIO_WriteToOutputPin(GPIOD, BLUE_LED, SET);
		GPIO_WriteToOutputPin(GPIOD, GREEN_LED, SET);
    GPIO_WriteToOutputPin(GPIOD, GREEN_LED, RESET);

    /* Config NVIC for PORTA, PORTB */
    Interrupt_Enable(PORTA_IQRNumber, 15);
    Interrupt_Enable(PORTB_IQRNumber, 15);

    /* Config SysTick */
    SysTick_Init(4799999);
    SysTick_StartTimer();

    while (1)
    {
        if (g_u8ButtonState == 1 && g_systick >= 10)
        {
						/* Check LED order */
            if (g_u8LedOrder)
            {
							/* Update LED state in increasing order */
							g_u8LedState = (g_u8LedState == 3)?(0):(g_u8LedState + 1);
            }
            else
            {
							/* Update LED state in decreasing order */
							g_u8LedState = (g_u8LedState == 0)?(3):(g_u8LedState - 1);
            }
            
						/* Reset systick count = 0*/
						g_systick = 0;
						
						/* Update current LED */
						GPIO_WriteToOutputPin(GPIOD, RED_LED, SET);
						GPIO_WriteToOutputPin(GPIOD, BLUE_LED, SET);
						GPIO_WriteToOutputPin(GPIOD, GREEN_LED, SET);
						GPIO_WriteToOutputPin(GPIOD, SWITCH_LED1(g_u8LedState), RESET);
        }
    }
		
    return 0;
}

void PORTA_IRQHandler(void)
{
		/* Check if PIN A3 is release */
    if (PORTA->PCR[3] & (1 << 24))
    {
        /* Clear pending flag */
        PORTA->PCR[3] |= PORT_PCR_ISF_MASK;
        g_u8ButtonState++;
        g_u8ButtonState %= 2;

        /* Change state of timer */
        if (g_u8ButtonState == 0)
        {
            SysTick_StopTimer();
        }
        else
        {
            SysTick_StartTimer();
        }
    }
}

void PORTB_IRQHandler(void)
{
		/* Check if PIN B8 is release */
    if (PORTB->PCR[8] & (1 << 24))
    {
        /* Clear pending flag */
        PORTB->PCR[8] |= PORT_PCR_ISF_MASK;
        g_u8LedOrder++;
        g_u8LedOrder %= 2;
    }
}

void SysTick_Handler(void)
{
		/* Update tick count */
    g_systick++;
}