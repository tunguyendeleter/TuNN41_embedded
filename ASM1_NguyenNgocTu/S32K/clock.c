/*
** ###########################################################################################################################
**	   Project name:        _01_BlinkLed
**	   File name:           clock.c
**     Description: 	Implementation of the PCC and SCGs
 *              	Target systems:           S32K144
 *              	Derivatives:              ARM-Cortex M4F
 *              	Compiler:                 S32DS
**
** ############################################################################################################################
*/
/**
 *   @file       clock.c
 *   @version    V1.0
 *   @brief      <V1.0> <clock> Driver
 *   @addtogroup <clock>_driver
 *   @{
 */


/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "clock.h"

/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/
/**
 *   @brief      This function enable clock for peripherals base on value of Peri_Name_e
 *
 *   @param[in]  Peri_Enum       Peri_Name_e
 *

 *
 *   @return     void   xxxxxxxx
 *   @retval     yyy1       xxxxxxxx
 *   @retval     yyy2       xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
*/
/*This clock enable function include PORT, LPUART*/
void ClockEnable(Peri_Enum Peri_Name_e){
	switch (Peri_Name_e){
		case PORTA_e: PCC->PORT[0] |= (1U << 30); break;
		case PORTB_e: PCC->PORT[1] |= (1U << 30); break;
		case PORTC_e: PCC->PORT[2] |= (1U << 30); break;
		case PORTD_e: PCC->PORT[3] |= (1U << 30); break;
		case PORTE_e: PCC->PORT[4] |= (1U << 30); break;

		case LPUART0_e: PCC->PCC_LPUART0 |= (1U << 30); break;
		case LPUART1_e: PCC->PCC_LPUART1 |= (1U << 30); break;
		case LPUART2_e: PCC->PCC_LPUART2 |= (1U << 30); break;

		case LPIT_e: PCC->PCC_LPIT |= (1U << 30); break;

		case LPTMR0_e: PCC->LPTMR0 |= (1U << 30); break;

		case FTM0_e: PCC->FTM0 |= (1U << 30); break;
		case FTM1_e: PCC->FTM1 |= (1U << 30); break;
		case FTM2_e: PCC->FTM2 |= (1U << 30); break;
		case FTM3_e: PCC->FTM3 |= (1U << 30); break;
		case FTM4_e: PCC->FTM4 |= (1U << 30); break;
		case FTM5_e: PCC->FTM5 |= (1U << 30); break;
		case FTM6_e: PCC->FTM6 |= (1U << 30); break;
		case FTM7_e: PCC->FTM7 |= (1U << 30); break;
	}
		
}
/**
 *   @brief      This function disable clock for peripherals base on value of Peri_Name_e
 *
 *   @param[in]  Peri_Enum       Peri_Name_e
 *

 *
 *   @return     void   xxxxxxxx
 *   @retval     yyy1       xxxxxxxx
 *   @retval     yyy2       xxxxxxxx
 *
 *   @note
 *
*/
void ClockDisable(Peri_Enum Peri_Name_e){
	switch (Peri_Name_e){
		case PORTA_e: PCC->PORT[0] &= ~(1U << 30); break;
		case PORTB_e: PCC->PORT[1] &= ~(1U << 30); break;
		case PORTC_e: PCC->PORT[2] &= ~(1U << 30); break;
		case PORTD_e: PCC->PORT[3] &= ~(1U << 30); break;
		case PORTE_e: PCC->PORT[4] &= ~(1U << 30); break;

		case LPUART0_e: PCC->PCC_LPUART0 &= ~(1U << 30); break;
		case LPUART1_e: PCC->PCC_LPUART1 &= ~(1U << 30); break;
		case LPUART2_e: PCC->PCC_LPUART2 &= ~(1U << 30); break;

		case LPIT_e: PCC->PCC_LPIT &= ~(1U << 30); break;

		case LPTMR0_e: PCC->LPTMR0 &= ~(1U << 30); break;

		case FTM0_e: PCC->FTM0 &= ~(1U << 30); break;
		case FTM1_e: PCC->FTM1 &= ~(1U << 30); break;
		case FTM2_e: PCC->FTM2 &= ~(1U << 30); break;
		case FTM3_e: PCC->FTM3 &= ~(1U << 30); break;
		case FTM4_e: PCC->FTM4 &= ~(1U << 30); break;
		case FTM5_e: PCC->FTM5 &= ~(1U << 30); break;
		case FTM6_e: PCC->FTM6 &= ~(1U << 30); break;
		case FTM7_e: PCC->FTM7 &= ~(1U << 30); break;

	}

}
/**
 *   @brief      This function configure divider for FIRC clock source and enable it.
 *
 *   @param[in]  uint32       Divider1
 *   @param[in]  uint32       Divider2
 *
 *
 *   @return     void   xxxxxxxx
 *
 *   @note
 *
*/

void FIRC_ClockEnable(uint32 Divider1, uint32 Divider2){
	
	uint32 temp = 0;

	temp &= ~(1U << 0);
	SCG->SCG_FIRCCSR = temp;							/*Clock disable to config*/

	temp = 0;
	temp |= ((Divider2 << 8) | (Divider1 << 0));
	SCG->SCG_FIRCDIV = temp;							/*Clock divider distribute 1 and 2*/

	temp = 0;
	temp |= (1U << 0);
	SCG->SCG_FIRCCSR = temp;							/*Clock enable*/

	while(!(SCG->SCG_FIRCCSR & (1U << 24)));			/*Wait to confirm status*/
}

/**
 *   @brief      This function configure divider for SIRC clock source, select External or Internal reference and enable it.
 *
 *   @param[in]  uint32       Divider1
 *   @param[in]  uint32       Divider2
 *   @param[in]  uint32       Range
 *
 *
 *   @return     void   xxxxxxxx
 *
 *   @note
 *
*/

