/******************************************************************************
 * Project Name: S32K144 HEADER FILE
 * File Name:   S32K144xx.h
 *
 * Description: S32K144 base address, typedef, macros
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex-M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/
#ifndef INC_S32K144XX_H_
#define INC_S32K144XX_H_

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/


/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/**
 * @brief  Define genetic macros
 */
#define ENABLE                          1U
#define DISABLE                         0U
#define SET                             ENABLE
#define RESET                           DISABLE
#define GPIO_PIN_SET                    SET
#define GPIO_PIN_RESET                  RESET
#define NULL_PTR                        (DISABLE)
#define PIN_PULLUP                      0X01U
#define PIN_PULLDOWN                    0X02U

/**
* @brief    Define base address of PCC module
*/
#define PCC_BASE                0X40065000    
 
/**
* @brief    Define base address of PORT module
*/       
#define PORTA_BASE              0X40049000      
#define PORTB_BASE              0X4004A000
#define PORTC_BASE              0X4004B000
#define PORTD_BASE              0X4004C000
#define PORTE_BASE              0X4004D000

/**
* @brief    Define base address of GPIO module
*/
#define GPIOA_BASE              0X400FF000
#define GPIOB_BASE              0X400FF040
#define GPIOC_BASE              0X400FF080
#define GPIOD_BASE              0X400FF0C0
#define GPIOE_BASE              0X400FF100

/**
* @brief    Define base address of GPIO module
*/
#define NVIC_BASE               0XE000E100

/**
* @brief    Define base address of SysTick module
*/
#define Systick_BASE            0XE000E010

/**
* @brief    Define base address of LPUART module
*/
#define LPUART0_BASE            0X4006A000
#define LPUART1_BASE            0X4006B000 
#define LPUART2_BASE            0X4006C000

/**
* @brief    Define base address of SCG module
*/
#define SCG_BASE                0X40064000

/**
* @brief    Define base address of LPIT module
*/
#define LPIT_BASE               0X40037000

/**
* @brief    Define base address of LPIT module
*/
#define ADC0_BASE               0X4003B000
#define ADC1_BASE               0X40027000

/**
* @brief    Define structure pointer of PORT typedef
*/
#define PORTA                   ((PORT_TypeDef*)PORTA_BASE)
#define PORTB                   ((PORT_TypeDef*)PORTB_BASE)
#define PORTC                   ((PORT_TypeDef*)PORTC_BASE)
#define PORTD                   ((PORT_TypeDef*)PORTD_BASE)
#define PORTE                   ((PORT_TypeDef*)PORTE_BASE)

/**
* @brief    Define structure pointer of PCC typedef
*/
#define PCC                     ((PCC_TypeDef*)PCC_BASE)

/**
* @brief    Define structure pointer of GPIO typedef
*/
#define GPIOA                   ((GPIO_TypeDef*)GPIOA_BASE)
#define GPIOB                   ((GPIO_TypeDef*)GPIOB_BASE)
#define GPIOC                   ((GPIO_TypeDef*)GPIOC_BASE)
#define GPIOD                   ((GPIO_TypeDef*)GPIOD_BASE)
#define GPIOE                   ((GPIO_TypeDef*)GPIOE_BASE)

/**
* @brief    Define structure pointer of LPIT typedef
*/
#define LPIT                    ((LPIT_TypeDef*)LPIT_BASE)

/**
* @brief    Define structure pointer of NVIC typedef
*/
#define NVIC                    ((NVIC_TypeDef*)NVIC_BASE)

/**
* @brief    Define structure pointer of NVIC typedef
*/
#define SysTick                 ((SysTick_TypeDef*)Systick_BASE)

/**
* @brief    Define structure pointer of LPUART typedef
*/
#define LPUART0                 ((LPUART_TypeDef*)LPUART0_BASE)
#define LPUART1                 ((LPUART_TypeDef*)LPUART1_BASE)
#define LPUART2                 ((LPUART_TypeDef*)LPUART2_BASE)

