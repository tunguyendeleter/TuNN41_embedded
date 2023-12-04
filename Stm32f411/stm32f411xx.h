#ifndef INC_STM32F411XX_H_
#define INC_STM32F411XX_H_

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include <stdint.h>

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/**
 * @brief  Define genetic macros
 */
#define ENABLE 							1
#define DISABLE 						0
#define SET 							ENABLE
#define RESET 							DISABLE
#define GPIO_PIN_SET 					SET
#define GPIO_PIN_RESET 					RESET

/**
 * @brief  Define portcode function for given GPIOx peripheral
 */
#define GPIO_BASEADDR_TO_CODE(x)		((x == GPIOA)?0:\
										 (x == GPIOB)?1:\
										 (x == GPIOC)?2:\
										 (x == GPIOD)?3:\
										 (x == GPIOE)?4:\
										 (x == GPIOH)?5:0)

/**
 * @brief  Define base address of FLASH, SRAM, system memory
 */
#define FLASH_BASEADDR					0x08000000U				/*Flash base address*/
#define SRAM1_BASEADDR					0x20000000U 			/*SRAM1 base address*/
#define SRAM							(SRAM1_BASEADDR) 		/*SRAM base address*/
#define ROM_BASEADDR					0x1FFF0000U 			/*System memory base address*/

/**
 * @brief  Define base address of peripheral, APB1, APB2, AHB1 buses
 */
#define PERIPH_BASEADDR					0x40000000U				/*Peripheral base address*/
#define APB1_BASEADDR					PERIPH_BASEADDR			/*APB1 Bus base address*/
#define APB2_BASEADDR					0x40010000U				/*APB2 Bus base address*/
#define AHB1_BASEADDR					0x40020000U				/*AHB1 Bus base address*/

/**
 * @brief  Define base address of GPIOx x:(A-H)
 */
#define GPIOA_BASEADDR					(AHB1_BASEADDR + 0x0000)				/*GPIOA base address*/
#define GPIOB_BASEADDR					(AHB1_BASEADDR + 0x0400)				/*GPIOB base address*/
#define GPIOC_BASEADDR					(AHB1_BASEADDR + 0x0800)				/*GPIOC base address*/
#define GPIOD_BASEADDR					(AHB1_BASEADDR + 0x0C00)				/*GPIOD base address*/
#define GPIOE_BASEADDR					(AHB1_BASEADDR + 0x1000)				/*GPIOE base address*/
#define GPIOH_BASEADDR					(AHB1_BASEADDR + 0x1C00)				/*GPIOH base address*/
#define GPIOA							((GPIO_Type*)GPIOA_BASEADDR)			/*GPIOA register pointer*/
#define GPIOB							((GPIO_Type*)GPIOB_BASEADDR)			/*GPIOB register pointer*/
#define GPIOC							((GPIO_Type*)GPIOC_BASEADDR)			/*GPIOC register pointer*/
#define GPIOD							((GPIO_Type*)GPIOD_BASEADDR)			/*GPIOD register pointer*/
#define GPIOE							((GPIO_Type*)GPIOE_BASEADDR)			/*GPIOE register pointer*/
#define GPIOH							((GPIO_Type*)GPIOH_BASEADDR)			/*GPIOH register pointer*/

/**
 * @brief  Define base address of I2C modules
 */
#define I2C1_BASEADDR					(APB1_BASEADDR + 0x5400)				/*I2C1 base address*/
#define I2C2_BASEADDR					(APB1_BASEADDR + 0x5800)				/*I2C2 base address*/
#define I2C3_BASEADDR					(APB1_BASEADDR + 0x5C00)				/*I2C3 base address*/

/**
 * @brief  Define base address of TIM modules
 */
