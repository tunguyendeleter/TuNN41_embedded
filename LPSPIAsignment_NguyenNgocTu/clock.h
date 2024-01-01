/******************************************************************************
 * Project Name: FRESHER  MCAL
 * File Name: clock.h
 *
 * Description: Implementation of the PCC and SCG
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex-M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/

#ifndef DRIVERS_INC_CLOCK_H_
#define DRIVERS_INC_CLOCK_H_


/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "S32K144xx.h"

/******************************************************************************
*   VERSION CHECK
 *****************************************************************************/


/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/**
 * @brief  MACROS for module PCC and SCG
 */

/*There are 4 clock source that can provide clock for clock peripheral SCG*/
/*They are: System OSC , Slow IRC , Fast IRC, System PLL */

/* Below is the Macros to config SOSC, SIRC, FIRC, SPLL */

/* Choose system clock source */
#define SCS_SOSC_CLK 	1U		/*System OSC mode*/
#define SCS_SIRC_CLK	2U		/*Slow IRC mode*/
#define SCS_FIRC_CLK	3U		/*Fast IRC mode*/
#define SCS_SPLL_CLK	6U		/*System PLL mode*/

/* Choose Core Clock Divide Ratio */
#define DIVCORE_BY_(X)	(X-1)		/*X is from 1 to 16*/

/* Choose Bus Clock Divide Ratio */
#define DIVBUS_BY_(X)	(X-1)		/*X is from 1 to 16*/

/* Choose Source Clock Divide Ratio */
#define DIVSLOW_BY_(X)	(X-1)		/*X is from 1 to 8******/

/*FIRC,SOSC,SIRC, SPLL macros*/

/*FIRC,SOSC Divider 1*/
#define DIV1_BY_DISABLE	0
#define DIV1_BY_1				1
#define DIV1_BY_2				2
#define DIV1_BY_4				3
#define DIV1_BY_8				4
#define DIV1_BY_16			5
#define DIV1_BY_32			6
#define DIV1_BY_64			7

/*FIRC, SOSC Divider 2*/
#define DIV2_BY_DISABLE	0
#define DIV2_BY_1				1
#define DIV2_BY_2				2
#define DIV2_BY_4				3
#define DIV2_BY_8				4
#define DIV2_BY_16			5
#define DIV2_BY_32			6
#define DIV2_BY_64			7

/*SIRC Range Select*/
#define RANGE_LOW_SIRC		0	/*2 MHz*/
#define RANGE_HIGH_SIRC		1	/*8 MHz*/

/*SOSC Range Select*/
#define RANGE_LOW_FREQUENCY			1
#define RANGE_MEDIUM_FREQUENCY	2
#define RANGE_HIGH_FREQUENCY		3

/*SOSC Reference Select*/
#define REFER_EXTENAL			0
#define REFER_INTERNAL		1

/*SPLL PreDiv*/
#define PRE_DIV_BY_(X)		(X-1) /*1->8*/

/*SPLL Multiply Factor*/
#define MULTIPLY_BY_(X)		(X-16)	/*16 -> 47*/

/*SPLL Input Clock Source Select*/
#define INPUT_SOSC			0
#define INPUT_FIRC			1

/*CLOCK OUT PIN Macros*/
#define SCG_SLOW_CLOCK		0
#define SYSTEM_OSC_CLOCK	1
#define SLOW_IRC_CLOCK		2
#define FAST_IRC_CLOCK		3
#define SYSTEM_PLL_CLOCK	6

/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/
/**
* @brief  typedef enum to put into ClockEnable and ClockDisable functions
*/
typedef enum{
	PORTA_e,	/*Peripheral PORTA*/
	PORTB_e,	/*Peripheral PORTB*/
	PORTC_e,	/*Peripheral PORTC*/
	PORTD_e,	/*Peripheral PORTD*/
	PORTE_e,	/*Peripheral PORTE*/

	LPUART0_e,	/*Peripheral LPUART0*/
	LPUART1_e,	/*Peripheral LPUART1*/
	LPUART2_e,	/*Peripheral LPUART2*/

	LPIT_e,	/*Peripheral LPIT */

	LPTMR0_e,	/*Peripheral LPTMR0*/

	FTM0_e,	/*Peripheral FTM0 */
	FTM1_e,	/*Peripheral FTM1 */
	FTM2_e,	/*Peripheral FTM2 */
	FTM3_e, /*Peripheral FTM3 */
	FTM4_e,	/*Peripheral FTM4 */
	FTM5_e,	/*Peripheral FTM5 */
	FTM6_e,	/*Peripheral FTM6 */
	FTM7_e,	/*Peripheral FTM7 */
	
	ADC0_e,	/*Peripheral ADC0 */
	ADC1_e,	/*Peripheral ADC0 */

	LPSPI0_e,	/*Peripheral LPSPI0 */
	LPSPI1_e,	/*Peripheral LPSPI1 */
	LPSPI2_e	/*Peripheral LPSPI2 */
}Peri_Enum;   /*Can change name to enable clock of other peripheral as well*/

/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/

/*This clock enable function include PORT, LPUART*/

extern void ClockEnable(Peri_Enum Peri_Name_e);

extern void ClockDisable(Peri_Enum Peri_Name_e);

extern void FIRC_ClockEnable(uint32 Divider1, uint32 Divider2);		/*Fast Clock for the SCG system*/

extern void SIRC_ClockEnable(uint32 Divider1, uint32 Divider2, uint32 Range);

extern void SOSC_ClockEnable(uint32 Divider1, uint32 Divider2, uint32 Range, uint32 Reference);

extern void SPLL_ClockEnable(uint32 Divider1, uint32 Divider2, uint32 PreDiv, uint32 Multiply, uint32 InputClockSource);

extern void SystemClockConfig(uint32 ClockMode); 								/*Test API*/

extern void SCG_ClockOutSelect(uint32 CLKOUTCNFG_Mode);


#endif /* DRIVERS_INC_CLOCK_H_ */

/*---------------------- End of File ----------------------------------------*/
