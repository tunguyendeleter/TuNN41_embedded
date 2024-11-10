#ifndef I2C_H_
#define I2C_H_

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "stm32f411xx.h"
#include "rcc.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/**
* @brief  Define I2C control register 1 macros
*/
#define I2C_CR1_SWRST_SHIFT				    15U
#define I2C_CR1_ALERT_SHIFT				    13U
#define I2C_CR1_PEC_SHIFT					12U
#define I2C_CR1_POS_SHIFT				    11U
#define I2C_CR1_ACK_SHIFT					10U
#define I2C_CR1_STOP_SHIFT				    9U
#define I2C_CR1_START_SHIFT				    8U
#define I2C_CR1_NOSTRETCH_SHIFT				7U
#define I2C_CR1_ENGC_SHIFT				    6U
#define I2C_CR1_ENPEC_SHIFT				    5U
#define I2C_CR1_ENARP_SHIFT				    4U
#define I2C_CR1_SMBTYPE_SHIFT				3U
#define I2C_CR1_SMBUS_SHIFT				    1U
#define I2C_CR1_PE_SHIFT				    0U

/**
* @brief  Define I2C Control register 2 macros
*/
#define I2C_CR2_LAST_SHIFT				    12U
#define I2C_CR2_DMAEN_SHIFT				    11U
#define I2C_CR2_ITBUFEN_SHIFT				10U
#define I2C_CR2_ITEVTEN_SHIFT               9U
#define I2C_CR2_ITERREN_SHIFT				8U
#define I2C_CR2_FREQ_SHIFT				    0U

/**
* @brief  Define I2C Own address register 1 macros
*/
#define I2C_OAR1_ADDMODE_SHIFT              15U
#define I2C_OAR1_ADD1_98_SHIFT              8U
#define I2C_OAR1_ADD1_71_SHIFT              1U
#define I2C_OAR1_ADD1_0_SHIFT               0U

/**
* @brief  Define I2C Own address register 2 macros
*/
#define I2C_OAR2_ADD2_71_SHIFT              8U
#define I2C_OAR2_ENDUAL_SHIFT               0U

/**
* @brief  Define I2C Status register 1 macros
*/
#define I2C_SR1_SMBALERT_SHIFT              15U
#define I2C_SR1_TIMEOUT_SHIFT               14U
#define I2C_SR1_PECERR_SHIFT                12U
#define I2C_SR1_OVR_SHIFT                   11U
#define I2C_SR1_AF_SHIFT                    10U
#define I2C_SR1_ARLO_SHIFT                  9U
#define I2C_SR1_BERR_SHIFT                  8U
#define I2C_SR1_TXE_SHIFT                   7U
#define I2C_SR1_RXNE_SHIFT                  6U
#define I2C_SR1_STOPF_SHIFT                 4U
#define I2C_SR1_ADD10_SHIFT                 3U
#define I2C_SR1_BTF_SHIFT                   2U
#define I2C_SR1_ADDR_SHIFT                  1U
#define I2C_SR1_SB_SHIFT                    0U

/**
* @brief  Define I2C Status register 2 macros
*/
#define I2C_SR2_PEC_SHIFT                   8U
#define I2C_SR2_DUALF_SHIFT                 7U
#define I2C_SR2_SMBHOST_SHIFT               6U
#define I2C_SR2_SMBDEFAULT_SHIFT            5U
#define I2C_SR2_GENCALL_SHIFT               4U
#define I2C_SR2_TRA_SHIFT                   2U
#define I2C_SR2_BUSY_SHIFT                  1U
#define I2C_SR2_MSL_SHIFT                   0U

/**
* @brief  Define I2C Clock control register macros
*/
#define I2C_CCR_FS_SHIFT                    15U
#define I2C_CCR_DUTY_SHIFT                  14U
#define I2C_CCR_CCR_SHIFT                   0U

/**
* @brief  Define TRISE register macros
*/
#define I2C_TRISE_TRISE_SHIFT               15U

/**
* @brief  Define FLTR register macros
*/
#define I2C_FLTR_ANOFF_SHIFT                4U
#define I2C_FLTR_DNF_SHIFT                  0U

