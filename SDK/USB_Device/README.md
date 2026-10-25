# USB Device Applications (STM32G491VET6 / G4V_MINI)

USB Device applications ported from `STM32Cube_FW_G4_V1.6.3/Projects/STM32G474E-EVAL/Applications/USB_Device`
to the G4V_MINI board. Each project is standalone (AC6 V6.21, Keil MDK, local `Drivers` + `Middlewares`).

USB pins: DM = PA11, DP = PA12 (fixed on STM32G4).

## Applications

| App | USB class | Notes |
| --- | --- | --- |
| CDC_Standalone | CDC (virtual COM) | USB-to-UART bridge (USART1) |
| HID_Standalone | HID (mouse) | Remote-wakeup via BUTTON_RST |
| DFU_Standalone | DFU (firmware upgrade) | Enter DFU via BUTTON_RST |
| MSC_Standalone | MSC (mass storage) | W25Q SPI flash as storage (SPI2, CS=PB12) |

## LED / button mapping (E-EVAL -> this board)

| E-EVAL | This board |
| --- | --- |
| LED3 (red) | LED_RED (PC0) |
| BUTTON_USER / KEY / KEY1 (PC13) | BUTTON_RST (PG10) |

All ported projects compile with 0 errors / 0 warnings on AC6.
