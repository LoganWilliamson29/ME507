/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define FAULT_n_Pin GPIO_PIN_13
#define FAULT_n_GPIO_Port GPIOC
#define ADC1_I1_Pin GPIO_PIN_0
#define ADC1_I1_GPIO_Port GPIOA
#define ADC1_I2_Pin GPIO_PIN_1
#define ADC1_I2_GPIO_Port GPIOA
#define ADC1_I3_Pin GPIO_PIN_2
#define ADC1_I3_GPIO_Port GPIOA
#define ADC1_I4_Pin GPIO_PIN_3
#define ADC1_I4_GPIO_Port GPIOA
#define ADC1_QBAT_Pin GPIO_PIN_4
#define ADC1_QBAT_GPIO_Port GPIOA
#define MOT1_PH_Pin GPIO_PIN_5
#define MOT1_PH_GPIO_Port GPIOA
#define MOT1_EN_Pin GPIO_PIN_6
#define MOT1_EN_GPIO_Port GPIOA
#define MOT2_EN_Pin GPIO_PIN_7
#define MOT2_EN_GPIO_Port GPIOA
#define MOT3_EN_Pin GPIO_PIN_0
#define MOT3_EN_GPIO_Port GPIOB
#define MOT4_EN_Pin GPIO_PIN_1
#define MOT4_EN_GPIO_Port GPIOB
#define MOT2_PH_Pin GPIO_PIN_2
#define MOT2_PH_GPIO_Port GPIOB
#define MOT3_PH_Pin GPIO_PIN_10
#define MOT3_PH_GPIO_Port GPIOB
#define MOT4_PH_Pin GPIO_PIN_12
#define MOT4_PH_GPIO_Port GPIOB
#define MOTORnSLEEP_Pin GPIO_PIN_13
#define MOTORnSLEEP_GPIO_Port GPIOB
#define LS4_Pin GPIO_PIN_14
#define LS4_GPIO_Port GPIOB
#define LS3_Pin GPIO_PIN_15
#define LS3_GPIO_Port GPIOB
#define LS1_Pin GPIO_PIN_9
#define LS1_GPIO_Port GPIOA
#define LS2_Pin GPIO_PIN_10
#define LS2_GPIO_Port GPIOA
#define STR_Pin GPIO_PIN_15
#define STR_GPIO_Port GPIOA
#define THR_Pin GPIO_PIN_3
#define THR_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
