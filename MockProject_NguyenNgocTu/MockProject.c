/*
** ####################################################################################################
**     Microcontroller:     S32K144EVB-100Q
**     Processor:           Arm Cortex M4F
**     Compiler:            Keil C V5
**     Version:             rev. 1.0, 01012024
**
**     Abstract:
**          [SRS 1]: After power on, display the time 00-00-00 (date: 01.01.1971)
**          [SRS 2]: Press Button 1
**                  + SRS 2-1: Display the date
**                  + SRS 2-2: Display the time
**          [SRS 3]: Press Button 2
**                  + SRS 3-1: Turn off the display mode
**                  + SRS 3-2: Turn on the display mode
**          [SRS 4]: Setting date, time, alarm by UART serial communication.
** ####################################################################################################
*/

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "sevenseg.h"
#include "config.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/**
 * @brief    Define macro flag for display time condition
 */
#define DISPLAY_TIME                    (uint8)(1 << 0)

/**
 * @brief    Define macro flag for display date condition
 */
#define DISPLAY_DATE                    (uint8)(1 << 1)

/**
 * @brief    Define macro flag for update date condition
 */
#define UPDATE_DATE                     (uint8)(1 << 2)

/**
 * @brief    Define macro flag for change time condition
 */
#define CHANGE_TIME                     (uint8)(1 << 3)

/**
 * @brief    Define macro flag for change date condition
 */
#define CHANGE_DATE                     (uint8)(1 << 4)

/******************************************************************************
 *  GLOBAL VARIABLE
 *****************************************************************************/
/**
 * @brief    Declare variable to receive date from lpuart
 */
static volatile uint8 pu8ReceiveData[11] = {0};

/**
 * @brief    Declare variable to button state 1
 */
static volatile uint8 u8SW2State;

/**
 * @brief    Declare variable to button state 2
 */
static volatile uint8 u8SW3State;

/**
 * @brief    Declare variable to store flag
 */
static volatile uint8 u8Flag;

/**
 * @brief    Declare variable to current date
 */
static volatile uint8 u8Date;

/**
 * @brief    Declare variable to current month
 */
static volatile uint8 u8Month;

/**
 * @brief    Declare variable to current year
 */
static volatile uint16 u16Year;

/**
 * @brief    Declare variable to current hour
 */
static volatile uint8 u8Hour;

/**
 * @brief    Declare variable to current minute
 */
static volatile uint8 u8Minute;

/**
 * @brief    Declare variable to current second
 */
static volatile uint8 u8Second;

/**
 * @brief    Declare variable to store data to display date on led
 */
static volatile uint8 Date[9] = {'0', '1' + 128U, '0', '1' + 128U, '1', '9', '7', '1', '\0'};

/**
 * @brief    Declare variable to store data to display time on led
 */
static volatile uint8 Time[9] = {0};

/******************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *****************************************************************************/
/**
 * @brief    This function performs a callback notification at the end of RX handler
 */
void LPUART_RX_Callback(void);

/**
 * @brief    This LPIT0_Ch0_IRQHandler function is used to update time and date for each 1000ms
 */
void LPIT0_Ch0_IRQHandler(void);

/**
 * @brief    This LPUART2_RxTx_IRQHandler function is used to process RXTX data from LPUART2
 */
void LPUART2_RxTx_IRQHandler(void);

/**
 * @brief    This LPSPI1_IRQHandler function is used to process RXTX data from LPSPI1
 */
void LPSPI1_IRQHandler(void);

/**
 * @brief    This PORTC_IRQHandler function is used to change the status of button SW2, SW3
 */
void PORTC_IRQHandler(void);

/******************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *****************************************************************************/
/**
 * @brief    This function set value for buffer with length of buffer
 */
void MEMSET(uint8 *Buffer, uint8 Character, uint16 Len);

/**
 * @brief    This function returns the number of character in a string excluding null character
 */
uint16 STRLEN(uint8 *string);

/**
 * @brief    This function compares 2 strings
 */
int8 STRCMP(uint8 *string1, uint8 *string2);

/**
 * @brief    This function updates the new date, month, year from lpuart communication
 */
