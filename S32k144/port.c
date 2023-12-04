/******************************************************************************
 * Project Name: PORT DRIVER
 * File Name:   port.c
 *
 * Description: Implementation of the PORT DRIVER
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex-M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "port.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/


/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/
/**
 *   @brief      This function configure output pin.
 *
 *   @param[in]  GPIO_TypeDef*          pGPIOx
 *   @param[in]  uint32                 PinNumber
 *
 *   @return     void                   xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void PORT_Pin_Output_Config(PORT_TypeDef *pPORTx, GPIO_TypeDef *pGPIOx, uint32 PinNumber)
{
    /* Set pin MUX as GPIO */
    pPORTx->PCR[PinNumber] &= ~(PORT_PCR_MUX_MASK);
    pPORTx->PCR[PinNumber] |= (1 << PORT_PCR_MUX_SHIFT);

    /* Set pin direction as OUTPUT */
    pGPIOx->PDDR |= (1 << PinNumber);
}

/**
 *   @brief      This function configure input pin.
 *
 *   @param[in]  PORT_TypeDef*          pPORTx
 *   @param[in]  GPIO_TypeDef*          pGPIOx
 *   @param[in]  uint32                 PinNumber
 *   @param[in]  uint8                  PullUpDown
 *
 *   @return     void                   xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void PORT_Pin_Input_Config(PORT_TypeDef *pPORTx, GPIO_TypeDef *pGPIOx, uint32 PinNumber, uint8 PullUpDown)
{
    /* Set pin MUX as GPIO */
    pPORTx->PCR[PinNumber] &= ~(PORT_PCR_MUX_MASK);
    pPORTx->PCR[PinNumber] |= (1 << PORT_PCR_MUX_SHIFT);

    /* Configure PullUp PullDown if enable */
    if (PullUpDown != 0)
    {
        /* Enable PullUp PullDown Setting Mode */
        pPORTx->PCR[PinNumber] |= (1 << PORT_PCR_PE_SHIFT);
			
        /* Enable Passive Filter */
        pPORTx->PCR[PinNumber] |= (1 << PORT_PCR_PFE_SHIFT);

        if (PullUpDown == PIN_PULLUP)
        {
            /* Configure Pull up */
            pPORTx->PCR[PinNumber] |= (1 << PORT_PCR_PS_SHIFT);
        }
        else if (PullUpDown == PIN_PULLDOWN)
        {
            /* Configure Pull down */
            pPORTx->PCR[PinNumber] &= ~(1 << PORT_PCR_PS_SHIFT);
        }
    }    

    /* Set pin direction as OUTPUT */
    pGPIOx->PDDR &= ~(1 << PinNumber);
}

/**
 *   @brief      This function configure input pin with interrupt.
 *
 *   @param[in]  PORT_TypeDef*          pPORTx
 *   @param[in]  GPIO_TypeDef*          pGPIOx
 *   @param[in]  uint32                 PinNumber
 *   @param[in]  uint32                 IQRCMode
 *
 *   @return     void                   xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void PORT_Pin_Input_IT_Config(PORT_TypeDef *pPORTx, GPIO_TypeDef *pGPIOx, uint32 PinNumber, uint32 IQRCMode, uint8 PullUpDown)
{
    /* Set pin MUX as GPIO */
    pPORTx->PCR[PinNumber] &= ~(PORT_PCR_IQRC_MASK | PORT_PCR_MUX_MASK);
    pPORTx->PCR[PinNumber] |= (1 << PORT_PCR_MUX_SHIFT);
	
    /* Set pin IQRC for interrupt */
    pPORTx->PCR[PinNumber] |= (IQRCMode << PORT_PCR_IQRC_SHIFT);

    /* Configure PullUp PullDown if enable */
    if (PullUpDown != 0)
    {
        /* Enable PullUp PullDown Setting Mode */
        pPORTx->PCR[PinNumber] |= (1 << PORT_PCR_PE_SHIFT);
			
        /* Enable Passive Filter */
        pPORTx->PCR[PinNumber] |= (1 << PORT_PCR_PFE_SHIFT);

        if (PullUpDown == PIN_PULLUP)
        {
            /* Configure Pull up */
            pPORTx->PCR[PinNumber] |= (1 << PORT_PCR_PS_SHIFT);
        }
        else if (PullUpDown == PIN_PULLDOWN)
        {
            /* Configure Pull down */
            pPORTx->PCR[PinNumber] &= ~(1 << PORT_PCR_PS_SHIFT);
        }
    }    

    /* Set pin direction as OUTPUT */
    pGPIOx->PDDR &= ~(1 << PinNumber);
}

/**
 *   @brief      This function reads value of a port pin.
 *
 *   @param[in]  GPIO_TypeDef*      pGPIOx
 *   @param[in]  uint8              PinNumber
 *
 *   @return     void               xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
uint8 GPIO_ReadFromInputPin(GPIO_TypeDef *pGPIOx, uint8 PinNumber)
{
    uint8 u8Value;
    u8Value = (uint8)((pGPIOx->PDIR >> PinNumber) & 0x01);
    return u8Value;
}

/**
 *   @brief      This function reads value of an input port.
 *
 *   @param[in]  GPIO_TypeDef*      pGPIOx
 *
 *   @return     void               xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
uint32 GPIO_ReadFromInputPort(GPIO_TypeDef *pGPIOx)
{
    uint32 u32Value;
    u32Value = (uint32)(pGPIOx->PDIR);
    return u32Value;
}

/**
 *   @brief      This function writes value of port pin.
 *
 *   @param[in]  GPIO_TypeDef*      PORTx
 *   @param[in]  uint8              PinNumber
 *   @param[in]  uint8              Value
 *
 *   @return     void               xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void GPIO_WriteToOutputPin(GPIO_TypeDef *pGPIOx, uint8 PinNumber, uint8 Value)
{
    if (Value)
    {
        pGPIOx->PDOR |= (1 << PinNumber);
    }
    else
    {
        pGPIOx->PDOR &= ~(1 << PinNumber);
    }
}

/**
 *   @brief      This function writes value of port.
 *
 *   @param[in]  GPIO_TypeDef*      PORTx
 *   @param[in]  uint32              PinNumber
 *
 *   @return     void               xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void GPIO_WriteToOutputPort(GPIO_TypeDef *pGPIOx, uint32 Value)
{
    pGPIOx->PDOR = Value;
}

/**
 *   @brief      This function toggles value of port pin.
 *
 *   @param[in]  GPIO_TypeDef*      PORTx
 *   @param[in]  uint8              PinNumber
 *
 *   @return     void               xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void GPIO_ToggleOutputPin(GPIO_TypeDef *pGPIOx, uint8 PinNumber)
{
    pGPIOx->PDOR ^= (1U << PinNumber);
}