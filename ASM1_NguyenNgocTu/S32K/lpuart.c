/******************************************************************************
 * Project Name: LPUART DRIVER
 * File Name:   lpuart.c
 *
 * Description: Implementation of the LPUART
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex-M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "lpuart.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/

/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/

/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPE
 *****************************************************************************/
/**
 *   @brief      This function configures LPUART protocol
 *
 *   @param[in]  LPUART_Type*       LPUARTx
 *   @param[in]  uint32       			SBR
 *   @param[in]  uint32       			OSR
 *   @param[in]  uint32       			Rx_Status
 *   @param[in]  uint32       			Tx_Status
 *   @param[in]  uint8       				Interrupt_Type
 *
 *   @return     void   						xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
*/
void LPUART_ConfigReceiveIT(LPUART_TypeDef *LPUARTx, uint32 SBR, uint32 OSR, uint32 Rx_Status, uint32 Tx_Status, uint8 Interrupt_Type)
{
    /*Setting baud rate: Baud rate = baud clock / ((OSR+1) * SBR)*/
    uint32 temp = (SBR << 0) | (OSR << 24) | (0U << 13);

    /*Setting Frame*/
    LPUARTx->BAUD = temp; /*Setting one stop bit - config 1U if want 2 stop bit*/

    /* Configure Interrupt on transmit or receive */
    if (Interrupt_Type == LPUART_IT_TR)
    {
        /*Interrupt transmitted data enable*/
        LPUARTx->CTRL |= (1 << 22);
    }else if (Interrupt_Type == LPUART_IT_RE)
    {
        /*Interrupt received data enable*/
        LPUARTx->CTRL |= (1 << 21);
    }else if (Interrupt_Type == LPUART_IT_TR_RE)
    {
        /*Interrupt transmitted data enable*/
        LPUARTx->CTRL |= (1 << 22);
        /*Interrupt received data enable*/
        LPUARTx->CTRL |= (1 << 21);
    }
    /*Enable Receiver*/
    LPUARTx->CTRL |= (Rx_Status << 18); 

    /*Enable Transmiter*/
    LPUARTx->CTRL |= (Tx_Status << 19); 
}

/**
 *   @brief      This function transmits single character by LPUART protocol
 *
 *   @param[in]  LPUART_Type*       LPUARTx
 *   @param[in]  char       				TransmitData
 *
 *   @return     void   xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
*/
void LPUART_TransmitChar(LPUART_TypeDef* LPUARTx, char TransmitData){
	while (! (LPUARTx->STAT & (1U << 23)) );	/*Wait until the buffer is empty*/

	LPUARTx->DATA = TransmitData;							/*Send data*/
}

/**
 *   @brief      This function transmits string by LPUART protocol
 *
 *   @param[in]  LPUART_Type*       LPUARTx
 *   @param[in]  char       				TransmitString[]
 *
 *   @return     void   xxxxxxxx
 *
 *   @note       This function call LPUART_TransmitChar(LPUART_Type* LPUARTx, char TransmitData) function
 * 				 to transmit single character.
 *
*/
void LPUART_TransmitString(LPUART_TypeDef* LPUARTx, char TransmitString[]){

	volatile int i = 0;

	while (TransmitString[i] != '\0'){
		LPUART_TransmitChar(LPUARTx, TransmitString[i]);
		i++;
	}
}

/**
 *   @brief      This function transmits string by LPUART protocol
 *
 *   @param[in]  LPUART_Type*       LPUARTx
 *   @param[in]  char       				TransmitString[]
 *
 *   @return     void   xxxxxxxx
 *
 *   @note       This function call LPUART_TransmitChar(LPUART_Type* LPUARTx, char TransmitData) function
 * 				 to transmit single character.
 *
*/
void LPUART_TransmitString_IT(LPUART_TypeDef* LPUARTx, char TransmitString[]){

	volatile int i = 0;

	while (TransmitString[i] != '\0'){
		LPUART_TransmitChar(LPUARTx, TransmitString[i]);
		i++;
	}
}

/**
 *   @brief      This function receive a single character by LPUART protocol
 *
 *   @param[in]  LPUART_Type*       	LPUARTx
 *
 *   @return     void   							xxxxxxxx
 *
 *   @note       This function call LPUART_TransmitChar(LPUART_Type* LPUARTx, char TransmitData) function
 * 				 to transmit single character.
 *
*/
char LPUART_ReceiveString(LPUART_TypeDef* LPUARTx){
	while (! (LPUARTx->STAT & (1U << 21)) ){}	/*Wait until the buffer is empty*/

    char data = LPUARTx->DATA;
    return data;
}
