/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "systick.h"
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

void SysTick_Init(uint32 CountValue, uint8 ClockSource)
{
    /* Disable timer to configure timer */
    SysTick->CSR &= ~(1 << SYSTICK_CSR_ENABLE_SHIFT);

    /* Configure clock source from processor */
    SysTick->CSR |= (ClockSource << SYSTICK_CSR_CLKSOURCE_SHIFT);

    /* Enable interrupt request to  systick timer */
    SysTick->CSR |= (1 << SYSTICK_CSR_TICKINT_SHIFT);

    /* Reload value [0:24] bits: max count value = 16,777,215 - 1 */
    SysTick->RVR = CountValue & SYSTICK_CVR_CURRENT_MASK;

    /* Clear current value */
    SysTick->CVR = 1;

    /* Enable timer to configure timer*/
    // SysTick->CSR |= (1 << SYSTICK_CSR_ENABLE_SHIFT);
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
    SysTick->CSR |= (1 << SYSTICK_CSR_ENABLE_SHIFT);
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
    SysTick->CSR &= ~(1 << SYSTICK_CSR_ENABLE_SHIFT);
}
