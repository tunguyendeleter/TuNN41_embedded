/******************************************************************************
 * Project Name: LPUART DRIVER
 * File Name:   sevenseg.c
 *
 * Description: Implementation of the SEVENSEG LIBRARY
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex-M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "sevenseg.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/

/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/

/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/
/**
 *   @brief      This function send command containing address and data to MAX7219 module.
 *
 *   @param[in]  uint8                  address
 *   @param[in]  uint8                  command
 *
 *   @return     void                   xxxxxxxx
 *
 *   @note       Driver should be called in SevenSeg_PrintString function.
 *
 */
void SevenSeg_SendCommand(uint8 address, uint8 command)
{
    uint16 data = 0U;
    data = ((uint16)(address << 8) | (uint16)(command << 0));
    LPSPI_Transmit(LPSPI1, data);
}

/**
 *   @brief      This function configures 7-SEGMENT MAX7219.
 *
 *   @return     void                   xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void SevenSeg_Init(void)
{
    /* Normal Operation */
    SevenSeg_SendCommand(SHUTDOWN_ADDR, NORMAL_MODE);

    /* Code B decode for digits 7–0 */
    SevenSeg_SendCommand(DECODE_MODE_ADDR, DECODE_7_0);

    /* Intensity 31/32 (max on) */
    SevenSeg_SendCommand(INTENSITY_ADDR, DUTY_31_PER_32);

    /* Display digits 0 1 2 3 4 5 6 7 */
    SevenSeg_SendCommand(SCAN_LIMIT_ADDR, SCAN_LIMIT_7_0);
}

/**
 *   @brief      This function send a string of data to 7-SEGMENT.
 *
 *   @param[in]  uint8*                 address
 *   @param[in]  uint8                  len
 *
 *   @return     void                   xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void SevenSeg_PrintString(uint8 *string, uint8 len)
{
    uint8 i = 0U;
    /* Loop for all character to be displayed */
    if (len > 0)
    {
        for (i = 0; i < len; i++)
        {
            /* Send each character to 7-Segment */
            if (*(string + i) != ' ')
            {
                SevenSeg_SendCommand((uint8)(len - i), (uint8)(*(string + i) - 48));
            }
            /* Send blank character to 7-Segment */
            else
            {
                SevenSeg_SendCommand((uint8)(len - i), (uint8)(0X7FU));
            }
        }
    }
}

/**
 *   @brief      This function turn off displaying screen.
 *
 *   @return     void                   xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void SevenSeg_ClearDisplay(void)
{
    /* ShutDown Mode */
    SevenSeg_SendCommand(SHUTDOWN_ADDR, SHUTDOWN_MODE);
}

/**
 *   @brief      This function turn on displaying screen.
 *
 *   @return     void                   xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void SevenSeg_SetDisplay(void)
{
    /* ShutDown Mode */
    SevenSeg_SendCommand(SHUTDOWN_ADDR, NORMAL_MODE);
}
