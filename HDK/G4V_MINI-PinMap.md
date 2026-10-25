# STM32G91VET6 板级引脚映射 / Board Pin Map（PinMap）

> 本文件定义 G4V_MINI 板级引脚与功能映射，供查阅与开发参考。
> This file defines the G4V_MINI board pin / function mapping for reference and development.

## RGB LED 三色灯 / RGB LED

| 功能 Function | 引脚 Pin | 说明 Description |
|------|------|------|
| RED 红 | **PC0** | 红色 LED / Red LED |
| GREEN 绿 | **PC1** | 绿色 LED / Green LED |
| BLUE 蓝 | **PC2** | 蓝色 LED / Blue LED |

## 按键 / Key

| 功能 Function | 引脚 Pin | 说明 Description |
|------|------|------|
| RST_KEY | **PG10** | 复位按键，EXTI10 / Reset key, EXTI10 |
| BOOT0_KEY | **PB8** | BOOT0 按键，EXTI8 / BOOT0 key, EXTI8 |

## 串口 USART1 / UART USART1

| 功能 Function | 引脚 Pin | 说明 Description |
|------|------|------|
| TX | **PA9** | USART1_TX，AF7 |
| RX | **PA10** | USART1_RX，AF7 |

## SPI LCD 屏 / SPI LCD

| 功能 Function | 引脚 Pin | 说明 Description |
|------|------|------|
| LCD_PWR | **PD3** | 电源 / Power |
| LCD_RST | **PD6** | 复位 / Reset |
| LCD_DC | **PB4** | 数据/命令 / Data / Command |
| LCD_SDA | **PB5** | 数据 / Data (MOSI) |
| LCD_SCL | **PB3** | 时钟 / Clock |
| LCD_CS | **PB6** | 片选 / Chip select |

## USB

| 功能 Function | 引脚 Pin | 说明 Description |
|------|------|------|
| DM | **PA11** | USB DM |
| DP | **PA12** | USB DP |

## QSPI Flash 闪存 / QSPI Flash

| 功能 Function | 引脚 Pin | 说明 Description |
|------|------|------|
| CLK | **PA3** | 时钟 / Clock |
| CS | **PA2** | 片选 / Chip select |
| D0 | **PB1** | 数据 0 / Data 0 |
| D1 | **PF9** | 数据 1 / Data 1 |
| D2 | **PA7** | 数据 2 / Data 2 |
| D3 | **PA6** | 数据 3 / Data 3 |
