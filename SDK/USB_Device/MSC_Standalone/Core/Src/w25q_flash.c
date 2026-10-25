/**
  * @file    w25q_flash.c
  * @brief   W25Q SPI NOR flash driver for G4R_NANO (SPI2: PB13 SCK / PB15 MOSI / PB14 MISO, CS = PB12).
  *          Provides byte-addressable read / sector-erase + page-program write.
  */
#include "w25q_flash.h"
#include "spi.h"
#include "stm32g4xx_hal.h"

#define W25Q_CS_PORT      GPIOB
#define W25Q_CS_PIN       GPIO_PIN_12

#define W25Q_CMD_WRITE_ENABLE   0x06u
#define W25Q_CMD_READ_STATUS1   0x05u
#define W25Q_CMD_READ_DATA      0x03u
#define W25Q_CMD_PAGE_PROGRAM   0x02u
#define W25Q_CMD_SECTOR_ERASE   0x20u
#define W25Q_CMD_JEDEC_ID       0x9Fu

static uint32_t w25q_capacity = 8u * 1024u * 1024u;  /* default: W25Q64 (8MB) */

static void W25Q_CS_Low(void)  { HAL_GPIO_WritePin(W25Q_CS_PORT, W25Q_CS_PIN, GPIO_PIN_RESET); }
static void W25Q_CS_High(void) { HAL_GPIO_WritePin(W25Q_CS_PORT, W25Q_CS_PIN, GPIO_PIN_SET); }

static void W25Q_WriteEnable(void)
{
  uint8_t cmd = W25Q_CMD_WRITE_ENABLE;
  W25Q_CS_Low();
  HAL_SPI_Transmit(&hspi2, &cmd, 1, 1000);
  W25Q_CS_High();
}

static uint8_t W25Q_ReadStatus(void)
{
  uint8_t cmd = W25Q_CMD_READ_STATUS1;
  uint8_t status = 0u;
  W25Q_CS_Low();
  HAL_SPI_Transmit(&hspi2, &cmd, 1, 1000);
  HAL_SPI_Receive(&hspi2, &status, 1, 1000);
  W25Q_CS_High();
  return status;
}

static void W25Q_WaitBusy(void)
{
  while (W25Q_ReadStatus() & 0x01u) { }
}

bool W25Q_Init(void)
{
  GPIO_InitTypeDef gpio = {0};
  uint8_t id[3] = {0u, 0u, 0u};
  uint8_t cmd = W25Q_CMD_JEDEC_ID;

  MX_SPI2_Init();

  __HAL_RCC_GPIOB_CLK_ENABLE();
  gpio.Pin   = W25Q_CS_PIN;
  gpio.Mode  = GPIO_MODE_OUTPUT_PP;
  gpio.Pull  = GPIO_PULLUP;
  gpio.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(W25Q_CS_PORT, &gpio);
  W25Q_CS_High();

  W25Q_CS_Low();
  HAL_SPI_Transmit(&hspi2, &cmd, 1, 1000);
  HAL_SPI_Receive(&hspi2, id, 3, 1000);
  W25Q_CS_High();

  if ((id[0] == 0xEFu) || (id[0] == 0xC8u) || (id[0] == 0x1Fu))
  {
    switch (id[2])   /* capacity byte */
    {
      case 0x15u: w25q_capacity = 2u  * 1024u * 1024u; break;  /* W25Q16  */
      case 0x16u: w25q_capacity = 4u  * 1024u * 1024u; break;  /* W25Q32  */
      case 0x17u: w25q_capacity = 8u  * 1024u * 1024u; break;  /* W25Q64  */
      case 0x18u: w25q_capacity = 16u * 1024u * 1024u; break;  /* W25Q128 */
      default:    w25q_capacity = 8u  * 1024u * 1024u; break;
    }
  }

  return true;
}

uint32_t W25Q_GetCapacity(void)   { return w25q_capacity; }
uint32_t W25Q_GetBlockSize(void)  { return 512u; }
uint32_t W25Q_GetBlockCount(void) { return w25q_capacity / 512u; }

bool W25Q_IsReady(void)
{
  return (W25Q_ReadStatus() & 0x01u) == 0u;
}

int W25Q_Read(uint32_t addr, uint8_t *buf, uint32_t len)
{
  uint8_t cmd[4];
  cmd[0] = W25Q_CMD_READ_DATA;
  cmd[1] = (uint8_t)(addr >> 16);
  cmd[2] = (uint8_t)(addr >> 8);
  cmd[3] = (uint8_t)(addr);

  W25Q_CS_Low();
  if (HAL_SPI_Transmit(&hspi2, cmd, 4, 1000) != HAL_OK) { W25Q_CS_High(); return -1; }
  if (HAL_SPI_Receive(&hspi2, buf, (uint16_t)len, 1000) != HAL_OK) { W25Q_CS_High(); return -1; }
  W25Q_CS_High();
  return 0;
}

static int W25Q_EraseSector(uint32_t addr)
{
  uint8_t cmd[4];
  cmd[0] = W25Q_CMD_SECTOR_ERASE;
  cmd[1] = (uint8_t)(addr >> 16);
  cmd[2] = (uint8_t)(addr >> 8);
  cmd[3] = (uint8_t)(addr);

  W25Q_WriteEnable();
  W25Q_CS_Low();
  HAL_SPI_Transmit(&hspi2, cmd, 4, 1000);
  W25Q_CS_High();
  W25Q_WaitBusy();
  return 0;
}

static int W25Q_ProgramPage(uint32_t addr, const uint8_t *buf, uint32_t len)
{
  uint8_t cmd[4];
  cmd[0] = W25Q_CMD_PAGE_PROGRAM;
  cmd[1] = (uint8_t)(addr >> 16);
  cmd[2] = (uint8_t)(addr >> 8);
  cmd[3] = (uint8_t)(addr);

  W25Q_WriteEnable();
  W25Q_CS_Low();
  HAL_SPI_Transmit(&hspi2, cmd, 4, 1000);
  HAL_SPI_Transmit(&hspi2, (uint8_t *)buf, (uint16_t)len, 1000);
  W25Q_CS_High();
  W25Q_WaitBusy();
  return 0;
}

int W25Q_Write(uint32_t addr, const uint8_t *buf, uint32_t len)
{
  uint32_t end = addr + len;
  uint32_t sec;

  /* erase all sectors touched by the write */
  for (sec = addr & ~(W25Q_SECTOR_SIZE - 1u); sec < end; sec += W25Q_SECTOR_SIZE)
  {
    W25Q_EraseSector(sec);
  }

  /* program page by page */
  while (len > 0u)
  {
    uint32_t page_off = addr & (W25Q_PAGE_SIZE - 1u);
    uint32_t chunk = W25Q_PAGE_SIZE - page_off;
    if (chunk > len) { chunk = len; }
    W25Q_ProgramPage(addr, buf, chunk);
    addr += chunk;
    buf  += chunk;
    len  -= chunk;
  }
  return 0;
}
