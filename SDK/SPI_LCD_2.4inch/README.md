# SPI_LCD_2.4inch

Independent STM32CubeMX / Keil MDK example for STM32G491VET6 (G4V_MINI board, LQFP100). Drives a 2.4-inch ST7789 SPI LCD.

## Behavior

Initializes the LCD, shows boot text and a running tick counter, and toggles the RGB LEDs periodically.

## Connections

| Signal | Pin | Configuration |
| --- | --- | --- |
| LCD_SCL | PB3 | SPI1_SCK |
| LCD_SDA | PB5 | SPI1_MOSI |
| LCD_DC | PB4 | Command/data select |
| LCD_RST | PD6 | Reset |
| LCD_PWR | PD3 | Backlight / power |
| LCD_CS | PB6 | Software chip select |
| Red / Green / Blue LED | PC0 / PC1 / PC2 | Push-pull outputs |
| USART1 TX / RX | PA9 / PA10 | 115200 baud serial |

## Build and use

Open the .uvprojx in MDK-ARM with Keil MDK, build, and program the target. The STM32G491VET6.ioc file contains the matching CubeMX configuration.