/**
 * @brief  Define base address of SCG and macro pointer to SCG registers
 */
#define SCG                     ((SCG_TypeDef*) SCG_BASE)

/**
 * @brief  Define base address of ADC and macro pointer to ADC registers
 */
#define ADC0                    ((ADC_TypeDef*) ADC0_BASE)
#define ADC1                    ((ADC_TypeDef*) ADC1_BASE)

/**
* @brief    Define PCC bit fields masks
*/
#define PIN(X)                  (1 << X)
#define PCC_CGC_MASK            0x40000000u
#define PCC_CGC_SHIFT           30u
#define PCC_PCS_MASK            0x7000000u
#define PCC_PCS_SHIFT           24u
#define PCC_PR_MASK             (1 << 31)

/**
* @brief    Define PORT bit fields masks
*/
#define PORT_PCR_ISF_MASK       0X01000000U       /* Interrupt flag MASK */
#define PORT_PCR_IQRC_MASK      0X000F0000U       /* Interrupt configuration MASK */
#define PORT_PCR_MUX_MASK       0X00000700U       /* MUX select MASK */
#define PORT_PCR_DSE_MASK       0X00000040U       /* Drive strength enable MASK */
#define PORT_PCR_PFE_MASK       0X00000010U       /* Passive filter enable (external button) MASK */
#define PORT_PCR_PE_MASK        0X00000002U       /* Pull enable MASK */
#define PORT_PCR_PS_MASK        0X00000001U       /* Pullup Pulldown select MASK */

/**
* @brief    Define PORT bit fields shift
*/
#define PORT_PCR_ISF_SHIFT      24U                /* Interrupt flag SHIFT */
#define PORT_PCR_IQRC_SHIFT     16U                /* Interrupt configuration SHIFT */
#define PORT_PCR_MUX_SHIFT      8U                 /* MUX select SHIFT */
#define PORT_PCR_DSE_SHIFT      6U                 /* Drive strength enable SHIFT */
#define PORT_PCR_PFE_SHIFT      4U                 /* Passive filter enable (external button) SHIFT */
#define PORT_PCR_PE_SHIFT       1U                 /* Pull enable SHIFT */
#define PORT_PCR_PS_SHIFT       0U                 /* Pullup Pulldown select SHIFT */

/**
* @brief    Define PORT bit fields shift
*/
#define IRQC_LOW                8U                /* ISF flag and Interrupt when logic 0 */
#define IRQC_HIGH               12U               /* ISF flag and Interrupt when logic 1 */
#define IRQC_RE                 9U                /* ISF flag and Interrupt on rising-edge */
#define IRQC_FE                 10U               /* ISF flag and Interrupt on falling-edge */
#define IRQC_EE                 11U               /* ISF flag and Interrupt on either edge */


/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/
/**
* @brief  UNSIGNED INT 8 BIT
*/
typedef unsigned char 	uint8;

 /**
 * @brief  UNSIGNED INT 16 BIT
 */
typedef unsigned short 	uint16;

/**
* @brief  UNSIGNED INT 32 BIT
*/
typedef unsigned int	uint32;

/**
* @brief    Define structure of GPIO typedef
*/
typedef struct 
{
    volatile uint32 PDOR;                  /* Port Data Output Register */
    volatile uint32 PSOR;                  /* Port Set Output Register */
    volatile uint32 PCOR;                  /* Port Clear Output Register */
    volatile uint32 PTOR;                  /* Port Toggle Output Register */
    volatile uint32 PDIR;                  /* Port Data Input Register */
    volatile uint32 PDDR;                  /* Port Data Direction Register */
    volatile uint32 PIDR;                  /* Port Input Disable Register */
} GPIO_TypeDef;

