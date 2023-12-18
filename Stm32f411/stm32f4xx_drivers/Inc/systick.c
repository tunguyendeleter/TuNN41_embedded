/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "nvic.h"
#include "stm32f411xx.h"

/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/

/**
 *   @brief      This function configures SysTick timer modules
 *
 *   @param[in]  uint32 CountValue              Reload value to RVR register
 *
 *   @return     void                           xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */

void SysTick_Init(uint32 CountValue)
{
    /* Disable timer to configure timer*/
    SysTick->CSR &= ~(1 << 0);

    /* Configure clock source from processor */
    SysTick->CSR |= (1 << 2);

    /* Enable interrupt request to  systick timer */
    SysTick->CSR |= (1 << 1);

    /* Reload value */
    SysTick->RVR = CountValue;

    /* Clear current value */
    SysTick->CVR = 1;

    /* Enable timer to configure timer*/
    SysTick->CSR |= (1 << 0);
}

/**
 *   @brief      This function enbales SysTick timer to start
 *
 *   @return     void                           xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void SysTick_StartTimer(void)
{
    /* Enable timer to configure timer*/
    SysTick->CSR |= (1 << 0);
}

/**
 *   @brief      This function disables SysTick timer to stop
 *
 *   @return     void                           xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void SysTick_StopTimer(void)
{
    /* Disable timer to configure timer*/
    SysTick->CSR &= ~(1 << 0);
}
