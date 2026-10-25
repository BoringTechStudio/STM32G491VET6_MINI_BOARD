/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           USB_Device/MSC_Standalone/USB_Device/App/usbd_storage_if.c
  * @author         MCD Application Team (adapted for W25Q SPI flash)
  * @brief          Memory management layer backed by W25Q SPI NOR flash.
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_storage_if.h"
#include "w25q_flash.h"

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @{
  */

/** @defgroup USBD_STORAGE
  * @{
  */

/** @defgroup USBD_STORAGE_Private_Defines
  * @{
  */

#define STORAGE_LUN_NBR                  1
#define STORAGE_BLK_SIZ                  0x200

/** @defgroup USBD_STORAGE_Exported_Variables
  * @{
  */

extern USBD_HandleTypeDef hUsbDeviceFS;

/** @defgroup USBD_STORAGE_Private_Variables
  * @{
  */

/** USB Mass storage Standard Inquiry Data. */
const int8_t STORAGE_Inquirydata_FS[] = {/* 36 */

  /* LUN 0 */
  0x00,
  0x80,
  0x02,
  0x02,
  (STANDARD_INQUIRY_DATA_LEN - 5),
  0x00,
  0x00,
  0x00,
  'S', 'T', 'M', ' ', ' ', ' ', ' ', ' ', /* Manufacturer : 8 bytes */
  'P', 'r', 'o', 'd', 'u', 'c', 't', ' ', /* Product      : 16 Bytes */
  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
  '0', '.', '0' ,'1'                      /* Version      : 4 Bytes */
};

/** @defgroup USBD_STORAGE_Private_FunctionPrototypes
  * @{
  */

static int8_t STORAGE_Init_FS(uint8_t lun);
static int8_t STORAGE_GetCapacity_FS(uint8_t lun, uint32_t *block_num, uint16_t *block_size);
static int8_t STORAGE_IsReady_FS(uint8_t lun);
static int8_t STORAGE_IsWriteProtected_FS(uint8_t lun);
static int8_t STORAGE_Read_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
static int8_t STORAGE_Write_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
static int8_t STORAGE_GetMaxLun_FS(void);

USBD_StorageTypeDef USBD_Storage_Interface_fops_FS =
{
  STORAGE_Init_FS,
  STORAGE_GetCapacity_FS,
  STORAGE_IsReady_FS,
  STORAGE_IsWriteProtected_FS,
  STORAGE_Read_FS,
  STORAGE_Write_FS,
  STORAGE_GetMaxLun_FS,
  (int8_t *)STORAGE_Inquirydata_FS
};

/* Private functions ---------------------------------------------------------*/

int8_t STORAGE_Init_FS(uint8_t lun)
{
  (void)lun;
  W25Q_Init();
  return (USBD_OK);
}

int8_t STORAGE_GetCapacity_FS(uint8_t lun, uint32_t *block_num, uint16_t *block_size)
{
  (void)lun;
  *block_num  = W25Q_GetBlockCount();
  *block_size = (uint16_t)W25Q_GetBlockSize();
  return (0);
}

int8_t STORAGE_IsReady_FS(uint8_t lun)
{
  (void)lun;
  return (W25Q_IsReady() ? 0 : -1);
}

int8_t STORAGE_IsWriteProtected_FS(uint8_t lun)
{
  (void)lun;
  return (USBD_OK);
}

int8_t STORAGE_Read_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
{
  (void)lun;
  if (W25Q_Read((uint32_t)blk_addr * STORAGE_BLK_SIZ, buf, (uint32_t)blk_len * STORAGE_BLK_SIZ) != 0)
  {
    return (-1);
  }
  return (0);
}

int8_t STORAGE_Write_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
{
  (void)lun;
  if (W25Q_Write((uint32_t)blk_addr * STORAGE_BLK_SIZ, buf, (uint32_t)blk_len * STORAGE_BLK_SIZ) != 0)
  {
    return (-1);
  }
  return (0);
}

int8_t STORAGE_GetMaxLun_FS(void)
{
  return (STORAGE_LUN_NBR - 1);
}

/**
  * @}
  */
/**
  * @}
  */