/**
* @brief    Define structure of PORT typedef
*/
typedef struct 
{
    volatile uint32 PCR[32];               /* Pin Control Register [32], step = 0x4 */
    volatile uint32 GPCLR;                 /* Global Pin Control Low Register, OFFSET = 80h*/
    volatile uint32 GPCHR;                 /* Global Pin Control High Register, OFFSET = 84h*/
    volatile uint32 GICLR;                 /* Global Interrupt Control Low Register, OFFSET = 88h*/
    volatile uint32 GICHR;                 /* Global Interrupt Control High Register, OFFSET = 8Ch*/
    uint32 reserve0[4];    
    volatile uint32 ISFR;                  /* Interrupt Status Flag Register, OFFSET = A0h*/ 
    uint32 reserve1[7];    
    volatile uint32 DFER;                  /* Digital Filter Enable Register, OFFSET = C0h*/ 
    volatile uint32 DFCR;                  /* Digital Filter Clock Register, OFFSET = C4h*/ 
    volatile uint32 DFWR;                  /* Digital Filter Width Register, OFFSET = C8h*/ 

} PORT_TypeDef;

/**
* @brief    Define structure of SysTick typedef
*/
typedef struct 
{
    volatile uint32 CSR;                  /* SysTick Control and Status Register */
    volatile uint32 RVR;                 /* SysTick Reload Value Register */
    volatile uint32 CVR;                 /* SysTick Currrent Value Register */
    volatile uint32 CALIB;               /* SysTick Calibration Calibration Register */

} SysTick_TypeDef;

/**
* @brief    Define structure of PCC typedef
*/
typedef struct 
{
    uint32 reserve0[32];         
    volatile uint32 FTFC;                  /* PCC FTFC Register, OFFSET = 80h*/
    volatile uint32 DMAMUX;                /* PCC DMAMUX Register, OFFSET = 84h*/      
    uint32 reserve1[2];                      
    volatile uint32 FlexCAN0;              /* PCC FlexCAN0 Register, OFFSET = 90h*/        
    volatile uint32 FlexCAN1;              /* PCC FlexCAN1 Register, OFFSET = 94h*/        
    volatile uint32 FTM3;                  /* PCC FTM3 Register, OFFSET = 98h*/     
    volatile uint32 PCC_ADC1;                  /* PCC ADC1 Register, OFFSET = 9Ch*/ 
    uint32 reserve2[3];                 
    volatile uint32 FlexCAN2;              /* PCC FlexCAN2 Register, OFFSET = ACh*/   
    volatile uint32 LPSPI0;                /* PCC LPSPI0 Register, OFFSET = B0h*/    
    volatile uint32 LPSPI1;                /* PCC LPSPI1 Register, OFFSET = B4h*/   
    volatile uint32 LPSPI2;                /* PCC LPSPI2 Register, OFFSET = B8h*/   
    uint32 reserve3[2];            
    volatile uint32 PDB1;                  /* PCC PDB1 Register, OFFSET = C4h*/   
    volatile uint32 CRC;                   /* PCC CRC Register, OFFSET = C8h*/   
    uint32 reserve4[3];                 
    volatile uint32 PDB0;                  /* PCC PDB0 Register, OFFSET = D8h*/   
    volatile uint32 PCC_LPIT;                  /* PCC LPIT Register, OFFSET = DCh*/  
    volatile uint32 FTM0;                  /* PCC FTM0 Register, OFFSET = E0h*/  
    volatile uint32 FTM1;                  /* PCC FTM1 Register, OFFSET = E4h*/  
    volatile uint32 FTM2;                  /* PCC FTM2 Register, OFFSET = E8h*/  
    volatile uint32 PCC_ADC0;                  /* PCC ADC0 Register, OFFSET = ECh*/  
    uint32 reserve5;                 
    volatile uint32 RTC;                   /* PCC RTC Register, OFFSET = F4h*/  
    uint32 reserve6[2];                 
    volatile uint32 LPTMR0;                /* PCC LPTMR0 Register, OFFSET = 100h*/  
    uint32 reserve7[8];                 
    volatile uint32 PORT[5];               /* PCC PORT[A,B,C,D,E] Register, OFFSET = 124h-134h*/  
    uint32 reserve8[6];                 
    volatile uint32 SAI0;                  /* PCC SAI0 Register, OFFSET = 150h*/  
    volatile uint32 SAI1;                  /* PCC SAI1 Register, OFFSET = 154h*/  
    uint32 reserve9[4];                 
    volatile uint32 FlexIO;                /* PCC FlexIO Register, OFFSET = 168h*/  
    uint32 reserve10[6];                 
    volatile uint32 EWM;                   /* PCC EWM Register, OFFSET = 184h*/  
    uint32 reserve11[4];                 
    volatile uint32 LPI2C0;                /* PCC LPI2C0 Register, OFFSET = 198h*/  
    volatile uint32 LPI2C1;                /* PCC LPI2C1 Register, OFFSET = 19Ch*/  
    uint32 reserve12[2];                 
    volatile uint32 PCC_LPUART0;          /* PCC LPUART0 Register, OFFSET = 1A8h*/  
    volatile uint32 PCC_LPUART1;          /* PCC LPUART1 Register, OFFSET = 1ACh*/  
    volatile uint32 PCC_LPUART2;          /* PCC LPUART2 Register, OFFSET = 1B0h*/  
    uint32 reserve13;                 
    volatile uint32 FTM4;                  /* PCC FTM4 Register, OFFSET = 1B8h*/  
    volatile uint32 FTM5;                  /* PCC FTM5 Register, OFFSET = 1BCh*/  
    volatile uint32 FTM6;                  /* PCC FTM6 Register, OFFSET = 1C0h*/  
    volatile uint32 FTM7;                  /* PCC FTM7 Register, OFFSET = 1C4h*/  
    uint32 reserve14;                 
    volatile uint32 CMP0;                  /* PCC CMP0 Register, OFFSET = 1CCh*/  
    uint32 reserve15[2];                 
    volatile uint32 QSPI;                  /* PCC QSPI Register, OFFSET = 1D8h*/  
    uint32 reserve16[2];                 
    volatile uint32 ENET;                  /* PCC ENET Register, OFFSET = 1E4h*/  
} PCC_TypeDef;

