# QSPI_FLASH

Independent STM32CubeMX / Keil MDK example for STM32G491VET6 (G4V_MINI board, LQFP100). Reads/writes a W25Q flash over the QUADSPI (quad-SPI) interface.

## Behavior

Reads the JEDEC ID, erases sector 0, writes 256 bytes, and reads them back for verification. On success the green LED turns on; on failure the red LED turns on. The RGB LEDs also blink periodically.

## Connections

| Signal | Pin | Configuration |
| --- | --- | --- |
| QSPI_CLK | PA3 | QUADSPI_CLK (AF10) |
| QSPI_NCS | PA2 | QUADSPI_BK1_NCS (AF10) |
| D0 / IO0 | PB1 | QUADSPI_BK1_IO0 (AF10) |
| D1 / IO1 | PF9 | QUADSPI_BK1_IO1 (AF10) |
| D2 / IO2 | PA7 | QUADSPI_BK1_IO2 (AF10) |
| D3 / IO3 | PA6 | QUADSPI_BK1_IO3 (AF10) |
| Red / Green / Blue LED | PC0 / PC1 / PC2 | Push-pull outputs |
| USART1 TX / RX | PA9 / PA10 | 115200 baud serial |

## Build and use

Open the .uvprojx in MDK-ARM with Keil MDK, build, and program the target. The STM32G491VET6.ioc file contains the matching CubeMX configuration.