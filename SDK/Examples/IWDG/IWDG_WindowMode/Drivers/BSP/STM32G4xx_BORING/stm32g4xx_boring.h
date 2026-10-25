/**
  ******************************************************************************
  * @file    stm32g4xx_boring.h
  * @author  MCD Application Team
  * @brief   This file contains definitions for:
  *          - LEDs and push-button available on G4R_NANO / G4V_MINI / G4C_NANO boards
  *            from boring_tech_studio
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32G4XX_BORING_H
#define STM32G4XX_BORING_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_boring_errno.h"
#include "stm32g4xx_boring_conf.h"

#if (USE_BSP_COM_FEATURE > 0)
  #if (USE_COM_LOG > 0)
    #ifndef __GNUC__
      #include "stdio.h"
    #endif
  #endif
#endif

#if !defined (G4R_NANO) && !defined (G4V_MINI) && !defined (G4C_NANO)
#error "Board not defined: define G4R_NANO (G474RET6/LQFP64), G4V_MINI (G474VET6/LQFP100) or G4C_NANO (G431CBT6/LQFP48)"
#endif

/* Supported boards, selected by the project preprocessor define:
     - G4R_NANO : G474RET6 (LQFP64)
     - G4V_MINI : G474VET6 (LQFP100)
     - G4C_NANO : G431CBT6 (LQFP48)
   Each board defines its own low-level IO block below. RGB LED / keys / USART1
   pins are kept in separate per-board blocks so they can diverge independently. */

/** @addtogroup BSP
  * @{
  */

/** @defgroup STM32G4XX_BORING STM32G4XX_BORING
  * @{
  */

/** @defgroup STM32G4XX_BORING_LOW_LEVEL LOW LEVEL
  * @{
  */

/** @defgroup STM32G4XX_BORING_LOW_LEVEL_Exported_Types LOW LEVEL Exported Types
  * @{
  */
typedef enum
{
  LED_RED = 0U,
  LED_GREEN = 1U,
  LED_BLUE = 2U,
  LEDn
}Led_TypeDef;

#if defined (G4R_NANO) || defined (G4V_MINI) || defined (G4C_NANO)
typedef enum
{
  BUTTON_RST = 0U,
  BUTTON_BOOT0 = 1U,
  BUTTONn
}Button_TypeDef;

typedef enum
{
  BUTTON_MODE_GPIO = 0U,
  BUTTON_MODE_EXTI = 1U
}ButtonMode_TypeDef;
#endif /* (G4R_NANO) || (G4V_MINI) || (G4C_NANO) */

#if (USE_BSP_COM_FEATURE > 0)
typedef enum
{
  COM1 = 0U,
  COMn
}COM_TypeDef;

typedef enum
{
  COM_STOPBITS_1     =   UART_STOPBITS_1,
  COM_STOPBITS_2     =   UART_STOPBITS_2,
}COM_StopBitsTypeDef;

typedef enum
{
  COM_PARITY_NONE     =  UART_PARITY_NONE,
  COM_PARITY_EVEN     =  UART_PARITY_EVEN,
  COM_PARITY_ODD      =  UART_PARITY_ODD,
}COM_ParityTypeDef;

typedef enum
{
  COM_HWCONTROL_NONE    =  UART_HWCONTROL_NONE,
  COM_HWCONTROL_RTS     =  UART_HWCONTROL_RTS,
  COM_HWCONTROL_CTS     =  UART_HWCONTROL_CTS,
  COM_HWCONTROL_RTS_CTS =  UART_HWCONTROL_RTS_CTS,
}COM_HwFlowCtlTypeDef;

typedef enum
{
  COM_WORDLENGTH_7B = UART_WORDLENGTH_7B,
  COM_WORDLENGTH_8B = UART_WORDLENGTH_8B,
  COM_WORDLENGTH_9B = UART_WORDLENGTH_9B,
}COM_WordLengthTypeDef;

typedef struct
{
  uint32_t              BaudRate;
  COM_WordLengthTypeDef WordLength;
  COM_StopBitsTypeDef   StopBits;
  COM_ParityTypeDef     Parity;
  COM_HwFlowCtlTypeDef  HwFlowCtl;
}COM_InitTypeDef;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
typedef struct
{
  pUART_CallbackTypeDef  pMspInitCb;
  pUART_CallbackTypeDef  pMspDeInitCb;
}BSP_COM_Cb_t;
#endif /* (USE_HAL_UART_REGISTER_CALLBACKS == 1) */
#endif /* (USE_BSP_COM_FEATURE > 0) */

