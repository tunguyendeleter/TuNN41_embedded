#include "gpio2.h"


void GPIO_PeriClockControl(GPIO_Type *pGPIOx, uint8 EnorDis)
{
	if(EnorDis == ENABLE)
	{
		if(pGPIOx == GPIOA)
			PORTA_CLK_EN();
		else if(pGPIOx == GPIOB)
			PORTB_CLK_EN();
		else if(pGPIOx == GPIOC)
			PORTC_CLK_EN();
		else if(pGPIOx == GPIOD)
			PORTD_CLK_EN();
		else if(pGPIOx == GPIOE)
			PORTE_CLK_EN();
		else if(pGPIOx == GPIOH)
			PORTH_CLK_EN();
	}else if(EnorDis == DISABLE)
	{
		if(pGPIOx == GPIOA)
			PORTA_CLK_DIS();
		else if(pGPIOx == GPIOB)
			PORTB_CLK_DIS();
		else if(pGPIOx == GPIOC)
			PORTC_CLK_DIS();
		else if(pGPIOx == GPIOD)
			PORTD_CLK_DIS();
		else if(pGPIOx == GPIOE)
			PORTE_CLK_DIS();
		else if(pGPIOx == GPIOH)
			PORTH_CLK_DIS();
	}
}

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32 temp = 0;
	/*1. Configure the mode of gpio pin*/
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{ /*non interrupt mode*/
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER &= ~(0x03 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));		/*clearing bitfields*/
		pGPIOHandle->pGPIOx->MODER |= temp;		/*setting bitfields*/
		temp = 0;
	}
	else
	{ /*interrupt mode*/
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FE)
		{
			/*1. Configure falling edge selection*/
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RE)
		{
			/*1. Configure rising edge selection*/
			EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_EE)
		{
			/*1. Configure either edge selection*/
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}

		/*2. Configure the GPIO port selection in SYSCFG_EXTICR*/
		uint8 temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
		uint8 temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
		uint8 portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG_CLK_EN();
		SYSCFG->EXTICR[temp1] = portcode << (temp2 * 4);

		/*3. Enable the EXTI interrupt delivery using IMR*/
		EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}
	/*2. Configure the speed*/
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x03 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));		/*clearing bitfields*/
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;		/*setting bitfields*/
	temp = 0;

	/*3. Configure the pupd setting*/
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x03 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));			/*clearing bitfields*/
	pGPIOHandle->pGPIOx->PUPDR |= temp;			/*setting bitfields*/
	temp = 0;

	/*4. Configure the optype*/
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x01 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));				/*clearing bitfields*/
	pGPIOHandle->pGPIOx->OTYPER |= temp;		/*setting bitfields*/
	temp = 0;

	/*5. Configure the alt function*/
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode == GPIO_MODE_ALT)
	{
		uint8 temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
		uint8 temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		pGPIOHandle->pGPIOx->AFR[temp2] &= ~(0x0F << (4 * temp1));
		pGPIOHandle->pGPIOx->AFR[temp2] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp1));
	}
}

void GPIO_DeInit(GPIO_Type *pGPIOx)
{
	if(pGPIOx == GPIOA)
		GPIOA_REG_RESET();
	else if(pGPIOx == GPIOB)
		GPIOB_REG_RESET();
	else if(pGPIOx == GPIOC)
		GPIOC_REG_RESET();
	else if(pGPIOx == GPIOD)
		GPIOD_REG_RESET();
	else if(pGPIOx == GPIOE)
		GPIOE_REG_RESET();
	else if(pGPIOx == GPIOH)
		GPIOH_REG_RESET();
}

uint8 GPIO_ReadFromInputPin(GPIO_Type *pGPIOx, uint8 PinNumber)
{
	uint8 value;
	value = (uint8)((pGPIOx->IDR >> PinNumber) & 0x01);
	return value;
}

uint16 GPIO_ReadFromInputPort(GPIO_Type *pGPIOx)
{
	uint16 value;
	value = (uint16)(pGPIOx->IDR);
	return value;
}

void GPIO_WriteToOutputPin(GPIO_Type *pGPIOx, uint8 PinNumber, uint8 Value)
{
	if(Value == GPIO_PIN_SET)
		pGPIOx->ODR |= (1 << PinNumber);
	else
		pGPIOx->ODR &= ~(1 << PinNumber);
}

void GPIO_WriteToOutputPort(GPIO_Type *pGPIOx, uint16 Value)
{
	pGPIOx->ODR = Value;
}

void GPIO_ToggleOutputPin(GPIO_Type *pGPIOx, uint8 PinNumber)
{
	pGPIOx->ODR ^= (1 << PinNumber);
}


