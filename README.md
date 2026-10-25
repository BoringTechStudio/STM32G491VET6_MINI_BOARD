# STM32G491VET6 目录说明

简体中文 | [English](./README_EN.md)

> **开发板**：G4V_MINI
> **主控**：STM32G491VET6（LQFP100 封装）

## 板卡介绍

### 主控
- STM32G491VET6，Cortex-M4，170MHz 主频
- 512K Bytes Flash，112K Bytes RAM

### 时钟
- 24MHz HSE 晶振 ×1，32.768KHz LSE 晶振 ×1

### 电源
- 开关电源 ×1（5.5V 最大输入电压，1A 最大输出电流）

### 存储（选配）
- W25Q64 片外 QSPI Flash ×1（8M Bytes）

### 按键 & LED
- 复位按键（可复用）×1，BOOT 按键（可复用）×1
- 电源 LED ×1，用户 RGB LED ×1

### 接口
- USB TYPE-C 接口 ×1（直连芯片 PA11 PA12）
- LCD 接口 ×1（SPI 半双工驱动，彩色 IPS TFT）
- RTC 后备电池接口 ×1（适配 ML621-TZ1 可充电式电池）
- 2.54mm 间距 2×20Pin 排针 ×2（IO 全引出）
- 2.54mm 间距 2×4 排针 ×1（SWD 接口 + 串口1 专门引出）

### 尺寸 & 工艺
- 长 5.18cm，宽 3.60cm
- JLC 4 层板，沉金工艺，无铅 SMT

## 一、板级引脚映射（HDK/G4V_MINI-PinMap.md）

| 功能 | 引脚 | 说明 |
|------|------|------|
| RGB_LED - 红 (RED) | **PC0** | LED_RED |
| RGB_LED - 绿 (GREEN) | **PC1** | LED_GREEN |
| RGB_LED - 蓝 (BLUE) | **PC2** | LED_BLUE |
| 复位按键 (RST_KEY) | **PG10** | EXTI10 |
| BOOT0 按键 (BOOT0_KEY) | **PB8** | EXTI8 |
| UART1 - TX | **PA9** | USART1, AF7 |
| UART1 - RX | **PA10** | USART1, AF7 |
| USB - DM / DP | PA11 / PA12 | — |
| SPI_LCD | PB3/4/5 + PD3/6 + PB6 | SCL/DC/SDA + PWR/RST + CS |
| SPI_FLASH | PB13/14/15 + PB12 | CLK/MOSI/MISO + CS |
| QSPI_FLASH | PA3/PA2/PB1/PF9/PA7/PA6 | CLK/CS/D0/D1/D2/D3 |

## 二、顶层目录结构

| 路径 | 说明 |
|------|------|
| `HDK/` | 硬件开发套件（Hardware Development Kit） |
| `HDK/G4V_MINI-Schematic.pdf` | 核心板原理图 |
| `HDK/G4V_MINI-PinMap.md` | 板级引脚映射 |
| `HDK/Altium-Designer-Libraries/G4V_MINI.PcbLib` | Altium Designer PCB 封装库 |
| `HDK/Altium-Designer-Libraries/G4V_MINI.SchLib` | Altium Designer 原理图符号库 |
| `HDK/Mechanical/` | 机械尺寸图 |
| `SDK/Examples/` | 官方例程库（已适配 G4V_MINI，88 个工程） |
| `SDK/FreeRTOS/` | 独立工程：FreeRTOS 应用（9 个，从 STM32G474E-EVAL 移植） |
| `SDK/USB_Device/` | 独立工程：USB Device 应用（CDC/HID/DFU/MSC 共 4 个，从 STM32G474E-EVAL 移植） |
| `SDK/RGB/` | 独立工程：RGB LED 控制 |
| `SDK/RST_KEY/` | 独立工程：复位按键测试 |
| `SDK/SPI_LCD_1.47inch/` | 独立工程：1.47 寸 LCD |
| `SDK/SPI_LCD_2.0inch/` | 独立工程：2.0 寸 LCD |
| `SDK/SPI_LCD_2.4inch/` | 独立工程：2.4 寸 LCD |
| `SDK/SPI_FLASH/` | 独立工程：SPI Flash（W25Q） |
| `SDK/QSPI_FLASH/` | 独立工程：QSPI Flash（W25Q） |
| `SDK/keilclean.bat` | Keil 清理脚本 |
| `STM32_CubeMX_Keil_快速上手.md` | CubeMX/Keil 快速上手文档 |
| `README.md` | 本说明文档（简体中文） |
| `README_EN.md` | 英文说明文档 |

## 三、Examples 例程库（共 88 个）

| 分类 | 例程名称 |
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

> 分类统计：ADC(2)、COMP(2)、CORDIC(2)、Cortex(4)、CRC(4)、DAC(1)、DMA(2)、FLASH(2)、FMAC(5)、GPIO(3)、HAL(1)、I2C(6)、IWDG(2)、LPTIM(4)、OPAMP(1)、PWR(9)、RCC(3)、RNG(2)、RTC(3)、SPI(6)、TIM(12)、UART(10)、USART(1)、WWDG(1)

## 四、独立工程（共 9 个目录）

| 工程 | 说明 | README |
|------|------|:---:|
| `SDK/RGB/` | RGB LED（PC0/PC1/PC2）控制 | ✅ |
| `SDK/RST_KEY/` | 复位按键（PG10）测试 | ✅ |
| `SDK/SPI_FLASH/` | SPI Flash（W25Q）读写 | ✅ |
| `SDK/QSPI_FLASH/` | QSPI Flash（W25Q）读写 | ✅ |
| `SDK/SPI_LCD_1.47inch/` | 1.47 寸 SPI LCD | ✅ |
| `SDK/SPI_LCD_2.0inch/` | 2.0 寸 SPI LCD | ✅ |
| `SDK/SPI_LCD_2.4inch/` | 2.4 寸 SPI LCD | ✅ |
| `SDK/FreeRTOS/` | FreeRTOS 应用（9 个） | ✅ |
| `SDK/USB_Device/` | USB Device 应用（4 个：CDC/HID/DFU/MSC） | ✅ |

> 工程总数：Examples 例程库 **88** 个 + 独立工程 **7** 个 + FreeRTOS **9** 个 + USB_Device **4** 个 = **108** 个
