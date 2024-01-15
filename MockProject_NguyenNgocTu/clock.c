#include "clock.h"

///*This clock enable function include PORT, LPUART*/
//void ClockEnable(Peri_Enum Peri_Name_e){
//	switch (Peri_Name_e){
//		case PORTA_e: PCC->PCC_PORTA |= (1U << 30); break;
//		case PORTB_e: PCC->PCC_PORTB |= (1U << 30); break;
//		case PORTC_e: PCC->PCC_PORTC |= (1U << 30); break;
//		case PORTD_e: PCC->PCC_PORTD |= (1U << 30); break;
//		case PORTE_e: PCC->PCC_PORTE |= (1U << 30); break;
//
//		case LPUART0_e: PCC->PCC_LPUART0 |= (1U << 30); break;
//		case LPUART1_e: PCC->PCC_LPUART1 |= (1U << 30); break;
//		case LPUART2_e: PCC->PCC_LPUART2 |= (1U << 30); break;
//
//		case LPIT_e: PCC->PCC_LPIT |= (1U << 30); break;
//
//		case LPTMR0_e: PCC->PCC_LPTMR0 |= (1U << 30); break;
//
//		case FTM0_e: PCC->PCC_FTM0 |= (1U << 30); break;
//		case FTM1_e: PCC->PCC_FTM1 |= (1U << 30); break;
//		case FTM2_e: PCC->PCC_FTM2 |= (1U << 30); break;
//		case FTM3_e: PCC->PCC_FTM3 |= (1U << 30); break;
//		case FTM4_e: PCC->PCC_FTM4 |= (1U << 30); break;
//		case FTM5_e: PCC->PCC_FTM5 |= (1U << 30); break;
//		case FTM6_e: PCC->PCC_FTM6 |= (1U << 30); break;
//		case FTM7_e: PCC->PCC_FTM7 |= (1U << 30); break;
//
//		case LPSPI0_e: PCC->PCC_LPSPI0 |= (1U << 30); break;
//		case LPSPI1_e: PCC->PCC_LPSPI1 |= (1U << 30); break;
//		case LPSPI2_e: PCC->PCC_LPSPI2 |= (1U << 30); break;
//	}
//
//}
//
//void ClockDisable(Peri_Enum Peri_Name_e){
//	switch (Peri_Name_e){
//		case PORTA_e: PCC->PCC_PORTA &= ~(1U << 30); break;
//		case PORTB_e: PCC->PCC_PORTB &= ~(1U << 30); break;
//		case PORTC_e: PCC->PCC_PORTC &= ~(1U << 30); break;
//		case PORTD_e: PCC->PCC_PORTD &= ~(1U << 30); break;
//		case PORTE_e: PCC->PCC_PORTE &= ~(1U << 30); break;
//
//		case LPUART0_e: PCC->PCC_LPUART0 &= ~(1U << 30); break;
//		case LPUART1_e: PCC->PCC_LPUART1 &= ~(1U << 30); break;
//		case LPUART2_e: PCC->PCC_LPUART2 &= ~(1U << 30); break;
//
//		case LPIT_e: PCC->PCC_LPIT &= ~(1U << 30); break;
//
//		case LPTMR0_e: PCC->PCC_LPTMR0 &= ~(1U << 30); break;
//
//		case FTM0_e: PCC->PCC_FTM0 &= ~(1U << 30); break;
//		case FTM1_e: PCC->PCC_FTM1 &= ~(1U << 30); break;
//		case FTM2_e: PCC->PCC_FTM2 &= ~(1U << 30); break;
//		case FTM3_e: PCC->PCC_FTM3 &= ~(1U << 30); break;
//		case FTM4_e: PCC->PCC_FTM4 &= ~(1U << 30); break;
//		case FTM5_e: PCC->PCC_FTM5 &= ~(1U << 30); break;
//		case FTM6_e: PCC->PCC_FTM6 &= ~(1U << 30); break;
//		case FTM7_e: PCC->PCC_FTM7 &= ~(1U << 30); break;
//
//		case LPSPI0_e: PCC->PCC_LPSPI0 &= ~(1U << 30); break;
//		case LPSPI1_e: PCC->PCC_LPSPI1 &= ~(1U << 30); break;
//		case LPSPI2_e: PCC->PCC_LPSPI2 &= ~(1U << 30); break;
//	}
//
//}

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

