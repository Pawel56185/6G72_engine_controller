/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define STEP_1_Pin GPIO_PIN_0
#define STEP_1_GPIO_Port GPIOC
#define STEP_2_Pin GPIO_PIN_1
#define STEP_2_GPIO_Port GPIOC
#define STEP_3_Pin GPIO_PIN_2
#define STEP_3_GPIO_Port GPIOC
#define STEP_4_Pin GPIO_PIN_3
#define STEP_4_GPIO_Port GPIOC
#define BASE_Pin GPIO_PIN_0
#define BASE_GPIO_Port GPIOA
#define ENC_SPARSE_Pin GPIO_PIN_1
#define ENC_SPARSE_GPIO_Port GPIOA
#define ENC_DENSE_Pin GPIO_PIN_2
#define ENC_DENSE_GPIO_Port GPIOA
#define HOME_Pin GPIO_PIN_3
#define HOME_GPIO_Port GPIOA
#define STEPPER_LEFT_Pin GPIO_PIN_4
#define STEPPER_LEFT_GPIO_Port GPIOA
#define STEPPER_RIGHT_Pin GPIO_PIN_5
#define STEPPER_RIGHT_GPIO_Port GPIOA
#define DEBUG_LED_Pin GPIO_PIN_12
#define DEBUG_LED_GPIO_Port GPIOB
#define WTR1_Pin GPIO_PIN_10
#define WTR1_GPIO_Port GPIOD
#define WTR2_Pin GPIO_PIN_11
#define WTR2_GPIO_Port GPIOD
#define WTR3_Pin GPIO_PIN_12
#define WTR3_GPIO_Port GPIOD
#define WTR4_Pin GPIO_PIN_13
#define WTR4_GPIO_Port GPIOD
#define WTR5_Pin GPIO_PIN_14
#define WTR5_GPIO_Port GPIOD
#define WTR6_Pin GPIO_PIN_15
#define WTR6_GPIO_Port GPIOD
#define CEWKA1_OD_Pin GPIO_PIN_0
#define CEWKA1_OD_GPIO_Port GPIOD
#define CEWKA2_OD_Pin GPIO_PIN_1
#define CEWKA2_OD_GPIO_Port GPIOD
#define CEWKA3_OD_Pin GPIO_PIN_2
#define CEWKA3_OD_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
