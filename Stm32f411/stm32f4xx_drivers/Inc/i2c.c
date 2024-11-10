/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "i2c.h"
#include "stm32f411xx.h"

/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/
void I2C_PeriClockControl(I2C_Type *pI2Cx, uint8 EnorDis)
{
    if (EnorDis == ENABLE)
    {
        if (pI2Cx == I2C1)
            I2C1_CLK_EN();
        else if (pI2Cx == I2C2)
            I2C2_CLK_EN();
        else if (pI2Cx == I2C3)
            I2C3_CLK_EN();
    }
    else if (EnorDis == DISABLE)
    {
        if (pI2Cx == I2C1)
            I2C1_CLK_DIS();
        else if (pI2Cx == I2C2)
            I2C2_CLK_DIS();
        else if (pI2Cx == I2C3)
            I2C3_CLK_DIS();
    }
}

void I2C_Init(I2C_Handle_Type *pI2CHandle)
{
    uint32 temp = 0U;

    /* Reset I2C bus */
    pI2CHandle->pI2Cx->CR1 |= (1 << I2C_CR1_SWRST_SHIFT);
    pI2CHandle->pI2Cx->CR1 &= ~(1 << I2C_CR1_SWRST_SHIFT);

    /* Configure FREQ of I2C */
    temp |= RCC_GetPCLK1Value();
    pI2CHandle->pI2Cx->CR2 |= (temp / 1000000) & 0X3F;
    temp = 0U;

    /* Configure device address */
    temp |= (1 << 14); /* always set this bit to 1 */
    temp |= (pI2CHandle->I2C_Config.I2C_DeviceAddress << I2C_OAR1_ADD1_71_SHIFT);
    pI2CHandle->pI2Cx->OAR1 |= (temp & 0XFF);
    temp = 0U;

    /* Configure Duty cycle of I2C */
    if (pI2CHandle->I2C_Config.I2C_SCLSpeed > I2C_SCL_SPEED_SM)
    {
        /* Select I2C mode */
        temp |= (1 << I2C_CCR_FS_SHIFT);

        /* select FM duty cycle */
        temp |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle << I2C_CCR_DUTY_SHIFT);

        /* Calculate frequency of FM */
        if (pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2)
        {
            temp |= RCC_GetPCLK1Value() / (pI2CHandle->I2C_Config.I2C_SCLSpeed * 3);
        }
        else if (pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_16_9)
        {
            temp |= RCC_GetPCLK1Value() / (pI2CHandle->I2C_Config.I2C_SCLSpeed * 25);
        }
    }
    else if (pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
    {
        temp |= RCC_GetPCLK1Value() / (pI2CHandle->I2C_Config.I2C_SCLSpeed * 2);
    }
    pI2CHandle->pI2Cx->CCR |= (temp & 0XFFF);
    temp = 0U;

    /* Configure the AKC control */
    temp |= (pI2CHandle->I2C_Config.I2C_ACKControl << I2C_CR1_ACK_SHIFT);
    // pI2CHandle->pI2Cx->CR1 |= temp;
    pI2CHandle->pI2Cx->CR1 |= (1 << I2C_CR1_PE_SHIFT) | (1 << I2C_CR1_ACK_SHIFT);
    temp = 0U;
}

uint8 I2C_GetFlagStatus(I2C_Handle_Type *pI2CHandle, uint8 StatusFlagShift)
{
    /* Read specific flag of SR1 */
    uint8 temp;
    temp = (pI2CHandle->pI2Cx->SR1 >> StatusFlagShift) & 0X01U;
    return temp;
}

void I2C_MasterClearADDR(I2C_Handle_Type *pI2CHandle)
{
    /* Read SR1 and SR2 to clear ADDR flag */
    uint32 dummy;
    dummy = pI2CHandle->pI2Cx->SR1;
    dummy = pI2CHandle->pI2Cx->SR2;
    (void)dummy;
}

void I2C_MasterManageACK(I2C_Handle_Type *pI2CHandle, uint8 EnorDis)
{
    if (EnorDis == I2C_ACK_ENABLE)
    {
        /* send ACK bit after read or write DR */
        pI2CHandle->pI2Cx->CR1 |= (1 << I2C_CR1_ACK_SHIFT);
    }
    else
    {
        /* send NACK bit after read or write DR */
        pI2CHandle->pI2Cx->CR1 &= ~(1 << I2C_CR1_ACK_SHIFT);
    }
}

void I2C_MasterWriteStart(I2C_Handle_Type *pI2CHandle)
{
    pI2CHandle->pI2Cx->CR1 |= (1 << I2C_CR1_START_SHIFT);
}