#define TIM2_BASEADDR					(APB1_BASEADDR + 0x0000)				/*TIM2 base address*/
#define TIM3_BASEADDR					(APB1_BASEADDR + 0x0400)				/*TIM3 base address*/
#define TIM4_BASEADDR					(APB1_BASEADDR + 0x0800)				/*TIM4 base address*/
#define TIM5_BASEADDR					(APB1_BASEADDR + 0x0C00)				/*TIM5 base address*/
#define TIM9_BASEADDR					(APB2_BASEADDR + 0x4000)				/*TIM9 base address*/
#define TIM10_BASEADDR					(APB2_BASEADDR + 0x4400)				/*TIM10 base address*/
#define TIM11_BASEADDR					(APB2_BASEADDR + 0x4800)				/*TIM11 base address*/

/**
 * @brief  Define base address of USART modules
 */
#define USART1_BASEADDR					(APB2_BASEADDR + 0x1000)				/*USART1 base address*/
#define USART2_BASEADDR					(APB1_BASEADDR + 0x4400)				/*USART2 base address*/
#define USART6_BASEADDR					(APB2_BASEADDR + 0x1400)				/*USART6 base address*/

/**
 * @brief  Define base address of SPI modules
 */
#define SPI2_BASEADDR					(APB1_BASEADDR + 0x3800)				/*SPI2 base address*/
#define SPI3_BASEADDR					(APB1_BASEADDR + 0x3C00)				/*SPI3 base address*/
#define SPI1_BASEADDR					(APB2_BASEADDR + 0x3000)				/*SPI1 base address*/
#define SPI4_BASEADDR					(APB2_BASEADDR + 0x3400)				/*SPI4 base address*/
#define SPI5_BASEADDR					(APB2_BASEADDR + 0x5000)				/*SPI5 base address*/

/**
 * @brief  Define base address of RCC module
 */
#define RCC_BASEADDR					(AHB1_BASEADDR + 0x3800)				/*RCC base address*/
#define RCC								((RCC_Type*)RCC_BASEADDR)				/*RCC register pointer*/

/**
 * @brief  Define base address of EXTI module
 */
#define EXTI_BASEADDR					(APB2_BASEADDR + 0x3C00)				/*EXTI base address*/
#define EXTI							((EXTI_Type*)EXTI_BASEADDR)				/*EXTI register pointer*/

/**
 * @brief  Define base address of SYSCFG module
 */
#define SYSCFG_BASEADDR					(APB2_BASEADDR + 0x3800)				/*SYSCFG base address*/
#define SYSCFG							((SYSCFG_Type*)SYSCFG_BASEADDR)			/*SYSCFG register pointer*/

/**
 * @brief  Define base address of SYSCFG module
 */
#define Systick_BASEADDR				(0XE000E010)							/*SYSTICK base address*/
#define SysTick							((SysTick_TypeDef*)Systick_BASEADDR)	/*SYSTICK register pointer*/

/**
* @brief  define address of NVIC layer
*/
#define NVIC_BASEADDR					0xE000E100								/*NVIC base address*/
#define NVIC							((NVIC_Type*)NVIC_BASEADDR)				/*NVIC register pointer*/

/**
 * @brief  Define GPIOx clock enable and disable macros
 */
#define PORTA_CLK_EN()					(RCC->AHB1ENR |= (1 << 0))				/*enable peripheral clock at PORTA*/
#define PORTB_CLK_EN()					(RCC->AHB1ENR |= (1 << 1))				/*enable peripheral clock at PORTB*/
#define PORTC_CLK_EN()					(RCC->AHB1ENR |= (1 << 2))				/*enable peripheral clock at PORTC*/
#define PORTD_CLK_EN()					(RCC->AHB1ENR |= (1 << 3))				/*enable peripheral clock at PORTD*/
#define PORTE_CLK_EN()					(RCC->AHB1ENR |= (1 << 4))				/*enable peripheral clock at PORTE*/
#define PORTH_CLK_EN()					(RCC->AHB1ENR |= (1 << 7))				/*enable peripheral clock at PORTH*/

