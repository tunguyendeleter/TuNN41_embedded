#ifndef SPI_H_
#define SPI_H_

/******************************************************************************
 *  INCLUDES
 *****************************************************************************/
#include "stm32f411xx.h"

/******************************************************************************
 *  DEFINES & MACROS
 *****************************************************************************/
/**
* @brief  Define SPI control register 1 bit macros
*/
#define SPI_CR1_BIDIMODE_SHIFT				15U
#define SPI_CR1_BIDIOE_SHIFT				14U
#define SPI_CR1_CRCEN_SHIFT					13U
#define SPI_CR1_CRCNEXT_SHIFT				12U
#define SPI_CR1_DFF_SHIFT					11U
#define SPI_CR1_RXONLY_SHIFT				10U
#define SPI_CR1_SSM_SHIFT					9U
#define SPI_CR1_SSI_SHIFT					8U
#define SPI_CR1_LSBFIRST_SHIFT				7U
#define SPI_CR1_SPE_SHIFT					6U
#define SPI_CR1_BR_SHIFT					3U
#define SPI_CR1_MSTR_SHIFT					2U
#define SPI_CR1_CPOL_SHIFT					1U
#define SPI_CR1_CPHA_SHIFT					0U

/**
* @brief  Define SPI control register 2 bit macros
*/
#define SPI_CR2_TXEIE_SHIFT					7U
#define SPI_CR2_RXNEIE_SHIFT				6U
#define SPI_CR2_ERRIE_SHIFT					5U
#define SPI_CR2_FRF_SHIFT					4U
#define SPI_CR2_SSOE_SHIFT					2U
#define SPI_CR2_TXDMAEN_SHIFT				1U
#define SPI_CR2_RXDMAEN_SHIFT				0U

/**
* @brief  Define SPI status register bit macros
*/
#define SPI_SR_FRE_SHIFT					8U
#define SPI_SR_BSY_SHIFT					7U
#define SPI_SR_OVR_SHIFT					6U
#define SPI_SR_MODF_SHIFT					5U
#define SPI_SR_CRCERR_SHIFT					4U
#define SPI_SR_UDR_SHIFT					3U
#define SPI_SR_CHSIDE_SHIFT					2U
#define SPI_SR_TXE_SHIFT					1U
#define SPI_SR_RXNE_SHIFT					0U


/*
 * SPI Application States
 */
#define SPI_READY							0U
#define SPI_BUSY_IN_RX						1U
#define SPI_BUSY_IN_TX						2U

/*
 * SPI Application events
 */
#define SPI_EVENT_TX_CMPLT					0U
#define SPI_EVENT_RX_CMPLT					1U
#define SPI_EVENT_MODF_ERR					2U
#define SPI_EVENT_OVR_ERR					3U
#define SPI_EVENT_CRC_ERR					4U
#define SPI_EVENT_FRE_ERR					5U

/*
 * @SPI_DeviceMode
 */
#define SPI_DEVICE_MODE_MASTER				1U
#define SPI_DEVICE_MODE_SLAVE				0U

/*
 * @SPI_BusConfig
 */
#define SPI_BUS_CONFIG_FD					1U
#define SPI_BUS_CONFIG_HD					2U
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY		3U

/*
 * @SPI_SclkSpeed
 */
#define SPI_SCLK_SPEED_DIV2					0U
#define SPI_SCLK_SPEED_DIV4					1U
#define SPI_SCLK_SPEED_DIV8					2U
#define SPI_SCLK_SPEED_DIV16				3U
#define SPI_SCLK_SPEED_DIV32				4U
#define SPI_SCLK_SPEED_DIV64				5U
#define SPI_SCLK_SPEED_DIV128				6U
#define SPI_SCLK_SPEED_DIV256				7U

/*
 * @SPI_DFF
 */
#define SPI_DFF_8BITS						0U
#define SPI_DFF_16BITS						1U

/*
 * @SPI_CPOL
 */
#define SPI_CPOL_HIGH						1U
#define SPI_CPOL_LOW						0U

/*
 * @SPI_CPHA
 */
#define SPI_CPHA_HIGH						1U
#define SPI_CPHA_LOW						0U

/*
 * @SPI_SSM
 */
#define SPI_SSM_EN							1U
#define SPI_SSM_DI							0U

/*
 * SPI related status flag definitions
 */
#define SPI_RXNE_flag						(SPI_SR_RXNE_SHIFT)
#define SPI_TXE_flag						(SPI_SR_TXE_SHIFT)
#define SPI_CHSIDE_flag						(SPI_SR_CHSIDE_SHIFT)
#define SPI_UDR_flag						(SPI_SR_UDR_SHIFT)
#define SPI_CRCERR_flag						(SPI_SR_CRCERR_SHIFT)
#define SPI_MODF_flag						(SPI_SR_MODF_SHIFT)
#define SPI_OVR_flag						(SPI_SR_OVR_SHIFT)
#define SPI_BSY_flag						(SPI_SR_BSY_SHIFT)
#define SPI_SRE_flag						(SPI_SR_FRE_SHIFT)


/******************************************************************************
 *  TYPEDEFS
 *****************************************************************************/
/*
 * Configuration structure for SPIx peripheral
 */
typedef struct
{
	uint8 DeviceMode;	
	uint8 BusConfig;
	uint8 SclkSpeed;
	uint8 DFF;
	uint8 CPOL;
	uint8 CPHA;
	uint8 SSM;
} SPI_Config_Type;

/*
 * Handle structure for SPIx peripheral
 */
typedef struct
{
	SPI_Type *pSPIx; 	/*!< This holds the base address of SPIx(x:0,1,2) peripheral >*/
	SPI_Config_Type SPIConfig;
	// uint8_t *pTxBuffer; /* !< To store the app. Tx buffer address > */
	// uint8_t *pRxBuffer; /* !< To store the app. Rx buffer address > */
	// uint32_t TxLen;		/* !< To store the Tx len > */
	// uint32_t RxLen;		/* !< To store the Rx len > */
	// uint8_t TxState;	/* !< To store the Tx state > */
	// uint8_t RxState;	/* !< To store the Rx len > */
} SPI_Handle_Type;

/******************************************************************************
 *  GLOBAL VARIABLES
 *****************************************************************************/

/**
* @brief  this function setup global clock to SPI
*/
extern void SPI_PeriClockControl(SPI_Type *pSPIx, uint8 EnorDis);

/**
* @brief  this function configures SPI dataframe
*/
extern void SPI_Init(SPI_Handle_Type* pSPIHandle);

/**
* @brief  this function write and read data
*/
extern void SPI_Write(SPI_Handle_Type* pSPIHandle, uint8* pTxBuffer, uint32 Len);
extern void SPI_Read(SPI_Handle_Type *pSPIHandle, uint8 *pRxBuffer, uint32 Len);

/**
* @brief  this function write and read data with interrupt
*/
extern uint8 SPI_WriteIT(SPI_Handle_Type *pSPIHandle, uint8 *pTxBuffer, uint32 Len);
extern uint8 SPI_ReadIT(SPI_Handle_Type *pSPIHandle, uint8 *pRxBuffer, uint32 Len);
extern void SPI_IRQHandling(SPI_Handle_Type *pSPIHandle);

/**
* @brief  this function gets and clears status flag
*/
extern uint8 SPI_GetFlagStatus(SPI_Type *pSPIx, uint8 StatusFlagShift);
extern void SPI_ClearFlagStatus(SPI_Type *pSPIx, uint8 StatusFlagShift);
/******************************************************************************
 *  GLOBAL FUNCTION
 *****************************************************************************/

#endif /* SPI_H_ */
