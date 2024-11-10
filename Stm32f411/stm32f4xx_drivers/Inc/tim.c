/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "tim.h"
#include "stm32f411xx.h"


/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/

void TIM_PeriClockControl(TIM_Type *pTIMx, uint8 EnorDis)
{
    if (EnorDis == ENABLE)
    {
        if (pTIMx == TIM1)
            TIM1_CLK_EN();
    }
    else if (EnorDis == DISABLE)
    {
        if (pTIMx == TIM1)
            TIM1_CLK_DIS();
    }
}