#define PORTA_CLK_DIS()					(RCC->AHB1ENR &= ~(1 << 0))				/*disable peripheral clock at PORTA*/
#define PORTB_CLK_DIS()					(RCC->AHB1ENR &= ~(1 << 1))				/*disable peripheral clock at PORTB*/
#define PORTC_CLK_DIS()					(RCC->AHB1ENR &= ~(1 << 2))				/*disable peripheral clock at PORTC*/
#define PORTD_CLK_DIS()					(RCC->AHB1ENR &= ~(1 << 3))				/*disable peripheral clock at PORTD*/
#define PORTE_CLK_DIS()					(RCC->AHB1ENR &= ~(1 << 4))				/*disable peripheral clock at PORTE*/
#define PORTH_CLK_DIS()					(RCC->AHB1ENR &= ~(1 << 7))				/*disable peripheral clock at PORTH*/

/**
 * @brief  Define TIMx clock enable and disable macros
 */
#define TIM2_CLK_EN()					(RCC->APB1ENR |= (1 << 0))				/*enable peripheral clock at TIM2*/
#define TIM3_CLK_EN()					(RCC->APB1ENR |= (1 << 1))				/*enable peripheral clock at TIM3*/
#define TIM4_CLK_EN()					(RCC->APB1ENR |= (1 << 2))				/*enable peripheral clock at TIM4*/
#define TIM5_CLK_EN()					(RCC->APB1ENR |= (1 << 3))				/*enable peripheral clock at TIM5*/
#define TIM9_CLK_EN()					(RCC->APB2ENR |= (1 << 16))				/*enable peripheral clock at TIM9*/
#define TIM10_CLK_EN()					(RCC->APB2ENR |= (1 << 17))				/*enable peripheral clock at TIM10*/
#define TIM11_CLK_EN()					(RCC->APB2ENR |= (1 << 18))				/*enable peripheral clock at TIM11*/

#define TIM2_CLK_DIS()					(RCC->APB1ENR &= ~(1 << 0))				/*disable peripheral clock at TIM2*/
#define TIM3_CLK_DIS()					(RCC->APB1ENR &= ~(1 << 1))				/*disable peripheral clock at TIM3*/
#define TIM4_CLK_DIS()					(RCC->APB1ENR &= ~(1 << 2))				/*disable peripheral clock at TIM4*/
#define TIM5_CLK_DIS()					(RCC->APB1ENR &= ~(1 << 3))				/*disable peripheral clock at TIM5*/
#define TIM9_CLK_DIS()					(RCC->APB2ENR &= ~(1 << 16))			/*disable peripheral clock at TIM9*/
#define TIM10_CLK_DIS()					(RCC->APB2ENR &= ~(1 << 17))			/*disable peripheral clock at TIM10*/
#define TIM11_CLK_DIS()					(RCC->APB2ENR &= ~(1 << 18))			/*disable peripheral clock at TIM11*/

/**
 * @brief  Define I2Cx clock enable and disable macros
 */
#define I2C1_CLK_EN()					(RCC->APB1ENR |= (1 << 21))				/*enable peripheral clock at I2C1*/
#define I2C2_CLK_EN()					(RCC->APB1ENR |= (1 << 22))				/*enable peripheral clock at I2C2*/
#define I2C3_CLK_EN()					(RCC->APB1ENR |= (1 << 23))				/*enable peripheral clock at I2C3*/

#define I2C1_CLK_DIS()					(RCC->APB1ENR &= ~(1 << 21))			/*disable peripheral clock at I2C1*/
#define I2C2_CLK_DIS()					(RCC->APB1ENR &= ~(1 << 22))			/*disable peripheral clock at I2C2*/
#define I2C3_CLK_DIS()					(RCC->APB1ENR &= ~(1 << 23))			/*disable peripheral clock at I2C3*/

/**
 * @brief  Define SPIx clock enable and disable macros
 */