/**
* @brief    Define structure of NVIC typedef
*/
typedef struct {
     volatile uint32 ISER[8];         /* Interrupt Set Enable Register n, array offset: 0x0, array step: 0x4 */
     uint8 reserve0[96];
     volatile uint32 ICER[8];         /* Interrupt Clear Enable Register n, array offset: 0x80, array step: 0x4 */
     uint8 reserve1[96];
     volatile uint32 ISPR[8];         /* Interrupt Set Pending Register n, array offset: 0x100, array step: 0x4 */
     uint8 reserve2[96];
     volatile uint32 ICPR[8];         /* Interrupt Clear Pending Register n, array offset: 0x180, array step: 0x4 */
     uint8 reserve3[96];
     volatile uint32 IABR[8];         /* Interrupt Active bit Register n, array offset: 0x200, array step: 0x4 */
     uint8 reserve4[224];
     volatile uint8 IP[240];          /* Interrupt Priority Register n, array offset: 0x300, array step: 0x1 */
     uint8 reserve5[2576];
     volatile  uint32 STIR;           /* Software Trigger Interrupt Register, offset: 0xE00 */
} NVIC_TypeDef;

/**
* @brief    Define structure of LPUART typedef
*/
typedef struct {
     volatile uint32 VERID;         /* Version ID Register */
     volatile uint32 PARAM;         /* Parameter Register (PARAM) */
     volatile uint32 GLOBAL;        /* LPUART Global Register (GLOBAL) */
     volatile uint32 PINCFG;        /* LPUART Pin Configuration Register (PINCFG) */
     volatile uint32 BAUD;          /* LPUART Baud Rate Register (BAUD) */
     volatile uint32 STAT;          /* LPUART Status Register (STAT) */
     volatile uint32 CTRL;          /* LPUART Control Register (CTRL) */    
     volatile uint32 DATA;          /* LPUART Data Register (DATA) */
     volatile uint32 MATCH;         /* LPUART Match Address Register (MATCH) */
     volatile uint32 MODIR;         /* LPUART Modem IrDA Register (MODIR) */
     volatile uint32 FIFO;          /* LPUART FIFO Register (FIFO) */
     volatile uint32 WATER;         /* LPUART Watermark Register (WATER) */
} LPUART_TypeDef;


