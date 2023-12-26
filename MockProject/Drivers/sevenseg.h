/******************************************************************************
 * Project Name: LPUART DRIVER
 * File Name:   sevenseg.h
 *
 * Description: Implementation of the SEVENSEG LIBRARY
 *              Target systems:           S32K144
 *              Derivatives:              ARM Cortex-M4
 *              Compiler:                 S32DS
 *
 *****************************************************************************/
#ifndef DRIVERS_INC_SEVENSEG_H_
#define DRIVERS_INC_SEVENSEG_H_

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "Common_S32K144.h"
#include "lpspi.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/**
* @brief  define address macros for displaying digit registers
*/
#define DIGIT0_ADDR                 0X1U
#define DIGIT1_ADDR                 0X2U
#define DIGIT2_ADDR                 0X3U
#define DIGIT3_ADDR                 0X4U
#define DIGIT4_ADDR                 0X5U
#define DIGIT5_ADDR                 0X6U
#define DIGIT6_ADDR                 0X7U
#define DIGIT7_ADDR                 0X8U

/**
* @brief  define address macros for mode registers
*/
#define DECODE_MODE_ADDR            0X9U
#define INTENSITY_ADDR              0XAU
#define SCAN_LIMIT_ADDR             0XBU
#define SHUTDOWN_ADDR               0XCU
#define DISPLAY_TEST_ADDR           0XFU

/**
* @brief  define macros for Shutdown Register Format  
*/
#define SHUTDOWN_MODE               0X0U
#define NORMAL_MODE                 0XFU

/**
* @brief  define macros Code B Font   
*/
#define CHAR_DATA(x)                ((uint8)x - 48)

/**
* @brief  define macros for Decode-Mode   
*/
#define NO_DECODE                   0X0U
#define DECODE_0_0                  0X1U
#define DECODE_1_0                  0X3U
#define DECODE_2_0                  0X7U
#define DECODE_3_0                  0XFU
#define DECODE_4_0                  0X1FU
#define DECODE_5_0                  0X3FU
#define DECODE_6_0                  0X7FU
#define DECODE_7_0                  0XFFU

/**
* @brief  define macros for Intensity Register Format    
*/
#define DUTY_1_PER_32               0X0U
#define DUTY_3_PER_32               0X1U
#define DUTY_5_PER_32               0X2U
#define DUTY_7_PER_32               0X3U
#define DUTY_9_PER_32               0X4U
#define DUTY_11_PER_32              0X5U
#define DUTY_13_PER_32              0X6U
#define DUTY_15_PER_32              0X7U
#define DUTY_17_PER_32              0X8U
#define DUTY_19_PER_32              0X9U
#define DUTY_21_PER_32              0XAU
#define DUTY_23_PER_32              0XBU
#define DUTY_25_PER_32              0XCU
#define DUTY_27_PER_32              0XDU
#define DUTY_29_PER_32              0XEU
#define DUTY_31_PER_32              0XFU

/**
* @brief  define macros for Scan-Limit Register Format    
*/
#define SCAN_LIMIT_0_0              0X0U
#define SCAN_LIMIT_1_0              0X1U
#define SCAN_LIMIT_2_0              0X2U
#define SCAN_LIMIT_3_0              0X3U
#define SCAN_LIMIT_4_0              0X4U
#define SCAN_LIMIT_5_0              0X5U
#define SCAN_LIMIT_6_0              0X6U
#define SCAN_LIMIT_7_0              0X7U

/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/

/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPE
 *****************************************************************************/
/**
* @brief  This function send command containing address and data to MAX7219 module.
*/
extern void SevenSeg_Init(void);

/**
* @brief  This function configures 7-SEGMENT MAX7219.
*/
extern void SevenSeg_SendCommand(uint8 address, uint8 command);

/**
* @brief  This function send a string of data to 7-SEGMENT.
*/
extern void SevenSeg_PrintString(uint8 *string, uint8 len);

/**
* @brief  This function turn off displaying screen.
*/
extern void SevenSeg_ClearDisplay(void);

/**
* @brief  This function turn on displaying screen.
*/
extern void SevenSeg_SetDisplay(void);

#endif /* DRIVERS_INC_SEVENSEG_H_ */