void GetNewDate(void);

/**
 * @brief    This function updates the new hours, minutes, seconds from lpuart communication
 */
void GetNewTime(void);

/**
 * @brief    This function returns the number of dates in a specific month
 */
uint8 DaysInMonth(uint8 Month, uint16 Year);

/**
 * @brief    This function updates date, month, year based on current date
 */
void DateUpdate(void);

/**
 * @brief    This function updates second, minute, hour based on current time
 */
void TimeUpdate(void);

/******************************************************************************
 *  MAIN FUNCTION
 *****************************************************************************/
int main(void)
{
    uint16 u16AdcData;
    u8SW2State = 0U;
    u8SW3State = 0U;
    u8Flag = 0U;
    u8Date = 1U;
    u8Month = 1U;
    u16Year = 1917U;
    u8Hour = 0U;
    u8Minute = 0U;
    u8Second = 0U;

    /*---------------------------------------------------------Clock Config ------------------------------------------------------------*/

    /*FIRC clock config with frequency DIV1 = DIV2 = 24Mhz*/
    FIRC_ClockEnable(DIV1_BY_2, DIV2_BY_2);

    /*Enable SOSC clock with frequency = 8Mhz*/
    SOSC_ClockEnable(DIV1_BY_1, DIV1_BY_1, RANGE_MEDIUM_FREQUENCY, REFER_INTERNAL);

    /*Enable SPLL clock with frequency = 72Mhz; Div2 = 36Mhz*/
    SPLL_ClockEnable(DIV1_BY_2, DIV2_BY_2, PRE_DIV_BY_(2), MULTIPLY_BY_(36), INPUT_SOSC);

    /*Config system clock with core clock = 72Mhz and bus clock = 36hz and div clock = 24Mhz*/
    SystemClockConfig(SCS_SPLL_CLK, DIVCORE_BY_(1), DIVBUS_BY_(2), DIVSLOW_BY_(3));

    /*--------------------------------------------------------ADC module----------------------------------------------------------------*/

    /* Configure ADC0 module */
    PORT_PeripheralClockConfig(PORTA);
    PORT_PeripheralClockConfig(PORTB);
    PORT_PeripheralClockConfig(PORTC);
    PORT_PeripheralClockConfig(PORTD);

    ADC_PeripheralClockConfig(&adc0);
    ADC_Init(&adc0);

    /*--------------------------------------------------------PORT module---------------------------------------------------------------*/

    /* Enable clock at PORTx */
    PORT_PeripheralClockConfig(PORTA);
    PORT_PeripheralClockConfig(PORTB);
    PORT_PeripheralClockConfig(PORTC);
    PORT_PeripheralClockConfig(PORTD);

    /* Set pin C12, C13 as INPUT */
    PORT_Pin_Input_IT_Config(PORTC, GPIOC, 12, IRQC_FE, PIN_PULLDOWN);
    PORT_Pin_Input_IT_Config(PORTC, GPIOC, 13, IRQC_FE, PIN_PULLDOWN);

    /* Config NVIC for PORTC */
    Interrupt_Enable(PORTC_IQRNumber, 8);

    /*-------------------------------------------------------LPUART2 Config ------------------------------------------------------------*/

    /* Configure LPUART2 module */
    PORT_Pin_Alt_Config(PORTD, 7, ALT_FUNC(2)); /* LPUART2_TX */
    PORT_Pin_Alt_Config(PORTD, 6, ALT_FUNC(2)); /* LPUART2_RX */

    LPUART_PeripheralClockConfig(&lpuart2);
    LPUART_Init(&lpuart2);
    Interrupt_Enable(LPUART2_IRQ_ID, 7);

    /*-------------------------------------------------------LPIT TIMER Config ---------------------------------------------------------*/

    LPIT_PeripheralClockConfig(&lpit);
    LPIT_Init(&lpit);
    LPIT_StartTimer(&lpit);
    Interrupt_Enable(LPIT_CH0_IRQ_ID, 6);

    /*--------------------------------------------------------LPSPI1 Config ------------------------------------------------------------*/

    /* Configure LPSPI module */
    PORT_Pin_Alt_Config(PORTB, 16, ALT_FUNC(3)); /* LPSPI1_SOUT */
    PORT_Pin_Alt_Config(PORTB, 14, ALT_FUNC(3)); /* LPSPI1_SCK */
    PORT_Pin_Alt_Config(PORTB, 15, ALT_FUNC(3)); /* LPSPI1_SIN */
    PORT_Pin_Alt_Config(PORTB, 17, ALT_FUNC(3)); /* LPSPI1_PCS3 */

    LPSPI_PeripheralClockConfig(&lpspi1);
    LPSPI_Init(&lpspi1);
    Interrupt_Enable(LPSPI1_IRQ_ID, 5);

    /*--------------------------------------------------------7SEG-LED module-----------------------------------------------------------*/

    /* Configure 7-Segment LED module */
    SevenSeg_Init(&lpspi1);
    uint8 *pu8Data = (uint8 *)Date;
    SevenSeg_PrintString(&lpspi1, pu8Data, STRLEN(pu8Data));

    /*----------------------------------------------------Before Enter Character -------------------------------------------------------*/

    /* INTRODUCTION */
    LPUART_TransmitString(&lpuart2, (uint8 *)"######################################################################\r\n");
    LPUART_TransmitString(&lpuart2, (uint8 *)"[Nguyen Ngoc Tu] - Mock Project\r\n");
    LPUART_TransmitString(&lpuart2, (uint8 *)"Digital Clock Application\r\n\n");
    /* USER GUIDE */
    LPUART_TransmitString(&lpuart2, (uint8 *)"USER GUIDE:\r\n\n");
    /* HOW TO ENTER DATE AND TIME: */
    LPUART_TransmitString(&lpuart2, (uint8 *)"If you want to change the current date:\r\n");
    LPUART_TransmitString(&lpuart2, (uint8 *)"Input Hercules: TIME<ENTER>\r\n");
    LPUART_TransmitString(&lpuart2, (uint8 *)"Input Hercules: Hours-Minutes-Seconds<ENTER>\r\n");
    LPUART_TransmitString(&lpuart2, (uint8 *)"Example:  => TIME<ENTER> => 23-59-30<ENTER>\r\n\n");
    LPUART_TransmitString(&lpuart2, (uint8 *)"If you want to change the current time:\r\n");
    LPUART_TransmitString(&lpuart2, (uint8 *)"Input Hercules: DATE<ENTER>\r\n");
    LPUART_TransmitString(&lpuart2, (uint8 *)"Input Hercules: Dates-Months-Years<ENTER>\r\n");
    LPUART_TransmitString(&lpuart2, (uint8 *)"Example:  => DATE<ENTER> => 22-02-2000<ENTER>\r\n\n");
    /* WARNING*/
    LPUART_TransmitString(&lpuart2, (uint8 *)"WARNING:\r\n");
    LPUART_TransmitString(&lpuart2, (uint8 *)"You must have to enter ENTER or DATE before sending updating new value\r\n");
    LPUART_TransmitString(&lpuart2, (uint8 *)"The program will not work properly if you not follow the GUIDELINE\r\n");
    LPUART_TransmitString(&lpuart2, (uint8 *)"######################################################################\r\n");

    /*--------------------------------------------------------START PROGRAM-------------------------------------------------------------*/

    while (1)
    {
        /* Check flag for display MAX7219 */
        if (u8Flag)
        {
            /* If flag is used to display time */
            if (u8Flag & DISPLAY_TIME)
            {
                uint8 *pu8Data = (uint8 *)Time;
                SevenSeg_PrintString(&lpspi1, pu8Data, STRLEN(pu8Data));
                /* Clear Display flag */
                u8Flag &= ~DISPLAY_TIME;
            }
            /* If flag is used to display date */
            else if (u8Flag & DISPLAY_DATE)
            {
                uint8 *pu8Data = (uint8 *)Date;
                SevenSeg_PrintString(&lpspi1, pu8Data, STRLEN(pu8Data));
                /* Clear Display flag */
                u8Flag &= ~DISPLAY_DATE;
            }
        }

        /* Check for bus state of LPUART interrupt reception */
        uint8 *pu8Data = (uint8 *)pu8ReceiveData;
        if (lpuart2.RxStatus == LPUART_READY)
        {
            /* receive signal data as "DATE" then start receiving data for date */
            if (STRCMP(pu8Data, (uint8 *)"DATE") == 0) /* DATE = "01.01.2077"*/
            {
                LPUART_ReceiveIT(&lpuart2, pu8Data, 10U);
            }
            /* receive signal data as "TIME" then start receiving data for time */
            else if (STRCMP(pu8Data, (uint8 *)"TIME") == 0) /* TIME = "00-00-00"*/
            {
                LPUART_ReceiveIT(&lpuart2, pu8Data, 8U);
            }
            /* receive signal data from LPUART interrupt */
            else
            {
                LPUART_ReceiveIT(&lpuart2, pu8Data, 4U);
            }
        }

        /* Start ADC conversion */
        ADC_StartConversion(&adc0);

        /* Poll for ADC complete conversion */
        while (ADC_GetStatus(&adc0, 0) == 0)
            ;

        /* Change intensity of 7-SEG LED */
        u16AdcData = (ADC_ReadConversion(&adc0, 0) * 15 + 0X7FF) / 0XFFF;
        SevenSeg_SendCommand(&lpspi1, INTENSITY_ADDR, u16AdcData);
    }

    return 0;
}