void I2C_MasterWriteStop(I2C_Handle_Type *pI2CHandle)
{
    pI2CHandle->pI2Cx->CR1 |= (1 << I2C_CR1_STOP_SHIFT);
}

void I2C_MasterWrite(I2C_Handle_Type *pI2CHandle, uint8 *pTxBuffer, uint32 Len, uint8 SlaveAddress)
{
    uint8 i;

    /* 1. generate the START condition */
    I2C_MasterWriteStart(pI2CHandle);

    /* 2. confirm that start generation is completed by checking the SB flag in the SR1
        NOTE: Until the SB is cleared SCL will be stretched (pulled to LOW) */
    while (!I2C_GetFlagStatus(pI2CHandle, I2C_SR1_SB_SHIFT))
    {
        /* do nothing */
    }

    /* 3. send the address of the slave with r/w bit set to w(0) (total 8 bits) */
    pI2CHandle->pI2Cx->DR = (((SlaveAddress << 1) | (I2C_WRITE_BIT << 0)) & 0XFF);

    /* 4. confirm that the address phase is completed by checking the ADDR flag in SR1 */
    while (!I2C_GetFlagStatus(pI2CHandle, I2C_SR1_ADDR_SHIFT))
    {
        /* do nothing */
    }

    /* 5. clear the ADDR flag according to its software sequence
        NOTE: Until the ADDR is cleared SCL will be stretched (pulled to LOW) */
    I2C_MasterClearADDR(pI2CHandle);

    /* 6. send the data until len is 0 */
    for (i = Len; i > 0; i--)
    {
        while (!I2C_GetFlagStatus(pI2CHandle, I2C_SR1_TXE_SHIFT)) // buffer empty
        {
            /* do nothing */
        }
        pI2CHandle->pI2Cx->DR = (pTxBuffer[Len - i] & 0XFF);
    }

    /* 7. when len is 0, wait for TXE = 1, and BTF = 1, before generating the STOP condition
        NOTE: TXE = 1, BTF = 1, means that both SR and DR are empty and next transmisstion
        should begin when BTF = 1, SCL will be stretched (pulled to LOW) */
    while (!I2C_GetFlagStatus(pI2CHandle, I2C_SR1_TXE_SHIFT))
    {
        /* do nothing */
    }
    while (!I2C_GetFlagStatus(pI2CHandle, I2C_SR1_BTF_SHIFT))
    {
        /* do nothing */
    }

    /* 8. generate STOP condition and master need not to wait for the completion of stop condition
        NOTE: generating STOP, automatically clears the BTF */
    I2C_MasterWriteStop(pI2CHandle);
}

void I2C_MasterRead(I2C_Handle_Type *pI2CHandle, uint8 *pRxBuffer, uint32 Len, uint8 SlaveAddress)
{
    uint8 i;

    /* 1. generate the START condition */
    I2C_MasterWriteStart(pI2CHandle);

    /* 2. confirm that start generation is completed by checking the SB flag in the SR1
        NOTE: Until the SB is cleared SCL will be stretched (pulled to LOW) */
    while (!I2C_GetFlagStatus(pI2CHandle, I2C_SR1_SB_SHIFT))
    {
        /* do nothing */
    }

    /* 3. send the address of the slave with r/w bit set to R(1) (total 8 bits) */
    pI2CHandle->pI2Cx->DR = (((SlaveAddress << 1) | (I2C_READ_BIT << 0)) & 0XFF);

    /* 4. wait until address phase is completed by checking the ADDR flag in the SR1 */
    while (!I2C_GetFlagStatus(pI2CHandle, I2C_SR1_ADDR_SHIFT))
    {
        /* do nothing */
    }
    I2C_MasterClearADDR(pI2CHandle);

    /* 5. read every bytes sent from receiver */
    /* If the len is more than one then send back ACK to continue receiving */
    I2C_MasterManageACK(pI2CHandle, I2C_ACK_ENABLE);
    for (i = Len; i > 0; i--)
    {
        /* If the len is one then send back NACK to stop receiving */
        if (i == 1U)
        {
            /* send NACK */
            I2C_MasterManageACK(pI2CHandle, I2C_ACK_DISABLE);
        }

        /* Check if the RXNE buffer is full */
        while (!I2C_GetFlagStatus(pI2CHandle, I2C_SR1_RXNE_SHIFT))
        {
            /* do nothing */
        }

        /* Receive byte within DR */
        pRxBuffer[Len - i] = (uint8)(pI2CHandle->pI2Cx->DR & 0XFF);
    }

    /* generate STOP condition */
    I2C_MasterWriteStop(pI2CHandle);

    /* Re-enable ACKing */
    pI2CHandle->pI2Cx->CR1 |= (pI2CHandle->I2C_Config.I2C_ACKControl << I2C_CR1_ACK_SHIFT);
}
