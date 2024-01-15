#ifndef CLOCK_H
#define CLOCK_H

#include "S32K144xx.h"

typedef enum
{
	PORTA_e,
	PORTB_e,
	PORTC_e,
	PORTD_e,
	PORTE_e,

	LPUART0_e,
	LPUART1_e,
	LPUART2_e,

	LPIT_e,

	LPTMR0_e,

	FTM0_e,
	FTM1_e,
	FTM2_e,
	FTM3_e,
	FTM4_e,
	FTM5_e,
	FTM6_e,
	FTM7_e,

	LPSPI0_e,
	LPSPI1_e,
	LPSPI2_e

} Peri_Enum; /*Can change name to enable clock of other peripheral as well*/

/*There are 4 clock source that can provide clock for clock peripheral SCG*/
/*They are: System OSC , Slow IRC , Fast IRC, System PLL */

/* Below is the Macros to config SOSC, SIRC, FIRC, SPLL */

/* Choose system clock source */
#define SCS_SOSC_CLK 1U /*System OSC mode*/
#define SCS_SIRC_CLK 2U /*Slow IRC mode*/
#define SCS_FIRC_CLK 3U /*Fast IRC mode*/
#define SCS_SPLL_CLK 6U /*System PLL mode*/

/* Choose Core Clock Divide Ratio */
#define DIVCORE_BY_(X) (X - 1) /*X is from 1 to 16*/

/* Choose Bus Clock Divide Ratio */
#define DIVBUS_BY_(X) (X - 1) /*X is from 1 to 16*/

/* Choose Source Clock Divide Ratio */
#define DIVSLOW_BY_(X) (X - 1) /*X is from 1 to 8******/

/*FIRC,SOSC macros*/

/*FIRC,SOSC Divider 1*/
#define DIV1_BY_DISABLE 0
#define DIV1_BY_1 1
#define DIV1_BY_2 2
#define DIV1_BY_4 3
#define DIV1_BY_8 4
#define DIV1_BY_16 5
#define DIV1_BY_32 6
#define DIV1_BY_64 7

/*FIRC, SOSC Divider 2*/
#define DIV2_BY_DISABLE 0
#define DIV2_BY_1 1
#define DIV2_BY_2 2
#define DIV2_BY_4 3
#define DIV2_BY_8 4
#define DIV2_BY_16 5
#define DIV2_BY_32 6
#define DIV2_BY_64 7

/*SIRC Range Select*/
#define RANGE_LOW_SIRC 0  /*2 MHz*/
#define RANGE_HIGH_SIRC 1 /*8 MHz*/

/*SOSC Range Select*/
#define RANGE_LOW_FREQUENCY 1
#define RANGE_MEDIUM_FREQUENCY 2
#define RANGE_HIGH_FREQUENCY 3

/*SOSC Reference Select*/
#define REFER_EXTENAL 0
#define REFER_INTERNAL 1

/*SPLL PreDiv*/
#define PRE_DIV_BY_(X) (X - 1) /*1->8*/

/*SPLL Multiply Factor*/
#define MULTIPLY_BY_(X) (X - 16) /*16 -> 47*/

/*SPLL Input Clock Source Select*/
#define INPUT_SOSC 0
#define INPUT_FIRC 1

/*SPLL Input Clock Source Select*/
#define INPUT_SOSC 0
#define INPUT_FIRC 1

/*CLOCK OUT PIN Macros*/
#define SCG_SLOW_CLOCK 0
#define SYSTEM_OSC_CLOCK 1
#define SLOW_IRC_CLOCK 2
#define FAST_IRC_CLOCK 3
#define SYSTEM_PLL_CLOCK 6

/*CLOCK OUT PIN Macros*/
#define SCG_SLOW_CLOCK 0
#define SYSTEM_OSC_CLOCK 1
#define SLOW_IRC_CLOCK 2
#define FAST_IRC_CLOCK 3
#define SYSTEM_PLL_CLOCK 6

void ClockEnable(Peri_Enum Peri_Name_e);

void ClockDisable(Peri_Enum Peri_Name_e);

void FIRC_ClockEnable(uint32 Divider1, uint32 Divider2); /*Fast Clock for the SCG system*/

void SIRC_ClockEnable(uint32 Divider1, uint32 Divider2, uint32 Range);

void SOSC_ClockEnable(uint32 Divider1, uint32 Divider2, uint32 Range, uint32 Reference);

void SPLL_ClockEnable(uint32 Divider1, uint32 Divider2, uint32 PreDiv, uint32 Multiply, uint32 InputClockSource);

void SystemClockConfig(uint32 ClockMode, uint32 DivCore, uint32 DivBus, uint32 DivSlow);

void CLOCK_SCG_ENABLE(void);

void SCG_ClockOutSelect(uint32 CLKOUTCNFG_Mode);

#endif /* CLOCK_H */