/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/
/**
 *   @brief      This function updates the new hours, minutes, seconds from lpuart communication.
 *
 *   @return     void                       xxxxxxxx
 *
 *   @note       Driver should be called in LPIT0_Ch0_IRQHandler function.
 *
 */
void GetNewTime(void)
{
    uint8 *pu8Data = (uint8 *)pu8ReceiveData;
    /* Update Time */
    if (u8Flag & CHANGE_TIME)
    {
        /* Get Hours */
        u8Hour = pu8Data[0] - 48U;
        u8Hour = (u8Hour * 10) + (pu8Data[1] - 48U);

        /* Get Minutes */
        u8Minute = pu8Data[3] - 48U;
        u8Minute = (u8Minute * 10) + (pu8Data[4] - 48U);

        /* Get Seconds */
        u8Second = pu8Data[6] - 48U;
        u8Second = (u8Second * 10) + (pu8Data[7] - 48U);

        MEMSET(pu8Data, '\0', 10U);
        /* Clear Time flag */
        u8Flag &= ~CHANGE_TIME;
    }
}

/**
 *   @brief      This function updates the new date, month, year from lpuart communication.
 *
 *   @return     void                       xxxxxxxx
 *
 *   @note       Driver should be called in LPIT0_Ch0_IRQHandler function.
 *
 */
