# 1 "C:/S32K/test_main.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 385 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/S32K/test_main.c" 2
# 1 "C:/S32K/S32K144xx.h" 1
# 188 "C:/S32K/S32K144xx.h"
typedef unsigned char uint8;




typedef unsigned short uint16;




typedef unsigned int uint32;




typedef struct
{
    volatile uint32 PDOR;
    volatile uint32 PSOR;
    volatile uint32 PCOR;
    volatile uint32 PTOR;
    volatile uint32 PDIR;
    volatile uint32 PDDR;
    volatile uint32 PIDR;
} GPIO_TypeDef;




typedef struct
{
    volatile uint32 PCR[32];
    volatile uint32 GPCLR;
    volatile uint32 GPCHR;
    volatile uint32 GICLR;
    volatile uint32 GICHR;
    uint32 reserve0[4];
    volatile uint32 ISFR;
    uint32 reserve1[7];
    volatile uint32 DFER;
    volatile uint32 DFCR;
    volatile uint32 DFWR;

} PORT_TypeDef;




typedef struct
{
    volatile uint32 CSR;
    volatile uint32 RVR;
    volatile uint32 CVR;
    volatile uint32 CALIB;

} SysTick_TypeDef;




typedef struct
{
    uint32 reserve0[32];
    volatile uint32 FTFC;
    volatile uint32 DMAMUX;
    uint32 reserve1[2];
    volatile uint32 FlexCAN0;
    volatile uint32 FlexCAN1;
    volatile uint32 FTM3;
    volatile uint32 ADC1;
    uint32 reserve2[3];
    volatile uint32 FlexCAN2;
    volatile uint32 LPSPI0;
    volatile uint32 LPSPI1;
    volatile uint32 LPSPI2;
    uint32 reserve3[2];
    volatile uint32 PDB1;
    volatile uint32 CRC;
    uint32 reserve4[3];
    volatile uint32 PDB0;
    volatile uint32 PCC_LPIT;
    volatile uint32 FTM0;
    volatile uint32 FTM1;
    volatile uint32 FTM2;
    volatile uint32 ADC0;
    uint32 reserve5;
    volatile uint32 RTC;
    uint32 reserve6[2];
    volatile uint32 LPTMR0;
    uint32 reserve7[8];
    volatile uint32 PORT[5];
    uint32 reserve8[6];
    volatile uint32 SAI0;
    volatile uint32 SAI1;
    uint32 reserve9[4];
    volatile uint32 FlexIO;
    uint32 reserve10[6];
    volatile uint32 EWM;
    uint32 reserve11[4];
    volatile uint32 LPI2C0;
    volatile uint32 LPI2C1;
    uint32 reserve12[2];
    volatile uint32 PCC_LPUART0;
    volatile uint32 PCC_LPUART1;
    volatile uint32 PCC_LPUART2;
    uint32 reserve13;
    volatile uint32 FTM4;
    volatile uint32 FTM5;
    volatile uint32 FTM6;
    volatile uint32 FTM7;
    uint32 reserve14;
    volatile uint32 CMP0;
    uint32 reserve15[2];
    volatile uint32 QSPI;
    uint32 reserve16[2];
    volatile uint32 ENET;
} PCC_TypeDef;




typedef struct {
     volatile uint32 ISER[8];
     uint8 reserve0[96];
     volatile uint32 ICER[8];
     uint8 reserve1[96];
     volatile uint32 ISPR[8];
     uint8 reserve2[96];
     volatile uint32 ICPR[8];
     uint8 reserve3[96];
     volatile uint32 IABR[8];
     uint8 reserve4[224];
     volatile uint8 IP[240];
     uint8 reserve5[2576];
     volatile uint32 STIR;
} NVIC_TypeDef;




typedef struct {
     volatile uint32 VERID;
     volatile uint32 PARAM;
     volatile uint32 GLOBAL;
     volatile uint32 PINCFG;
     volatile uint32 BAUD;
     volatile uint32 STAT;
     volatile uint32 CTRL;
     volatile uint32 DATA;
     volatile uint32 MATCH;
     volatile uint32 MODIR;
     volatile uint32 FIFO;
     volatile uint32 WATER;
} LPUART_TypeDef;





typedef struct {
    volatile const uint32 SCG_VERID;
    volatile const uint32 SCG_PARAM;
    uint32 dummy1[2];
    volatile const uint32 SCG_CSR;
    volatile uint32 SCG_RCCR;
    volatile uint32 SCG_VCCR;
    volatile uint32 SCG_HCCR;
    volatile uint32 SCG_CLKOUTCNFG;
    uint32 dummy2[55];
    volatile uint32 SCG_SOSCCSR;
    volatile uint32 SCG_SOSCDIV;
    volatile uint32 SCG_SOSCCFG;
    uint32 dummy3[61];
    volatile uint32 SCG_SIRCCSR;
    volatile uint32 SCG_SIRCDIV;
    volatile uint32 SCG_SIRCCFG;
    uint32 dummy4[61];
    volatile uint32 SCG_FIRCCSR;
    volatile uint32 SCG_FIRCDIV;
    volatile uint32 SCG_FIRCCFG;
    uint32 dummy5[189];
    volatile uint32 SCG_SPLLCSR;
    volatile uint32 SCG_SPLLDIV;
    volatile uint32 SCG_SPLLCFG;
} SCG_TypeDef;




typedef struct {
 volatile const uint32 VERID;
 volatile const uint32 PARAM;
 volatile uint32 MCR;
 volatile uint32 MSR;
 volatile uint32 MIER;
 volatile uint32 SETTEN;
 volatile uint32 CLRTEN;
 uint32 dummy1;
 struct{
        volatile uint32 TVAL;
        volatile const uint32 CVAL;
        volatile uint32 TCTRL;
        uint32 dummy2;
 }CHANNEL[4];
}LPIT_TypeDef;




typedef enum{
    PORTA_INDEX = 0U,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX,
}PORT_Index_TypeDef;
# 2 "C:/S32K/test_main.c" 2

int main(void)
{
 for (int i = 0; i < 24U; i++)
 {

 }

 while(1)
 {
 }
    return 0;
}