/**
* @brief  @I2C_SCLSpeed
*/
#define I2C_SCL_SPEED_SM 					100000U
#define I2C_SCL_SPEED_FM4K 					400000U
#define I2C_SCL_SPEED_FM2K 					200000U

/**
* @brief  @I2C_ACKControl
*/
#define I2C_ACK_ENABLE 						1U
#define I2C_ACK_DISABLE						0U

/**
* @brief  @I2C_FMDutyCycle
*/
#define I2C_FM_DUTY_2						1U
#define I2C_FM_DUTY_16_9					0U

/**
* @brief  Define read/write bit of I2C address information
*/
#define I2C_WRITE_BIT						0U
#define I2C_READ_BIT						1U

/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/
/*
 * Configuration structure for I2Cx peripheral
 */
typedef struct
{
	uint32 I2C_SCLSpeed;
	uint8 I2C_DeviceAddress;
	uint8 I2C_ACKControl;
	uint8 I2C_FMDutyCycle;
} I2C_Config_Type;

/*
 * Handle structure for I2Cx peripheral
 */
typedef struct
{
	I2C_Type *pI2Cx; 	/*!< This holds the base address of I2Cx(x:0,1,2) peripheral >*/
	I2C_Config_Type I2C_Config;
	// uint8_t *pTxBuffer; /* !< To store the app. Tx buffer address > */
	// uint8_t *pRxBuffer; /* !< To store the app. Rx buffer address > */
	// uint32_t TxLen;		/* !< To store the Tx len > */
	// uint32_t RxLen;		/* !< To store the Rx len > */
	// uint8_t TxState;	/* !< To store the Tx state > */
	// uint8_t RxState;	/* !< To store the Rx len > */
} I2C_Handle_Type;

/******************************************************************************
 *  GLOBAL VARIABLES
 *****************************************************************************/

/******************************************************************************
 *  GLOBAL FUNCTION PROTOCOLS
 *****************************************************************************/
/**
* @brief  this function setup global clock to I2C
*/
extern void I2C_PeriClockControl(I2C_Type *pI2Cx, uint8 EnorDis);

/**
* @brief  this function configures I2C dataframe
*/
extern void I2C_Init(I2C_Handle_Type* pI2CHandle);
extern void I2C_DeInit(I2C_Handle_Type* pI2CHandle);

/**
* @brief  this function configures ISR handling for I2C
*/
extern void I2C_IRQInterruptConfig(I2C_Handle_Type* pI2CHandle);
extern void I2C_IRQPriorityConfig(I2C_Handle_Type* pI2CHandle);

/**
* @brief  this function master write and read data
*/
extern void I2C_MasterClearADDR(I2C_Handle_Type *pI2CHandle);
extern void I2C_MasterManageACK(I2C_Handle_Type *pI2CHandle, uint8 EnorDis);
extern void I2C_MasterWriteStart(I2C_Handle_Type *pI2CHandle);
extern void I2C_MasterWriteStop(I2C_Handle_Type *pI2CHandle); 
extern void I2C_MasterWrite(I2C_Handle_Type* pI2CHandle, uint8* pTxBuffer, uint32 Len, uint8 SlaveAddress);
extern void I2C_MasterRead(I2C_Handle_Type *pI2CHandle, uint8 *pRxBuffer, uint32 Len, uint8 SlaveAddress);

/**
* @brief  this function write and read data with interrupt
*/
extern uint8 I2C_WriteIT(I2C_Handle_Type *pI2CHandle, uint8 *pTxBuffer, uint32 Len);
extern uint8 I2C_ReadIT(I2C_Handle_Type *pI2CHandle, uint8 *pRxBuffer, uint32 Len);
extern void I2C_IRQHandling(I2C_Handle_Type *pI2CHandle);

/**
* @brief  this function gets status flag
*/
extern uint8 I2C_GetFlagStatus(I2C_Handle_Type *pI2CHandle, uint8 StatusFlagShift);

#endif /* I2C_H_ */