#define SPI1_CLK_EN()					(RCC->APB2ENR |= (1 << 12))				/*enable peripheral clock at SPI1*/
#define SPI2_CLK_EN()					(RCC->APB1ENR |= (1 << 14))				/*enable peripheral clock at SPI2*/
#define SPI3_CLK_EN()					(RCC->APB1ENR |= (1 << 15))				/*enable peripheral clock at SPI3*/
#define SPI5_CLK_EN()					(RCC->APB2ENR |= (1 << 20))				/*enable peripheral clock at SPI5*/

#define SPI1_CLK_DIS()					(RCC->APB2ENR &= ~(1 << 12))			/*disable peripheral clock at SPI1*/
#define SPI2_CLK_DIS()					(RCC->APB1ENR &= ~(1 << 14))			/*disable peripheral clock at SPI2*/
#define SPI3_CLK_DIS()					(RCC->APB1ENR &= ~(1 << 15))			/*disable peripheral clock at SPI3*/
#define SPI5_CLK_DIS()					(RCC->APB2ENR &= ~(1 << 20))			/*disable peripheral clock at SPI5*/

/**
 * @brief  Define USARTx clock enable and disable macros
 */
#define USART1_CLK_EN()					(RCC->APB2ENR |= (1 << 4))				/*enable peripheral clock at USART1*/
#define USART2_CLK_EN()					(RCC->APB1ENR |= (1 << 17))				/*enable peripheral clock at USART2*/
#define USART6_CLK_EN()					(RCC->APB2ENR |= (1 << 5))				/*enable peripheral clock at USART6*/

#define USART1_CLK_DIS()				(RCC->APB2ENR &= ~(1 << 4))				/*disable peripheral clock at USART1*/
#define USART2_CLK_DIS()				(RCC->APB1ENR &= ~(1 << 17))			/*disable peripheral clock at USART2*/
#define USART6_CLK_DIS()				(RCC->APB2ENR &= ~(1 << 5))				/*disable peripheral clock at USART6*/

/**
 * @brief  Define System configuration controller clock enable and disable macros
 */
#define SYSCFG_CLK_EN()					(RCC->APB2ENR |= (1 << 14))				/*enable peripheral clock at SYSCFG*/
#define SYSCFG_CLK_DIS()				(RCC->APB2ENR &= ~(1 << 14))			/*disable peripheral clock at SYSCFG*/

/**
 * @brief  Define macros to reset peripheral GPIOx
 */
#define GPIOA_REG_RESET()			do{(RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0));}while(0)	/*reset register at GPIOA*/
#define GPIOB_REG_RESET()			do{(RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1));}while(0)	/*reset register at GPIOB*/
#define GPIOC_REG_RESET()			do{(RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2));}while(0)	/*reset register at GPIOC*/
#define GPIOD_REG_RESET()			do{(RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3));}while(0)	/*reset register at GPIOD*/
#define GPIOE_REG_RESET()			do{(RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4));}while(0)	/*reset register at GPIOE*/
#define GPIOH_REG_RESET()			do{(RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~(1 << 7));}while(0)	/*reset register at GPIOH*/

/**
 * @brief  Define macros to reset peripheral TIMx
 */
#define TIM1_REG_RESET()			do{(RCC->APB2RSTR |= (1 << 0)); (RCC->APB2RSTR &= ~(1 << 0));}while(0)	/*reset register at TIM1*/
#define TIM2_REG_RESET()			do{(RCC->APB1RSTR |= (1 << 0)); (RCC->APB1RSTR &= ~(1 << 0));}while(0)	/*reset register at TIM2*/
#define TIM3_REG_RESET()			do{(RCC->APB1RSTR |= (1 << 1)); (RCC->APB1RSTR &= ~(1 << 1));}while(0)	/*reset register at TIM3*/
#define TIM4_REG_RESET()			do{(RCC->APB1RSTR |= (1 << 2)); (RCC->APB1RSTR &= ~(1 << 2));}while(0)	/*reset register at TIM4*/
#define TIM5_REG_RESET()			do{(RCC->APB1RSTR |= (1 << 3)); (RCC->APB1RSTR &= ~(1 << 3));}while(0)	/*reset register at TIM5*/
#define TIM9_REG_RESET()			do{(RCC->APB2RSTR |= (1 << 16)); (RCC->APB2RSTR &= ~(1 << 16));}while(0)	/*reset register at TIM9*/
#define TIM10_REG_RESET()			do{(RCC->APB2RSTR |= (1 << 17)); (RCC->APB2RSTR &= ~(1 << 17));}while(0)	/*reset register at TIM10*/
#define TIM11_REG_RESET()			do{(RCC->APB2RSTR |= (1 << 18)); (RCC->APB2RSTR &= ~(1 << 18));}while(0)	/*reset register at TIM11*/

