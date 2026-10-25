# SPI_FLASH

Independent STM32CubeMX / Keil MDK example for STM32G491VET6 (G4V_MINI board, LQFP100). Reads/writes a W25Q serial flash over SPI2 using the SFUD driver.

## Behavior

sfud_init() detects the flash, then erases a sector, writes 256 bytes, and reads them back for verification. On success the green LED turns on; on failure the red LED turns on. The RGB LEDs also blink periodically.

## Connections

| Signal | Pin | Configuration |
| --- | --- | --- |
| SPI2_CLK | PB13 | SPI2_SCK |
| SPI2_CS | PB12 | Software chip select (GPIO) |
| SPI2_MOSI | PB15 | SPI2_MOSI (PinMap.md labels it PB14, flash-side view) |
| SPI2_MISO | PB14 | SPI2_MISO (PinMap.md labels it PB15, flash-side view) |
| KEY | PC13 | Pull-up input (unused in this demo) |
| Red / Green / Blue LED | PC0 / PC1 / PC2 | Push-pull outputs |
| USART1 TX / RX | PA9 / PA10 | 115200 baud serial |

## Build and use

Open the .uvprojx in MDK-ARM with Keil MDK, build, and program the target. The STM32G491VET6.ioc file contains the matching CubeMX configuration.