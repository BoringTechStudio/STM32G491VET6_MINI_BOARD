/**
  * @file    w25q_flash.h
  * @brief   W25Q SPI NOR flash driver (SPI2, CS = PB12) for G4R_NANO MSC storage.
  */
#ifndef __W25Q_FLASH_H
#define __W25Q_FLASH_H

#include <stdint.h>
#include <stdbool.h>

#define W25Q_PAGE_SIZE     256u
#define W25Q_SECTOR_SIZE   4096u

bool     W25Q_Init(void);
uint32_t W25Q_GetCapacity(void);   /* bytes */
uint32_t W25Q_GetBlockSize(void);  /* 512 */
uint32_t W25Q_GetBlockCount(void); /* capacity / 512 */
bool     W25Q_IsReady(void);
int      W25Q_Read(uint32_t addr, uint8_t *buf, uint32_t len);
int      W25Q_Write(uint32_t addr, const uint8_t *buf, uint32_t len);

#endif /* __W25Q_FLASH_H */