/**
  * @}
  */

/** @defgroup STM32G4XX_BORING_LOW_LEVEL_Exported_Constants LOW LEVEL Exported Constants
  * @{
  */

/**
  * @brief STM32G4XX_BORING BSP Driver version number
  */
#define STM32G4XX_BORING_BSP_VERSION_MAIN   0x01U /*!< [31:24] main version */
#define STM32G4XX_BORING_BSP_VERSION_SUB1   0x00U /*!< [23:16] sub1 version */
#define STM32G4XX_BORING_BSP_VERSION_SUB2   0x06U /*!< [15:8]  sub2 version */
#define STM32G4XX_BORING_BSP_VERSION_RC     0x00U /*!< [7:0]  release candidate */
#define STM32G4XX_BORING_BSP_VERSION        ((STM32G4XX_BORING_BSP_VERSION_MAIN << 24)\
                                            |(STM32G4XX_BORING_BSP_VERSION_SUB1 << 16)\
                                            |(STM32G4XX_BORING_BSP_VERSION_SUB2 << 8 )\
                                            |(STM32G4XX_BORING_BSP_VERSION_RC))

/**
  * @brief Define for STM32G4XX_BORING board
  */
#if !defined (USE_STM32G4XX_BORING)
 #define USE_STM32G4XX_BORING
#endif

#if defined (G4V_MINI)
#define STM32G4XX_BORING_BSP_BOARD_NAME  "G4V_MINI"
#elif defined (G4C_NANO)
#define STM32G4XX_BORING_BSP_BOARD_NAME  "G4C_NANO"
#else
#define STM32G4XX_BORING_BSP_BOARD_NAME  "G4R_NANO"
#endif
#define STM32G4XX_BORING_BSP_BOARD_ID    "BORING_TECH_STUDIO"

/** @defgroup STM32G4XX_BORING_LOW_LEVEL_LED LOW LEVEL LED
  * @{
  */
#if defined (G4R_NANO)
#define LED_RED_PIN                           GPIO_PIN_0
#define LED_RED_GPIO_PORT                     GPIOC
#define LED_RED_GPIO_CLK_ENABLE()             __HAL_RCC_GPIOC_CLK_ENABLE()
#define LED_RED_GPIO_CLK_DISABLE()            __HAL_RCC_GPIOC_CLK_DISABLE()

#define LED_GREEN_PIN                         GPIO_PIN_1
#define LED_GREEN_GPIO_PORT                   GPIOC
#define LED_GREEN_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOC_CLK_ENABLE()
#define LED_GREEN_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOC_CLK_DISABLE()

#define LED_BLUE_PIN                          GPIO_PIN_2
#define LED_BLUE_GPIO_PORT                    GPIOC
#define LED_BLUE_GPIO_CLK_ENABLE()            __HAL_RCC_GPIOC_CLK_ENABLE()
#define LED_BLUE_GPIO_CLK_DISABLE()           __HAL_RCC_GPIOC_CLK_DISABLE()
#elif defined (G4V_MINI)
#define LED_RED_PIN                           GPIO_PIN_0
#define LED_RED_GPIO_PORT                     GPIOC
#define LED_RED_GPIO_CLK_ENABLE()             __HAL_RCC_GPIOC_CLK_ENABLE()
#define LED_RED_GPIO_CLK_DISABLE()            __HAL_RCC_GPIOC_CLK_DISABLE()

#define LED_GREEN_PIN                         GPIO_PIN_1
#define LED_GREEN_GPIO_PORT                   GPIOC
#define LED_GREEN_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOC_CLK_ENABLE()
#define LED_GREEN_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOC_CLK_DISABLE()

#define LED_BLUE_PIN                          GPIO_PIN_2
#define LED_BLUE_GPIO_PORT                    GPIOC
#define LED_BLUE_GPIO_CLK_ENABLE()            __HAL_RCC_GPIOC_CLK_ENABLE()
#define LED_BLUE_GPIO_CLK_DISABLE()           __HAL_RCC_GPIOC_CLK_DISABLE()
#elif defined (G4C_NANO)
#define LED_RED_PIN                           GPIO_PIN_0
#define LED_RED_GPIO_PORT                     GPIOA
#define LED_RED_GPIO_CLK_ENABLE()             __HAL_RCC_GPIOA_CLK_ENABLE()
#define LED_RED_GPIO_CLK_DISABLE()            __HAL_RCC_GPIOA_CLK_DISABLE()