void SPLL_ClockEnable(uint32 Divider1, uint32 Divider2, uint32 PreDiv, uint32 Multiply, uint32 InputClockSource){

	volatile uint32 temp = 0;

	while (SCG->SCG_SPLLCSR & (1U << 23));			/*Check if SPLL is unlocked*/

	temp &= ~(1U << 0);
	SCG->SCG_SPLLCSR = temp;					/*Disable SPLL clock to config*/

	temp = 0;
	temp |= (InputClockSource << 0);	/*Choose Input clock source for SPLL*/
	temp |= (Multiply << 16);					/*SPLL Multiplier*/
	temp |= (PreDiv << 8);						/*PreDiv*/
	SCG->SCG_SPLLCFG |= temp;

	temp = 0;
	temp |= ((Divider2 << 8) | (Divider1 << 0));
	SCG->SCG_SPLLDIV = temp;					/*Clock divider distribute 1 and 2*/

	temp = 0;
	temp |= (1U << 0);
	SCG->SCG_SPLLCSR = temp;					/*Enable SPLL clock*/

	while(!(SCG->SCG_SPLLCSR & (1U << 24)));		/*Wait to confirm status*/
}

void SystemClockConfig(uint32 ClockMode, uint32 DivCore, uint32 DivBus, uint32 DivSlow){
	
	volatile uint32 temp = 0;
	
	/*Config system clock*/
	
	//temp |= (ClockMode << 24); 		/*24th is the position to choose the System Clock Source called SCS*/

	//temp |= (DIVCORE_BY_(8) << 16); 	/*16th is the position to choose the divide core: normal DIV by 12*/

	//temp |= (DIVBUS_BY_(1) << 4);		/*4th is the position to choose the divide bus*/

	//temp |= (DIVSLOW_BY_(2) << 0);		/*0th is the position to choose the divide slow*/

	/*------------------------------------------NEW----------------------------------------------------------*/
	
	temp |= (ClockMode << 24); 	/*24th is the position to choose the System Clock Source called SCS*/

	temp |= (DivCore << 16); 	/*16th is the position to choose the divide core: normal DIV by 12*/

	temp |= (DivBus << 4);		/*4th is the position to choose the divide bus*/

	temp |= (DivSlow << 0);		/*0th is the position to choose the divide slow*/
	
	/*------------------------------------------NEW----------------------------------------------------------*/
	
	SCG->SCG_RCCR = temp;

	/*Test SCS bit of CSR register*/
	while (((SCG->SCG_CSR & 0xF000000) >> 24 ) != ClockMode);		/*1 is SOSC mode; 3 is fast mode; 6 is PLL mode*/

	//while ((SCG->SCG_CSR >> 24) != 6);
}

void CLOCK_SCG_ENABLE(void){

	/*Config system clock*/
	SCG->SCG_RCCR |= (SCS_FIRC_CLK << 24); 		/*24th is the position to choose the System Clock Source called SCS*/

	SCG->SCG_RCCR |= (DIVCORE_BY_(8) << 16); 	/*16th is the position to choose the divide core*/

	SCG->SCG_RCCR |= (DIVBUS_BY_(1) << 4);		/*4th is the position to choose the divide bus*/

	SCG->SCG_RCCR |= (DIVSLOW_BY_(2) << 0);		/*0th is the position to choose the divide slow*/

	/*Test SCS bit of CSR register*/
	while (((SCG->SCG_CSR & 0xF000000) >> 24 ) != 3);		/*3 is fast mode; 6 is PLL mode*/

	//while ((SCG->SCG_CSR >> 24) != 6);
}

void SCG_ClockOutSelect(uint32 CLKOUTCNFG_Mode){

	/*3 for FIRC; 6 for SPLL*/ /*If debugger does not jump in this line -> there are some problem in while loop*/

	SCG->SCG_CLKOUTCNFG |= (CLKOUTCNFG_Mode << 24);
}