/**
* @brief  SCG
*/
typedef struct {
    volatile const 	uint32 SCG_VERID;       /**< Version ID Register, offset: 0x0 */
    volatile const 	uint32 SCG_PARAM;       /**< Parameter Register, offset: 0x4 */
    uint32 					dummy1[2];
    volatile const 	uint32 SCG_CSR;         /**< Clock Status Register, offset: 0x10 */
    volatile uint32 SCG_RCCR;               /**< Run Clock Control Register, offset: 0x14 */
    volatile uint32 SCG_VCCR;               /**< VLPR Clock Control Register, offset: 0x18 */
    volatile uint32 SCG_HCCR;               /**< HSRUN Clock Control Register, offset: 0x1C */
    volatile uint32 SCG_CLKOUTCNFG;         /**< SCG CLKOUT Configuration Register, offset: 0x20 */
    uint32 					dummy2[55];
    volatile uint32 SCG_SOSCCSR;            /**< System OSC Control Status Register, offset: 0x100 */
    volatile uint32 SCG_SOSCDIV;            /**< System OSC Divide Register, offset: 0x104 */
    volatile uint32 SCG_SOSCCFG;            /**< System Oscillator Configuration Register, offset: 0x108 */
    uint32 					dummy3[61];
    volatile uint32 SCG_SIRCCSR;            /**< Slow IRC Control Status Register, offset: 0x200 */
    volatile uint32 SCG_SIRCDIV;            /**< Slow IRC Divide Register, offset: 0x204 */
    volatile uint32 SCG_SIRCCFG;            /**< Slow IRC Configuration Register, offset: 0x208 */
    uint32 					dummy4[61];
    volatile uint32 SCG_FIRCCSR;            /**< Fast IRC Control Status Register, offset: 0x300 */
    volatile uint32 SCG_FIRCDIV;            /**< Fast IRC Divide Register, offset: 0x304 */
    volatile uint32 SCG_FIRCCFG;            /**< Fast IRC Configuration Register, offset: 0x308 */
    uint32 					dummy5[189];
    volatile uint32 SCG_SPLLCSR;            /**< System PLL Control Status Register, offset: 0x600 */
    volatile uint32 SCG_SPLLDIV;            /**< System PLL Divide Register, offset: 0x604 */
    volatile uint32 SCG_SPLLCFG;            /**< System PLL Configuration Register, offset: 0x608 */
} SCG_TypeDef;

/**
* @brief  Define structure of LPIT typedef
*/
typedef struct {
	volatile const uint32 VERID;            /**< Version ID Register, offset: 0x0 */
	volatile const uint32 PARAM;            /**< Parameter Register, offset: 0x4 */
	volatile uint32 MCR;                    /**< Module Control Register, offset: 0x8 */
	volatile uint32 MSR;                    /**< Module Status Register, offset: 0xC */
	volatile uint32 MIER;                   /**< Module Interrupt Enable Register, offset: 0x10 */
	volatile uint32 SETTEN;                 /**< Set Timer Enable Register, offset: 0x14 */
	volatile uint32 CLRTEN;                 /**< Clear Timer Enable Register, offset: 0x18 */
	uint32 dummy1;
	struct{                                 /* offset: 0x20, array step: 0x10 */
        volatile uint32 TVAL;               /**< Timer Value Register, array offset: 0x20, array step: 0x10 */
        volatile const uint32 CVAL;         /**< Current Timer Value, array offset: 0x24, array step: 0x10 */
        volatile uint32 TCTRL;              /**< Timer Control Register, array offset: 0x28, array step: 0x10 */
        uint32 dummy2;
	}CHANNEL[4];
}LPIT_TypeDef;