#define LED_GREEN_PIN                         GPIO_PIN_1
#define LED_GREEN_GPIO_PORT                   GPIOA
#define LED_GREEN_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOA_CLK_ENABLE()
#define LED_GREEN_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOA_CLK_DISABLE()

#define LED_BLUE_PIN                          GPIO_PIN_2
#define LED_BLUE_GPIO_PORT                    GPIOA
#define LED_BLUE_GPIO_CLK_ENABLE()            __HAL_RCC_GPIOA_CLK_ENABLE()
#define LED_BLUE_GPIO_CLK_DISABLE()           __HAL_RCC_GPIOA_CLK_DISABLE()
#endif /* G4R_NANO / G4V_MINI / G4C_NANO */

/**
  * @}
  */

/** @defgroup STM32G4XX_BORING_LOW_LEVEL_BUTTON LOW LEVEL BUTTON
  * @{
  */
/* Button state */
#define BUTTON_RELEASED                       0U
#define BUTTON_PRESSED                        1U

#if defined (G4R_NANO)
/**
  * @brief RST push-button (PG10)
  */
#define RST_KEY_PIN                           GPIO_PIN_10
#define RST_KEY_GPIO_PORT                     GPIOG
#define RST_KEY_GPIO_CLK_ENABLE()             __HAL_RCC_GPIOG_CLK_ENABLE()
#define RST_KEY_GPIO_CLK_DISABLE()            __HAL_RCC_GPIOG_CLK_DISABLE()
#define RST_KEY_EXTI_IRQn                     EXTI15_10_IRQn
#define RST_KEY_EXTI_LINE                     EXTI_LINE_10

/**
  * @brief BOOT0 push-button (PB8)
  */
#define BOOT0_KEY_PIN                         GPIO_PIN_8
#define BOOT0_KEY_GPIO_PORT                   GPIOB
#define BOOT0_KEY_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()
#define BOOT0_KEY_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOB_CLK_DISABLE()
#define BOOT0_KEY_EXTI_IRQn                   EXTI9_5_IRQn
#define BOOT0_KEY_EXTI_LINE                   EXTI_LINE_8
#elif defined (G4V_MINI)
/**
  * @brief RST push-button (PG10)
  */
#define RST_KEY_PIN                           GPIO_PIN_10
#define RST_KEY_GPIO_PORT                     GPIOG
#define RST_KEY_GPIO_CLK_ENABLE()             __HAL_RCC_GPIOG_CLK_ENABLE()
#define RST_KEY_GPIO_CLK_DISABLE()            __HAL_RCC_GPIOG_CLK_DISABLE()
#define RST_KEY_EXTI_IRQn                     EXTI15_10_IRQn
#define RST_KEY_EXTI_LINE                     EXTI_LINE_10

/**
  * @brief BOOT0 push-button (PB8)
  */
#define BOOT0_KEY_PIN                         GPIO_PIN_8
#define BOOT0_KEY_GPIO_PORT                   GPIOB
#define BOOT0_KEY_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()
#define BOOT0_KEY_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOB_CLK_DISABLE()
#define BOOT0_KEY_EXTI_IRQn                   EXTI9_5_IRQn
#define BOOT0_KEY_EXTI_LINE                   EXTI_LINE_8
#elif defined (G4C_NANO)
/**
  * @brief RST push-button (PG10)
  */
#define RST_KEY_PIN                           GPIO_PIN_10
#define RST_KEY_GPIO_PORT                     GPIOG
#define RST_KEY_GPIO_CLK_ENABLE()             __HAL_RCC_GPIOG_CLK_ENABLE()
#define RST_KEY_GPIO_CLK_DISABLE()            __HAL_RCC_GPIOG_CLK_DISABLE()
#define RST_KEY_EXTI_IRQn                     EXTI15_10_IRQn
#define RST_KEY_EXTI_LINE                     EXTI_LINE_10

/**
  * @brief BOOT0 push-button (PB8)
  */
#define BOOT0_KEY_PIN                         GPIO_PIN_8
#define BOOT0_KEY_GPIO_PORT                   GPIOB
#define BOOT0_KEY_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()
#define BOOT0_KEY_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOB_CLK_DISABLE()
#define BOOT0_KEY_EXTI_IRQn                   EXTI9_5_IRQn
#define BOOT0_KEY_EXTI_LINE                   EXTI_LINE_8
#endif /* G4R_NANO / G4V_MINI / G4C_NANO */
/**
  * @}
  */

