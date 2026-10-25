# FreeRTOS Applications (STM32G491VET6 / G4V_MINI)

9 FreeRTOS applications ported from `STM32Cube_FW_G4_V1.6.3/Projects/STM32G474E-EVAL/Applications/FreeRTOS`
to the G4V_MINI board. Each project is standalone (AC6 V6.21, Keil MDK, local `Drivers` + `Middlewares`).

## Applications

FreeRTOS_ThreadCreation, FreeRTOS_Mail, FreeRTOS_Queues, FreeRTOS_Semaphore,
FreeRTOS_SemaphoreFromISR, FreeRTOS_Signal, FreeRTOS_SignalFromISR,
FreeRTOS_Mutexes, FreeRTOS_Timers.

## LED / button mapping (E-EVAL -> this board)

| E-EVAL | This board |
| --- | --- |
| LED1 (green) | LED_GREEN (PC1) |
| LED2 (MFX) | LED_BLUE (PC2) |
| LED3 (red) | LED_RED (PC0) |
| LED4 (MFX) | LED_RED (PC0) |
| BUTTON_USER (PC13) | BUTTON_RST (PG10) |

RGB pins are selected automatically by the board macro `G4V_MINI` in the boring BSP.

All 9 projects compile with 0 errors / 0 warnings on AC6.