/**
 * @brief  Define macros to reset peripheral SPIx
 */
#define SPI1_REG_RESET()			do{(RCC->APB2RSTR |= (1 << 12)); (RCC->APB2RSTR &= ~(1 << 12));}while(0)	/*reset register at SPI1*/
#define SPI2_REG_RESET()			do{(RCC->APB1RSTR |= (1 << 14)); (RCC->APB1RSTR &= ~(1 << 14));}while(0)	/*reset register at SPI2*/
#define SPI3_REG_RESET()			do{(RCC->APB1RSTR |= (1 << 15)); (RCC->APB1RSTR &= ~(1 << 15));}while(0)	/*reset register at SPI3*/
#define SPI4_REG_RESET()			do{(RCC->APB2RSTR |= (1 << 13)); (RCC->APB2RSTR &= ~(1 << 13));}while(0)	/*reset register at SPI4*/
#define SPI5_REG_RESET()			do{(RCC->APB2RSTR |= (1 << 20)); (RCC->APB2RSTR &= ~(1 << 20));}while(0)	/*reset register at SPI5*/

/**
 * @brief  Define macros to reset peripheral I2Cx
 */
#define I2C1_REG_RESET()			do{(RCC->APB1RSTR |= (1 << 21)); (RCC->APB1RSTR &= ~(1 << 21));}while(0)	/*reset register at I2C1*/
#define I2C2_REG_RESET()			do{(RCC->APB1RSTR |= (1 << 22)); (RCC->APB1RSTR &= ~(1 << 22));}while(0)	/*reset register at I2C2*/
#define I2C3_REG_RESET()			do{(RCC->APB1RSTR |= (1 << 23)); (RCC->APB1RSTR &= ~(1 << 23));}while(0)	/*reset register at I2C3*/

/**
 * @brief  Define macros to reset peripheral USARTx
 */
#define USART1_REG_RESET()			do{(RCC->APB2RSTR |= (1 << 4)); (RCC->APB2RSTR &= ~(1 << 4));}while(0)		/*reset register at USART1*/
#define USART2_REG_RESET()			do{(RCC->APB1RSTR |= (1 << 17)); (RCC->APB1RSTR &= ~(1 << 17));}while(0)	/*reset register at USART2*/
#define USART6_REG_RESET()			do{(RCC->APB2RSTR |= (1 << 5)); (RCC->APB2RSTR &= ~(1 << 5));}while(0)		/*reset register at USART6*/


/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/
/**
* @brief  UNSIGNED INT 8 BIT
*/
typedef uint8_t 	uint8;

 /**
 * @brief  UNSIGNED INT 16 BIT
 */
typedef uint16_t 	uint16;

/**
* @brief  UNSIGNED INT 32 BIT
*/
typedef uint32_t	uint32;

/**
* @brief structure of GPIO register
*/
typedef struct{
	volatile uint32 MODER;
	volatile uint32 OTYPER;
	volatile uint32 OSPEEDR;
	volatile uint32 PUPDR;
	volatile uint32 IDR;
	volatile uint32 ODR;
	volatile uint32 BSRR;
	volatile uint32 LCKR;
	volatile uint32 AFR[2];
}GPIO_Type;

