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
 *   @brief      This function enable global clock, and configure functional clock to LPIT module.
 *
 *   @param[in]  LPIT_HandleType* pLPIT_Handle          Pointer to LPIT handler
 *
 *   @return     void                                   xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void LPIT_PeripheralClockConfig(LPIT_HandleType *pLPIT_Handle)
{
    /* Enable function clock to LPIT */
    PCC->PCC_LPIT |= (pLPIT_Handle->LPIT_Config.ClockSource << PCC_PCS_SHIFT);

    /* Enable global clock to LPIT */
    PCC->PCC_LPIT |= (1 << PCC_CGC_SHIFT);
}

/**
 *   @brief      This function configure reload value, timer channel, timer mode to LPIT module.
 *
 *   @param[in]  LPIT_HandleType* pLPIT_Handle          Pointer to LPIT handler
 *
 *   @return     void                                   xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void LPIT_Init(LPIT_HandleType *pLPIT_Handle)
{
    uint32 temp = 0U;
    uint8 i;
    /* Configure Module Status */
    pLPIT_Handle->pLPITx->MCR |= (uint32)pLPIT_Handle->LPIT_Config.Status;

    /* Configure Timer mode for all channels */
    for (i = 0; i < 4; i++)
    {
        /* Setup mode on channels */
        if (pLPIT_Handle->LPIT_Config.Channel & (uint8)(1 << i))
        {
            /* Time out period: CountValue */
            pLPIT_Handle->pLPITx->CHANNEL[i].TVAL = pLPIT_Handle->LPIT_Config.ReloadValue[i] - 1;

            /* Chose operation mode */
            temp |= (pLPIT_Handle->LPIT_Config.OpMode << LPIT_TCTRL_MODE_SHIFT);

            /* Enable timer channel */
            temp |= (1 << LPIT_TCTRL_TEN_SHIFT);

            pLPIT_Handle->pLPITx->CHANNEL[i].TCTRL |= temp;
            temp = 0U;

            /* Setup interrupt enable on channels */
            if (pLPIT_Handle->LPIT_Config.InterruptControl == LPIT_INTERRUPT_ENABLE)
            {
                pLPIT_Handle->pLPITx->MIER |= (uint32)(1 << i);
            }
        }
    }
}

/**
 *   @brief      This function start timer on all configured channels of LPIT module.
 *
 *   @param[in]  LPIT_HandleType* pLPIT_Handle          Pointer to LPIT handler
 *
 *   @return     void                                   xxxxxxxx
 *
 *   @note       Driver should be called after LPIT initialization.
 *
 */
void LPIT_StartTimer(LPIT_HandleType *pLPIT_Handle)
{
    uint8 i;
    /* Timer enable channel x */
    for (i = 0; i < 4; i++)
    {
        if (pLPIT_Handle->LPIT_Config.Channel & (uint8)(1 << i))
        {
            pLPIT_Handle->pLPITx->CHANNEL[i].TCTRL |= (1 << LPIT_TCTRL_TEN_SHIFT);
        }
    }
}

/**
 *   @brief      This function stop timer on all configured channels of LPIT module.
 *
 *   @param[in]  LPIT_HandleType* pLPIT_Handle          Pointer to LPIT handler
 *
 *   @return     void                                   xxxxxxxx
 *
 *   @note       Driver should be called in main function.
 *
 */
void LPIT_StopTimer(LPIT_HandleType *pLPIT_Handle)
{
    uint8 i;
    /*Timer disable channel x */
    for (i = 0; i < 4; i++)
    {
        if (pLPIT_Handle->LPIT_Config.Channel & (uint8)(1 << i))
        {
            pLPIT_Handle->pLPITx->CHANNEL[i].TCTRL &= ~(1 << LPIT_MCR_M_CEN_SHIFT);
        }
    }
}