void GetNewDate(void)
{
    uint8 *pu8Data = (uint8 *)pu8ReceiveData;
    /* Update Time */
    if (u8Flag & CHANGE_DATE)
    {
        /* Get Date */
        u8Date = pu8Data[0] - 48U;
        u8Date = (u8Date * 10) + (pu8Data[1] - 48U);

        /* Get Month */
        u8Month = pu8Data[3] - 48U;
        u8Month = (u8Month * 10) + (pu8Data[4] - 48U);

        /* Get Year */
        u16Year = pu8Data[6] - 48U;
        u16Year = (u16Year * 10) + (pu8Data[7] - 48U);
        u16Year = (u16Year * 10) + (pu8Data[8] - 48U);
        u16Year = (u16Year * 10) + (pu8Data[9] - 48U);

        MEMSET(pu8Data, '\0', 10U);
        /* Clear Time flag */
        u8Flag &= ~CHANGE_DATE;
    }
}

/**
 *   @brief      This function returns the number of character in a string excluding null character.
 *
 *   @param[in]  uint8*                     Pointer to string
 *
 *   @return     uint16                     Number of character in given string
 *
 *   @note       Driver should be called in main function.
 *
 */
uint16 STRLEN(uint8 *string)
{
    uint16 u16Count = 0U;
    while (string[u16Count] != '\0')
    {
        u16Count++;
    }
    return u16Count;
}

