/******************************************************************************
 * Project Name: LPUART DRIVER
 * File Name:   lpit.c
 *
 * Description: Implementation of the LPIT
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex-M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "lpit.h"

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
 *   @brief      This function configures LPIT module
 *
 *   @param[in]  uint32 CountValue      Reload value for timer channel
 *
 *   @return     void                   xxxxxxxx
 *
 *   @note       This function should be called in main function
 *
*/
void LPIT_CH0_Init(uint32 CountValue)
{
    /* Configure Module Status */
    uint32 temp;
    temp = (1 << LPIT_MCR_M_CEN_SHIFT);
    /*Enable clock for timer LPIT*/
    LPIT->MCR = temp; 						
    
    /*Enable interrupt for channel 0*/
    temp = (1 << LPIT_MIER_TIE0_SHIFT);
    LPIT->MIER = temp; 						

    /*Time out period: CountValue */
    LPIT->CHANNEL[0].TVAL = CountValue - 1; 	     
}

/**
 *   @brief      This function starts LPIT timer
 *
 *   @param[in]  uint8 Channel		      Channel number of timer module
 *
 *   @return     void                   xxxxxxxx
 *
 *   @note       This function should be called in main function
 *
*/
void LPIT_StartTimer(uint8 Channel)
{
    /*Timer enable channel x*/
    LPIT->CHANNEL[Channel].TCTRL |= (1 << 0);   
}

/**
 *   @brief      This function stops LPIT timer
 *
 *   @param[in]  uint8 Channel		      Channel number of timer module
 *
 *   @return     void                   xxxxxxxx
 *
 *   @note       This function should be called in main function
 *
*/
void LPIT_StopTimer(uint8 Channel)
{
    /*Timer enable channel x*/
    LPIT->CHANNEL[Channel].TCTRL &= ~(1 << 0);   
}