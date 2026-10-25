# STM32G491VET6 Directory Guide

English | [简体中文](./README.md)

> **Board**: G4V_MINI
> **MCU**: STM32G491VET6 (LQFP100 package)

## Board Introduction

### MCU
- STM32G491VET6, Cortex-M4, 170 MHz core clock
- 512 KB Flash, 112 KB RAM

### Clock
- 24 MHz HSE crystal ×1, 32.768 kHz LSE crystal ×1

### Power
- Switching power supply ×1 (5.5 V max input, 1 A max output)

### Storage (optional)
- W25Q64 external QSPI Flash ×1 (8 MB)

### Buttons & LEDs
- Reset button (reusable) ×1, BOOT button (reusable) ×1
- Power LED ×1, user RGB LED ×1

### Interfaces
- USB Type-C connector ×1 (directly connected to PA11/PA12)
- LCD header ×1 (SPI half-duplex driven, color IPS TFT)
- RTC backup battery header ×1 (fits ML621-TZ1 rechargeable battery)
- 2.54 mm pitch 2×20-pin headers ×2 (all IOs broken out)
- 2.54 mm pitch 2×4 header ×1 (SWD + USART1 dedicated breakout)

### Dimensions & Process
- 5.18 cm × 3.60 cm
- JLC 4-layer board, ENIG finish, lead-free SMT

## 1. Board-Level Pin Map (HDK/G4V_MINI-PinMap.md)

| Function | Pin | Notes |
|------|------|------|
| RGB LED - Red | **PC0** | LED_RED |
| RGB LED - Green | **PC1** | LED_GREEN |
| RGB LED - Blue | **PC2** | LED_BLUE |
| Reset key (RST_KEY) | **PG10** | EXTI10 |
| BOOT0 key (BOOT0_KEY) | **PB8** | EXTI8 |
| UART1 - TX | **PA9** | USART1, AF7 |
| UART1 - RX | **PA10** | USART1, AF7 |
| USB - DM / DP | PA11 / PA12 | — |
| SPI_LCD | PB3/4/5 + PD3/6 + PB6 | SCL/DC/SDA + PWR/RST + CS |
| SPI_FLASH | PB13/14/15 + PB12 | CLK/MOSI/MISO + CS |
| QSPI_FLASH | PA3/PA2/PB1/PF9/PA7/PA6 | CLK/CS/D0/D1/D2/D3 |

## 2. Top-Level Directory Structure

| Path | Description |
|------|------|
| `HDK/` | Hardware Development Kit |
| `HDK/G4V_MINI-Schematic.pdf` | Board schematic |
| `HDK/G4V_MINI-PinMap.md` | Board-level pin map |
| `HDK/Altium-Designer-Libraries/G4V_MINI.PcbLib` | Altium Designer PCB footprint library |
| `HDK/Altium-Designer-Libraries/G4V_MINI.SchLib` | Altium Designer schematic symbol library |
| `HDK/Mechanical/` | Mechanical dimension drawings |
| `SDK/Examples/` | Official example library (adapted to G4V_MINI, 88 projects) |
| `SDK/FreeRTOS/` | Standalone projects: FreeRTOS applications (9, ported from STM32G474E-EVAL) |
| `SDK/USB_Device/` | Standalone projects: USB Device applications (CDC/HID/DFU/MSC, 4 in total, ported from STM32G474E-EVAL) |
| `SDK/RGB/` | Standalone project: RGB LED control |
| `SDK/RST_KEY/` | Standalone project: reset key test |
| `SDK/SPI_LCD_1.47inch/` | Standalone project: 1.47" LCD |
| `SDK/SPI_LCD_2.0inch/` | Standalone project: 2.0" LCD |
| `SDK/SPI_LCD_2.4inch/` | Standalone project: 2.4" LCD |
| `SDK/SPI_FLASH/` | Standalone project: SPI Flash (W25Q) |
| `SDK/QSPI_FLASH/` | Standalone project: QSPI Flash (W25Q) |
| `SDK/keilclean.bat` | Keil cleanup script |
| `STM32_CubeMX_Keil_快速上手.md` | CubeMX/Keil quick-start guide (Chinese) |
| `README.md` | This document (Simplified Chinese) |
| `README_EN.md` | English version of this document |

## 3. Examples Library (88 in total)