/**
 *   @brief      This function compares 2 strings.
 *
 *   @param[in]  uint8*                     string1
 *   @param[in]  uint8*                     string2
 *
 *   @return     int8                       if buffer1 > buffer2 then return 1,
 *                                          if buffer1 < buffer2 then return -1
 *                                          else return 0
 *
 *   @note       Driver should be called in main function.
 *
 */
int8 STRCMP(uint8 *string1, uint8 *string2)
{
    uint16 u16StrLen1 = STRLEN(string1);
    uint16 u16StrLen2 = STRLEN(string2);
    uint16 u16MinLen = (u16StrLen1 > u16StrLen2) ? (u16StrLen2) : (u16StrLen1);
    uint16 u16MaxLen = (u16StrLen1 < u16StrLen2) ? (u16StrLen2) : (u16StrLen1);
    uint8 i;
    int8 result = 0;

    for (i = 0; i < u16MinLen; i++)
    {
        if (string1[i] < string2[i])
        {
            return -1;
        }
        else if (string1[i] > string2[i])
        {
            return 1;
        }
    }

    if (u16MinLen != u16MaxLen)
    {
        result = (u16MinLen == u16StrLen1) ? -1 : 1;
    }

    return result;
}

/**
 *   @brief      This function set value for buffer with length of buffer.
 *
 *   @param[in]  uint8*                     Buffer
 *   @param[in]  uint8                      Character
 *   @param[in]  uint16                     Len
 *
 *   @return     void                       xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void MEMSET(uint8 *Buffer, uint8 Character, uint16 Len)
{
    uint16 i;
    for (i = 0; i < Len; i++)
    {
        Buffer[i] = Character;
    }
}

/**
 *   @brief      This function updates date, month, year based on current date.
 *
 *   @return     void                       xxxxxxxx
 *
 *   @note       Driver should be called in LPIT0_Ch0_IRQHandler function.
 *
 */
void DateUpdate(void)
{
    uint8 i;
    uint16 temp;

    /* Update date */
    if (u8Flag & UPDATE_DATE)
    {
        u8Date += 1;

        /* Check valid date */
        if (u8Date > DaysInMonth(u8Month, u16Year))
        {
            u8Date = 1;
            u8Month += 1;
        }
        if (u8Month > 12)
        {
            u8Month = 1;
            u16Year += 1;
        }

        /* Clear Date flag */
        u8Flag &= ~UPDATE_DATE;
    }

    /* Format date */
    Date[0] = u8Date / 10 + 48U;
    Date[1] = u8Date % 10 + 176U;

    /* Format month */
    Date[2] = u8Month / 10 + 48U;
    Date[3] = u8Month % 10 + 176U;

    /* Format year */
    temp = u16Year;
    for (i = 0; i < 4; i++)
    {
        Date[7 - i] = temp % 10 + 48U;
        temp /= 10;
    }
}

/**
 *   @brief      This function updates second, minute, hour based on current time.
 *
 *   @return     void                       xxxxxxxx
 *
 *   @note       Driver should be called in LPIT0_Ch0_IRQHandler function.
 *
 */
void TimeUpdate(void)
{
    /* Update time */
    u8Second += 1;

    /* Check valid time */
    if (u8Second >= 60)
    {
        u8Second = 0;
        u8Minute += 1;
    }
    if (u8Minute >= 60)
    {
        u8Minute = 0;
        u8Hour += 1;
    }
    if (u8Hour >= 24)
    {
        u8Hour = 0;
        /* Update Date flag */
        u8Flag |= UPDATE_DATE;
    }

    /* Format Hours */
    Time[0] = u8Hour / 10 + 48;
    Time[1] = u8Hour % 10 + 48;
    Time[2] = 0XAU + 48;

    /* Format Minutes */
    Time[3] = u8Minute / 10 + 48;
    Time[4] = u8Minute % 10 + 48;
    Time[5] = 0XAU + 48;

    /* Format Seconds */
    Time[6] = u8Second / 10 + 48;
    Time[7] = u8Second % 10 + 48;
}