/**
* @brief structure of RCC register
*/
typedef struct{
	volatile uint32 CR;
	volatile uint32 PLLCFGR;
	volatile uint32 CFGR;
	volatile uint32 CIR;
	volatile uint32 AHB1RSTR;
	volatile uint32 AHB2RSTR;
	uint32 reversed1[2];
	volatile uint32 APB1RSTR;
	volatile uint32 APB2RSTR;
	uint32 reversed2[2];
	volatile uint32 AHB1ENR;
	volatile uint32 AHB2ENR;
	uint32 reversed3[2];
	volatile uint32 APB1ENR;
	volatile uint32 APB2ENR;
	uint32 reversed4[2];
	volatile uint32 AHB1LPENR;
	volatile uint32 AHB2LPENR;
	uint32 reversed5[2];
	volatile uint32 APB1LPENR;
	volatile uint32 APB2LPENR;
	uint32 reversed6[2];
	volatile uint32 BDCR;
	volatile uint32 CSR;
	uint32 reversed7[2];
	volatile uint32 SSCGR;
	volatile uint32 PLLI2SCFGR;
	uint32 reversed8;
	volatile uint32 DCKCFGR;
}RCC_Type;

/**
* @brief structure of EXTI register
*/
typedef struct{
	volatile uint32 IMR;
	volatile uint32 EMR;
	volatile uint32 RTSR;
	volatile uint32 FTSR;
	volatile uint32 SWIER;
	volatile uint32 PR;
}EXTI_Type;

/**
* @brief structure of SYSCFG register
*/
typedef struct{
	volatile uint32 MEMRMP;					/*address offset: 0x00*/
	volatile uint32 PMC;					/*address offset: 0x04*/
	volatile uint32 EXTICR[4];				/*address offset: 0x08-0x14*/
	uint32 reserved[2];						/*reserved: 0x18-0x1C*/
	volatile uint32 CMPCR;					/*address offset: 0x20*/
}SYSCFG_Type;

/**
* @brief  structure of NVIC ARM CORTEX-M4
*/
typedef struct {
	volatile uint32_t ISER[8];     			    /**< Interrupt Set Enable Register n, array offset: 0x0, array step: 0x4 */
	uint8_t RESERVED_0[96];
	volatile uint32_t ICER[8];        		 	/**< Interrupt Clear Enable Register n, array offset: 0x80, array step: 0x4 */
	uint8_t RESERVED_1[96];
	volatile uint32_t ISPR[8];       		    /**< Interrupt Set Pending Register n, array offset: 0x100, array step: 0x4 */
	uint8_t RESERVED_2[96];
	volatile uint32_t ICPR[8];    		        /**< Interrupt Clear Pending Register n, array offset: 0x180, array step: 0x4 */
	uint8_t RESERVED_3[96];
	volatile uint32_t IABR[8];         			/**< Interrupt Active bit Register n, array offset: 0x200, array step: 0x4 */
	uint8_t RESERVED_4[224];
	volatile uint8_t IP[240];              		/**< Interrupt Priority Register n, array offset: 0x300, array step: 0x1 */
	uint8_t RESERVED_5[2576];
	volatile uint32_t STIR;      				/**< Software Trigger Interrupt Register, offset: 0xE00 */
} NVIC_Type;

/**
* @brief    Define structure of SysTick typedef
*/
typedef struct
{
    volatile uint32 CSR;                  	/* SysTick Control and Status Register */
    volatile uint32 RVR;                 	/* SysTick Reload Value Register */
    volatile uint32 CVR;                 	/* SysTick Currrent Value Register */
    volatile uint32 CALIB;               	/* SysTick Calibration Calibration Register */

} SysTick_TypeDef;

/******************************************************************************
 *  GLOBAL VARIABLES
 *****************************************************************************/


/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/

#endif /* INC_STM32F411XX_H_ */
