/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    quadspi.c
  * @brief   This file provides code for the configuration of the QUADSPI instances.
  *
  * QSPI pins (from PinMap.md): CLK=PA3, CS=PA2, D0/IO0=PB1, D1/IO1=PF9, D2/IO2=PA7, D3/IO3=PA6  (AF10)
  ******************************************************************************
  */
/* USER CODE END Header */
#include "quadspi.h"

QSPI_HandleTypeDef hqspi;

/* QUADSPI init function */
void MX_QUADSPI_Init(void)
{
  hqspi.Instance = QUADSPI;
  hqspi.Init.ClockPrescaler = 1;                              /* QSPI clock = 170MHz / 2 = 85MHz */
  hqspi.Init.FifoThreshold = 32;
  hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
  hqspi.Init.FlashSize = 23;                                  /* 2^(23+1) = 16MB */
  hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_2_CYCLE;
  hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
  hqspi.Init.FlashID = QSPI_FLASH_ID_1;
  hqspi.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
  if (HAL_QSPI_Init(&hqspi) != HAL_OK)
  {
    Error_Handler();
  }
}

void HAL_QSPI_MspInit(QSPI_HandleTypeDef* qspiHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(qspiHandle->Instance==QUADSPI)
  {
    /* QUADSPI clock enable */
    __HAL_RCC_QSPI_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();

    /**QUADSPI GPIO Configuration
    PA2     ------> QUADSPI_BK1_NCS
    PA3     ------> QUADSPI_CLK
    PA6     ------> QUADSPI_BK1_IO3
    PA7     ------> QUADSPI_BK1_IO2
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /**PB1     ------> QUADSPI_BK1_IO0 */
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /**PF9     ------> QUADSPI_BK1_IO1 */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
  }
}

void HAL_QSPI_MspDeInit(QSPI_HandleTypeDef* qspiHandle)
{
  if(qspiHandle->Instance==QUADSPI)
  {
    __HAL_RCC_QSPI_CLK_DISABLE();

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_6|GPIO_PIN_7);
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_1);
    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_9);
  }
}