void SIRC_ClockEnable(uint32 Divider1, uint32 Divider2, uint32 Range){

	volatile uint32 temp = 0;

	temp &= ~(1U << 0);
	SCG->SCG_SIRCCSR = temp;							/*Clock disable*/

	temp = 0;
	temp |= ((Divider2 << 8) | (Divider1 << 0));
	SCG->SCG_SIRCDIV = temp;							/*Clock divider distribute 1 and 2*/

	temp = 0;
	temp |= (Range << 0);
	SCG->SCG_SIRCCFG = temp;							/*Select External or Internal reference*/

	temp |= (1U << 0);
	SCG->SCG_SIRCCSR = temp;							/*Clock enable*/

	while(!(SCG->SCG_SIRCCSR & (1U << 24)));			/*Wait to confirm status*/
}

/**
 *   @brief      This function configure divider for SOSC clock source, select External or Internal reference and enable it.
 *
 *   @param[in]  uint32       Divider1
 *   @param[in]  uint32       Divider2
 *   @param[in]  uint32       Range
 *
 *   @arg        uint32      Divider1
 *   @arg        uint32      Divider1
 *   @arg        uint32      Range
 *   @arg        uint32      Reference
 *   @return     void   xxxxxxxx
 *
 *   @note
 *
*/
void SOSC_ClockEnable(uint32 Divider1, uint32 Divider2, uint32 Range, uint32 Reference){

	volatile uint32 temp = 0;

	temp &= ~(1U << 0);
	SCG->SCG_SOSCCSR = temp;											/*Clock disable*/

	temp = 0;
	temp |= ((Divider2 << 8) | (Divider1 << 0));
	SCG->SCG_SOSCDIV = temp;											/*Clock divider distribute 1 and 2*/

	temp = 0;
	temp |= (Range << 4);
	temp |= (Reference << 2);
	SCG->SCG_SOSCCFG = temp;											/*Select External or Internal reference*/

	temp |= (1U << 0);
	SCG->SCG_SOSCCSR = temp;											/*Clock enable*/

	while(!(SCG->SCG_SOSCCSR & (1U << 24)));			/*Wait to confirm status*/
}

/**
 *   @brief      This function choose clock source for SPLL
 * 				configure Multiply and PreDiv to configure value SPLL clock source
 * 				 then configuring divider 1 and 2
 *
 *
 *   @param[in]  uint32       Divider1
 *   @param[in]  uint32       Divider2
 *   @param[in]  uint32       PreDiv
 *   @param[in]  uint32       Range
 *   @param[in]  uint32       InputClockSource
 *
 *
 *
 *   @return     void   xxxxxxxx
 *
 *   @note
 *
*/
void SPLL_ClockEnable(uint32 Divider1, uint32 Divider2, uint32 PreDiv, uint32 Multiply, uint32 InputClockSource){

	volatile uint32 temp = 0;

	while (SCG->SCG_SPLLCSR & (1U << 23));			/*Check if SPLL is unlocked*/

	temp &= ~(1U << 0);
	SCG->SCG_SPLLCSR = temp;					/*Disable SPLL clock to config*/

	temp = 0;
	temp |= (InputClockSource << 0);	/*Choose Input clock source for SPLL*/
	temp |= (Multiply << 16);			/*SPLL Multiplier*/
	temp |= (PreDiv << 8);				/*PreDiv*/
	SCG->SCG_SPLLCFG |= temp;

	temp = 0;
	temp |= ((Divider2 << 8) | (Divider1 << 0));
	SCG->SCG_SPLLDIV = temp;					/*Clock divider distribute 1 and 2*/

	temp = 0;
	temp |= (1U << 0);
	SCG->SCG_SPLLCSR = temp;					/*Enable SPLL clock*/

	while(!(SCG->SCG_SPLLCSR & (1U << 24)));		/*Wait to confirm status*/
}

/**
 *   @brief      This function choose clock source which is used as system clock
 *
 *
 *   @param[in]  uint32       ClockMode
 *   @param[in]  uint32       Divider2
 *   @param[in]  uint32       PreDiv
 *   @param[in]  uint32       Range
 *   @param[in]  uint32       InputClockSource
 *
 *
 *
 *   @return     void   xxxxxxxx
 *
 *   @note
 *
*/
void SystemClockConfig(uint32 ClockMode){

	 uint32 temp = 0;

	/*Config system clock*/
	temp |= (ClockMode << 24); 		/*24th is the position to choose the System Clock Source called SCS*/

	temp |= (DIVCORE_BY_(2) << 16); 	/*16th is the position to choose the divide core: Original Div 12*/

	temp |= (DIVBUS_BY_(2) << 4);		/*4th is the position to choose the divide bus*/

	temp |= (DIVSLOW_BY_(3) << 0);		/*0th is the position to choose the divide slow: Original Div 2*/

	SCG->SCG_RCCR = temp;

	/*Test SCS bit of CSR register*/
	while (((SCG->SCG_CSR & 0xF000000) >> 24 ) != ClockMode);		/*1 is SOSC; 3 is fast mode; 6 is PLL mode*/

	//while ((SCG->SCG_CSR >> 24) != 6);
}

/**
 *   @brief      This function choose clock out
 *
 *
 *   @param[in]  uint32       CLKOUTCNFG_Mode
 *
 *
 *   @return     void   xxxxxxxx
 *
 *   @note
 *
*/

void SCG_ClockOutSelect(uint32 CLKOUTCNFG_Mode){

	/*3 for FIRC; 6 for SPLL*/ /*If debugger does not jump in this line -> there are some problem in while loop*/

	SCG->SCG_CLKOUTCNFG |= (CLKOUTCNFG_Mode << 24);
}
