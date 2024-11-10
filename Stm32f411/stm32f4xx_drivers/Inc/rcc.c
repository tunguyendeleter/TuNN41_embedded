#include "rcc.h"

static uint16 AHB_prescaler[9] = {2, 4, 8, 16, 32, 64, 128, 256, 512};
static uint8 APB_prescaler[4] = {2, 4, 8, 16};

uint32 RCC_GetPLLValue(void)
{
    return 0;
}

uint32 RCC_GetPCLK1Value(void)
{
    uint8 tempsws, tempAHB, tempAPB1;
    uint16 tempAHBPre, tempAPB1Pre;
    uint32 tempclk;

    tempsws = (RCC->CFGR >> 2) & 0X3;
    if (tempsws == 0)
    {
        tempclk = 16000000;
    }
    else if (tempsws == 1)
    {
        tempclk = 8000000;
    }
    else if (tempsws == 2)
    {
        tempclk = RCC_GetPLLValue();
    }

    tempAHB = (RCC->CFGR >> 4) & 0XF;
    if (tempAHB < 8)
    {
        tempAHBPre = 1;
    }
    else if (tempAHB >= 8)
    {
        tempAHBPre = AHB_prescaler[tempAHB - 8];
    }

    tempAPB1 = (RCC->CFGR >> 10) & 0X7;
    if (tempAPB1 < 4)
    {
        tempAPB1Pre = 1;
    }
    else if (tempAPB1 >= 4)
    {
        tempAPB1Pre = APB_prescaler[tempAPB1 - 4];
    }

    tempclk = (tempclk / tempAHBPre) / tempAPB1Pre;
    return tempclk;
}

uint32 RCC_GetPCLK2Value(void)
{
    uint8 tempsws, tempAHB, tempAPB2;
    uint16 tempAHBPre, tempAPB2Pre;
    uint32 tempclk;

    tempsws = (RCC->CFGR >> 2) & 0X3;
    if (tempsws == 0)
    {
        tempclk = 16000000;
    }
    else if (tempsws == 1)
    {
        tempclk = 8000000;
    }
    else if (tempsws == 2)
    {
        tempclk = RCC_GetPLLValue();
    }

    tempAHB = (RCC->CFGR >> 4) & 0XF;
    if (tempAHB < 8)
    {
        tempAHBPre = 1;
    }
    else if (tempAHB >= 8)
    {
        tempAHBPre = AHB_prescaler[tempAHB - 8];
    }

    tempAPB2 = (RCC->CFGR >> 13) & 0X7;
    if (tempAPB2 < 4)
    {
        tempAPB2Pre = 1;
    }
    else if (tempAPB2 >= 4)
    {
        tempAPB2Pre = APB_prescaler[tempAPB2 - 4];
    }

    tempclk = (tempclk / tempAHBPre) / tempAPB2Pre;
    return tempclk;
}
