/**
  ******************************************************************************
  * @file    stm32g4xx_boring_conf.h
  * @author  MCD Application Team
  * @brief   STM32G4xx_BORING board configuration file.
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
#ifndef STM32G4XX_BORING_CONF_H
#define STM32G4XX_BORING_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32G4XX_BORING
  * @{
  */

/** @defgroup STM32G4XX_BORING_CONFIG Config
  * @{
  */

/** @defgroup STM32G4XX_BORING_CONFIG_Exported_Constants Exported Constants
  * @{
  */
/* Uncomment one of the board define below */
/* #define USE_NUCLEO_32 */
/* #define G4R_NANO */ /* G474RET6 (LQFP64) */
/* #define G4V_MINI */ /* G474VET6 (LQFP100) */
/* #define G4C_NANO */ /* G431CBT6 (LQFP48) */

/* COM usage define */
#define USE_BSP_COM_FEATURE                 0U

/* COM log define */
#define USE_COM_LOG                         0U

/* IRQ priorities */
#define BSP_RST_KEY_IT_PRIORITY              15U
#define BSP_BOOT0_KEY_IT_PRIORITY            15U
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

#endif /* STM32G4XX_BORING_CONF_H */