/**
* @brief  Define structure of ADC typedef
*/
typedef struct {
    volatile uint32 SC1[16];                           /**< ADC Status and Control Register 1, array offset: 0x0, array step: 0x4 */
    volatile uint32 CFG1;                              /**< ADC Configuration Register 1, offset: 0x40 */
    volatile uint32 CFG2;                              /**< ADC Configuration Register 2, offset: 0x44 */
    volatile uint32 R[16];                             /**< ADC Data Result Registers, array offset: 0x48, array step: 0x4 */
    volatile uint32 CV[2];                             /**< Compare Value Registers, array offset: 0x88, array step: 0x4 */
    volatile uint32 SC2;                               /**< Status and Control Register 2, offset: 0x90 */
    volatile uint32 SC3;                               /**< Status and Control Register 3, offset: 0x94 */
    volatile uint32 BASE_OFS;                          /**< BASE Offset Register, offset: 0x98 */
    volatile uint32 OFS;                               /**< ADC Offset Correction Register, offset: 0x9C */
    volatile uint32 USR_OFS;                           /**< USER Offset Correction Register, offset: 0xA0 */
    volatile uint32 XOFS;                              /**< ADC X Offset Correction Register, offset: 0xA4 */
    volatile uint32 YOFS;                              /**< ADC Y Offset Correction Register, offset: 0xA8 */
    volatile uint32 G;                                 /**< ADC Gain Register, offset: 0xAC */
    volatile uint32 UG;                                /**< ADC User Gain Register, offset: 0xB0 */
    volatile uint32 CLPS;                              /**< ADC General Calibration Value Register S, offset: 0xB4 */
    volatile uint32 CLP3;                              /**< ADC Plus-Side General Calibration Value Register 3, offset: 0xB8 */
    volatile uint32 CLP2;                              /**< ADC Plus-Side General Calibration Value Register 2, offset: 0xBC */
    volatile uint32 CLP1;                              /**< ADC Plus-Side General Calibration Value Register 1, offset: 0xC0 */
    volatile uint32 CLP0;                              /**< ADC Plus-Side General Calibration Value Register 0, offset: 0xC4 */
    volatile uint32 CLPX;                              /**< ADC Plus-Side General Calibration Value Register X, offset: 0xC8 */
    volatile uint32 CLP9;                              /**< ADC Plus-Side General Calibration Value Register 9, offset: 0xCC */
    volatile uint32 CLPS_OFS;                          /**< ADC General Calibration Offset Value Register S, offset: 0xD0 */
    volatile uint32 CLP3_OFS;                          /**< ADC Plus-Side General Calibration Offset Value Register 3, offset: 0xD4 */
    volatile uint32 CLP2_OFS;                          /**< ADC Plus-Side General Calibration Offset Value Register 2, offset: 0xD8 */
    volatile uint32 CLP1_OFS;                          /**< ADC Plus-Side General Calibration Offset Value Register 1, offset: 0xDC */
    volatile uint32 CLP0_OFS;                          /**< ADC Plus-Side General Calibration Offset Value Register 0, offset: 0xE0 */
    volatile uint32 CLPX_OFS;                          /**< ADC Plus-Side General Calibration Offset Value Register X, offset: 0xE4 */
    volatile uint32 CLP9_OFS;                          /**< ADC Plus-Side General Calibration Offset Value Register 9, offset: 0xE8 */
} ADC_TypeDef;


/**
* @brief    Define structure of PORT index
*/
typedef enum{
    PORTA_INDEX = 0U,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX,
}PORT_Index_TypeDef;

/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPE
 *****************************************************************************/



#endif /* INC_S32K144XX_H_ */