| Category | Example |
|------|----------|
| ADC | ADC_GainCompensation |
| ADC | ADC_OffsetCompensation |
| COMP | COMP_CompareGpioVsDacInt_OutputGpio |
| COMP | COMP_OutputBlanking |
| CORDIC | CORDIC_Sin_DMA |
| CORDIC | CORDIC_SinCos_DMA_Perf |
| Cortex | CORTEXM_ModePrivilege |
| Cortex | CORTEXM_MPU |
| Cortex | CORTEXM_ProcessStack |
| Cortex | CORTEXM_SysTick |
| CRC | CRC_Bytes_Stream_7bit_CRC |
| CRC | CRC_Data_Reversing_16bit_CRC |
| CRC | CRC_Example |
| CRC | CRC_UserDefinedPolynomial |
| DAC | DAC_SignalsGeneration2 |
| DMA | DMA_FLASHToRAM |
| DMA | DMA_MUXSYNC |
| FLASH | FLASH_EraseProgram |
| FLASH | FLASH_WriteProtection |
| FMAC | FMAC_Adaptive_FIR_AN5305 |
| FMAC | FMAC_FIR_DMAToIT |
| FMAC | FMAC_FIR_PollingToIT |
| FMAC | FMAC_IIR_ITToPolling |
| FMAC | FMAC_IIR_PollingToDMA |
| GPIO | GPIO_Demo |
| GPIO | GPIO_EXTI |
| GPIO | GPIO_IOToggle |
| HAL | HAL_TimeBase_TIM |
| I2C | I2C_TwoBoards_AdvComIT |
| I2C | I2C_TwoBoards_ComDMA |
| I2C | I2C_TwoBoards_ComIT |
| I2C | I2C_TwoBoards_ComPolling |
| I2C | I2C_TwoBoards_RestartComIT |
| I2C | I2C_WakeUpFromStop |
| IWDG | IWDG_Reset |
| IWDG | IWDG_WindowMode |
| LPTIM | LPTIM_PulseCounter |
| LPTIM | LPTIM_PWM_LSE |
| LPTIM | LPTIM_PWMExternalClock |
| LPTIM | LPTIM_Timeout |
| OPAMP | OPAMP_PGA |
| PWR | PWR_CurrentConsumption |
| PWR | PWR_LPRUN |
| PWR | PWR_LPSLEEP |
| PWR | PWR_PVD |
| PWR | PWR_SHUTDOWN |
| PWR | PWR_STANDBY_RTC |
| PWR | PWR_STOP0 |
| PWR | PWR_STOP0_RTC |
| PWR | PWR_STOP1_RTC |
| RCC | RCC_ClockConfig |
| RCC | RCC_CRS_Synchronization_IT |
| RCC | RCC_CRS_Synchronization_Polling |
| RNG | RNG_MultiRNG |
| RNG | RNG_MultiRNG_IT |
| RTC | RTC_Alarm |
| RTC | RTC_Calendar |
| RTC | RTC_LSI |
| SPI | SPI_FullDuplex_ComDMA_Master |
| SPI | SPI_FullDuplex_ComDMA_Slave |
| SPI | SPI_FullDuplex_ComIT_Master |
| SPI | SPI_FullDuplex_ComIT_Slave |
| SPI | SPI_FullDuplex_ComPolling_Master |
| SPI | SPI_FullDuplex_ComPolling_Slave |
| TIM | TIM_CascadeSynchro |
| TIM | TIM_Combined |
| TIM | TIM_ComplementarySignals |
| TIM | TIM_Dithering |
| TIM | TIM_DMA |
| TIM | TIM_DMABurst |
| TIM | TIM_Encoder |
| TIM | TIM_EncoderIndex_PulseOnCompare |
| TIM | TIM_InputCapture |
| TIM | TIM_OCToggle |
| TIM | TIM_PWMInput |
| TIM | TIM_PWMOutput |
| UART | LPUART_TwoBoards_ComIT |
| UART | LPUART_WakeUpFromStop |
| UART | UART_HyperTerminal_DMA |
| UART | UART_HyperTerminal_IT |
| UART | UART_Printf |
| UART | UART_ReceptionToIdle_CircularDMA |
| UART | UART_TwoBoards_ComDMA |
| UART | UART_TwoBoards_ComIT |
| UART | UART_TwoBoards_ComPolling |
| UART | UART_WakeUpFromStopUsingFIFO |
| USART | USART_SlaveMode |
| WWDG | WWDG_Example |

> Category stats: ADC(2), COMP(2), CORDIC(2), Cortex(4), CRC(4), DAC(1), DMA(2), FLASH(2), FMAC(5), GPIO(3), HAL(1), I2C(6), IWDG(2), LPTIM(4), OPAMP(1), PWR(9), RCC(3), RNG(2), RTC(3), SPI(6), TIM(12), UART(10), USART(1), WWDG(1)

## 4. Standalone Projects (9 directories)

| Project | Description | README |
|------|------|:---:|
| `SDK/RGB/` | RGB LED (PC0/PC1/PC2) control | ✅ |
| `SDK/RST_KEY/` | Reset key (PG10) test | ✅ |
| `SDK/SPI_FLASH/` | SPI Flash (W25Q) read/write | ✅ |
| `SDK/QSPI_FLASH/` | QSPI Flash (W25Q) read/write | ✅ |
| `SDK/SPI_LCD_1.47inch/` | 1.47" SPI LCD | ✅ |
| `SDK/SPI_LCD_2.0inch/` | 2.0" SPI LCD | ✅ |
| `SDK/SPI_LCD_2.4inch/` | 2.4" SPI LCD | ✅ |
| `SDK/FreeRTOS/` | FreeRTOS applications (9) | ✅ |
| `SDK/USB_Device/` | USB Device applications (4: CDC/HID/DFU/MSC) | ✅ |

> Total projects: Examples **88** + standalone **7** + FreeRTOS **9** + USB_Device **4** = **108**