/** @defgroup STM32G4XX_BORING_LOW_LEVEL_COM LOW LEVEL COM
  * @{
  */
/**
 * @brief Definition for COM port1, connected to USART1
 */
#if (USE_BSP_COM_FEATURE > 0)
#define COM1_UART                             USART1
#define COM1_CLK_ENABLE()                     __HAL_RCC_USART1_CLK_ENABLE()
#define COM1_CLK_DISABLE()                    __HAL_RCC_USART1_CLK_DISABLE()

#define COM1_TX_PIN                           GPIO_PIN_9
#define COM1_TX_GPIO_PORT                     GPIOA
#define COM1_TX_GPIO_CLK_ENABLE()             __HAL_RCC_GPIOA_CLK_ENABLE()
#define COM1_TX_GPIO_CLK_DISABLE()            __HAL_RCC_GPIOA_CLK_DISABLE()
#define COM1_TX_AF                            GPIO_AF7_USART1

#define COM1_RX_PIN                           GPIO_PIN_10
#define COM1_RX_GPIO_PORT                     GPIOA
#define COM1_RX_GPIO_CLK_ENABLE()             __HAL_RCC_GPIOA_CLK_ENABLE()
#define COM1_RX_GPIO_CLK_DISABLE()            __HAL_RCC_GPIOA_CLK_DISABLE()
#define COM1_RX_AF                            GPIO_AF7_USART1
#define COM_POLL_TIMEOUT                      1000

#define MX_UART_InitTypeDef COM_InitTypeDef
#endif /* (USE_BSP_COM_FEATURE > 0)*/
/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup STM32G4XX_BORING_LOW_LEVEL_Exported_Variables
  * @{
  */
#if defined (G4R_NANO) || defined (G4V_MINI) || defined (G4C_NANO)
extern EXTI_HandleTypeDef hpb_exti[];
#endif /* (G4R_NANO) || (G4V_MINI) || (G4C_NANO) */
#if (USE_BSP_COM_FEATURE > 0)
extern UART_HandleTypeDef hcom_uart[];
#endif /* (USE_BSP_COM_FEATURE > 0) */
/**
  * @}
  */

/** @defgroup STM32G4XX_BORING_LOW_LEVEL_Exported_Functions LOW LEVEL Exported Functions
  * @{
  */
int32_t  BSP_GetVersion(void);
const uint8_t* BSP_GetBoardName(void);
const uint8_t* BSP_GetBoardID(void);

/* Legacy APIs aliases */
#define BSP_GetHWBoardVersionName    BSP_GetBoardName
#define BSP_GetPDTypeName            BSP_GetBoardID

int32_t  BSP_LED_Init(Led_TypeDef Led);
int32_t  BSP_LED_DeInit(Led_TypeDef Led);
int32_t  BSP_LED_On(Led_TypeDef Led);
int32_t  BSP_LED_Off(Led_TypeDef Led);
int32_t  BSP_LED_Toggle(Led_TypeDef Led);
int32_t  BSP_LED_GetState (Led_TypeDef Led);
#if defined (G4R_NANO) || defined (G4V_MINI) || defined (G4C_NANO)
int32_t  BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode);
int32_t  BSP_PB_DeInit(Button_TypeDef Button);
int32_t  BSP_PB_GetState(Button_TypeDef Button);
void     BSP_PB_Callback(Button_TypeDef Button);
void     BSP_PB_IRQHandler(Button_TypeDef Button);
#endif /* (G4R_NANO) || (G4V_MINI) || (G4C_NANO) */
#if (USE_BSP_COM_FEATURE > 0)
int32_t  BSP_COM_Init(COM_TypeDef COM, COM_InitTypeDef *COM_Init);
int32_t  BSP_COM_DeInit(COM_TypeDef COM);
#if (USE_COM_LOG > 0)
int32_t  BSP_COM_SelectLogPort (COM_TypeDef COM);
#endif
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
int32_t  BSP_COM_RegisterDefaultMspCallbacks(COM_TypeDef COM);
int32_t  BSP_COM_RegisterMspCallbacks(COM_TypeDef COM , BSP_COM_Cb_t *Callback);
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
HAL_StatusTypeDef MX_USART1_Init(UART_HandleTypeDef *huart, MX_UART_InitTypeDef *COM_Init);
#endif /* (USE_BSP_COM_FEATURE > 0) */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32G4XX_BORING_H */


