# RGB

Independent STM32CubeMX / Keil MDK example for STM32G491VET6 (G4V_MINI board, LQFP100).

## Behavior

Prints hello world! over USART1, echoes received bytes, and toggles the RGB LEDs together every 500 ms.

## Connections

| Signal | Pin | Configuration |
| --- | --- | --- |
| Red LED | PC0 | Push-pull output, active low |
| Green LED | PC1 | Push-pull output, active low |
| Blue LED | PC2 | Push-pull output, active low |
| USART1 TX | PA9 | 115200 baud serial output |
| USART1 RX | PA10 | 115200 baud serial input |

## Build and use

Open the .uvprojx in MDK-ARM with Keil MDK, build, and program the target. The STM32G491VET6.ioc file contains the matching CubeMX configuration.