/**
 *   @brief      This function returns the number of dates in a specific month.
 *
 *   @param[in]  uint8                      Current month
 *   @param[in]  uint8                      Current year
 *
 *   @return     uint8                      Maximum number of dates in that month
 *
 *   @note       Driver should be called in DateUpdate() function.
 *
 */
uint8 DaysInMonth(uint8 Month, uint16 Year)
{

    switch (Month)
    {
    /*If current month is 1,3,5,7,8,10,12 => days in month is 31*/
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;

    /*If current month is 4,6,9,11 => days in month is 30*/
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;

    /*If current month is 2*/
    case 2:
        // Check for leap year
        if ((Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0))
            return 29;
        else
            return 28;
    }

    return 0;
}

/**
 *   @brief      This function performs a callback notification at the end of RX handler.
 *               Definition of this function is defined by user
 *
 *   @return     void                       xxxxxxxxx
 *
 *   @note       Driver should be called outside main function.
 *
 */
void LPUART_RX_Callback(void)
{
    uint8 *pu8Data = (uint8 *)pu8ReceiveData;
    if (STRLEN(pu8Data) == 10U)
    {
        u8Flag |= CHANGE_DATE;
    }
    else if (STRLEN(pu8Data) == 8U)
    {
        u8Flag |= CHANGE_TIME;
    }
}

/**
 *   @brief      This LPIT0_Ch0_IRQHandler function is used to update time and date for each 1000ms.
 *
 *   @return     void                       xxxxxxxxx
 *
 *   @note       Driver should be called outside main function.
 *
 */
void LPIT0_Ch0_IRQHandler(void)
{
    /* Check timer flag channel 0 */
    if (LPIT->MSR & (uint32)LPIT_CHANNEL0)
    {
        /* Clear flag LPIT channel 0 */
        LPIT->MSR |= (uint32)LPIT_CHANNEL0;

        /* Get date change */
        GetNewTime();

        /* Get date change */
        GetNewDate();

        /* Update time */
        TimeUpdate();

        /* Update date */
        DateUpdate();

        /* Update display flag */
        if (u8SW2State == 1)
        {
            u8Flag |= DISPLAY_DATE;
        }
        else
        {
            u8Flag |= DISPLAY_TIME;
        }
    }
}

/**
 *   @brief      This LPUART2_RxTx_IRQHandler function is used to process RXTX data from LPUART2.
 *
 *   @return     void                       xxxxxxxxx
 *
 *   @note       Driver should be called outside main function.
 *
 */
void LPUART2_RxTx_IRQHandler(void)
{
    LPUART_IRQHandling(&lpuart2);
}

/**
 *   @brief      This LPSPI1_IRQHandler function is used to process RXTX data from LPSPI1.
 *
 *   @return     void                       xxxxxxxxx
 *
 *   @note       Driver should be called outside main function.
 *
 */
void LPSPI1_IRQHandler(void)
{
    LPSPI_IRQHandling(&lpspi1);
}

/**
 *   @brief      This PORTC_IRQHandler function is used to change the status of button SW2, SW3.
 *
 *   @return     void                       xxxxxxxxx
 *
 *   @note       Driver should be called outside main function.
 *
 */
void PORTC_IRQHandler(void)
{
    /* Check interrupt flag at SW2 */
    if ((PORTC->PCR[12] >> PORT_PCR_ISF_SHIFT) & 0X01U)
    {
        /* CLear interrupt flag at SW2 */
        PORTC->PCR[12] |= PORT_PCR_ISF_MASK;

        /* Update button state */
        u8SW2State = (u8SW2State == 1) ? (0) : (u8SW2State + 1);
    }
    /* Check interrupt flag at SW3 */
    if ((PORTC->PCR[13] >> PORT_PCR_ISF_SHIFT) & 0X01U)
    {
        /* CLear interrupt flag at SW3 */
        PORTC->PCR[13] |= PORT_PCR_ISF_MASK;

        /* Update button state */
        u8SW3State = (u8SW3State == 1) ? (0) : (u8SW3State + 1);

        /* Update display mode */
        if (u8SW3State == 0)
        {
            SevenSeg_SetDisplay(&lpspi1);
        }
        else
        {
            SevenSeg_ClearDisplay(&lpspi1);
        }
    }
}
