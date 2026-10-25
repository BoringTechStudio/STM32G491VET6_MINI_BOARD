# STM32G491VET6 Examples

This directory contains the complete migration of the 94 examples from:

`STM32Cube_FW_G4_V1.6.3/Projects/NUCLEO-G474RE/Examples`

Each example is now a self-contained project at:

`Examples/<peripheral>/<example>/`

Every project includes its own:

- `Core/Inc` and `Core/Src` application source tree
- `Drivers` tree containing its required CMSIS, HAL, BSP, and DSP dependencies
- CubeMX `.ioc` file
- `MDK-ARM/*.uvprojx` Keil project

All Keil source and include paths resolve inside the corresponding example directory. The projects no longer rely on source files from the original STM32Cube firmware repository.

## CubeMX configuration

All migrated `.ioc` files are configured for `STM32G491VET6`, use `MDK-ARM V5.32` as the target toolchain, and generate application files under `Core/Src`. The official peripheral, clock, DMA, NVIC, and middleware settings are preserved so that each example can be opened and regenerated in STM32CubeMX independently.

## Validation

All 94 Keil projects have local file references that resolve within their own project directories. `GPIO/GPIO_Demo` was rebuilt after conversion with Keil MDK and completed with zero errors and zero warnings.

## Hardware adaptation

The MCU and LQFP64 package match the NUCLEO-G474RE examples. Examples that use only internal peripherals can be built and run without board-specific pin changes. Examples using LEDs, buttons, serial ports, two-board communication, timers, analog signals, or external clocks retain the original official pin assignments and require the corresponding signal to be connected on the custom board.

The existing board-specific examples remain at the parent level:

- `RGB`
- `RST_KEY`
- `GPIO_EXTI`
- `SPI_LCD_1.47inch`
- `SPI_LCD_2.0inch`
- `SPI_LCD_2.4inch`

Use these projects as the reference for the board's RGB pins (`PC0`, `PC1`, `PC2`), USART1 (`PA9`, `PA10`), 24 MHz HSE, and PG10 key wiring when adapting an official example to the custom board.

## Example count

The migration contains 94 independent examples in 25 peripheral categories: ADC, COMP, CORDIC, Cortex, CRC, DAC, DMA, FLASH, FMAC, GPIO, HAL, HRTIM, I2C, IWDG, LPTIM, OPAMP, PWR, RCC, RNG, RTC, SPI, TIM, UART, USART, and WWDG.

`../tools/MakeExamplesStandalone.ps1` is the idempotent migration utility used to localize the project trees. It is only needed when repeating the migration from the STM32Cube firmware package; the completed example projects do not require that package for their source files.