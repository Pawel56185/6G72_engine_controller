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
#define ENC_SPARSE_EXTI_IRQn EXTI1_IRQn
#define ENC_DENSE_Pin GPIO_PIN_2
#define ENC_DENSE_GPIO_Port GPIOA
#define ENC_DENSE_EXTI_IRQn EXTI2_IRQn
#define HOME_Pin GPIO_PIN_3
#define HOME_GPIO_Port GPIOA
#define STEPPER_LEFT_Pin GPIO_PIN_4
#define STEPPER_LEFT_GPIO_Port GPIOA
#define STEPPER_RIGHT_Pin GPIO_PIN_5
#define STEPPER_RIGHT_GPIO_Port GPIOA
#define DEBUG_LED_Pin GPIO_PIN_12
#define DEBUG_LED_GPIO_Port GPIOB
#define INJECTOR1_Pin GPIO_PIN_10
#define INJECTOR1_GPIO_Port GPIOD
#define INJECTOR2_Pin GPIO_PIN_11
#define INJECTOR2_GPIO_Port GPIOD
#define INJECTOR3_Pin GPIO_PIN_12
#define INJECTOR3_GPIO_Port GPIOD
#define INJECTOR4_Pin GPIO_PIN_13
#define INJECTOR4_GPIO_Port GPIOD
#define INJECTOR5_Pin GPIO_PIN_14
#define INJECTOR5_GPIO_Port GPIOD
#define INJECTOR6_Pin GPIO_PIN_15
#define INJECTOR6_GPIO_Port GPIOD
#define COIL_1_4_Pin GPIO_PIN_0
#define COIL_1_4_GPIO_Port GPIOD
#define COIL_2_5_Pin GPIO_PIN_1
#define COIL_2_5_GPIO_Port GPIOD
#define COIL_3_6_Pin GPIO_PIN_2
#define COIL_3_6_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */
#define TRUE    1
#define FALSE   0
#define INF8    255
#define INF16   65535
#define INF32   4294967295
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
