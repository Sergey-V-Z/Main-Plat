/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#define CS4_5_Pin GPIO_PIN_3
#define CS4_5_GPIO_Port GPIOE
#define CS4_4_Pin GPIO_PIN_4
#define CS4_4_GPIO_Port GPIOE
#define CS2_1_Pin GPIO_PIN_0
#define CS2_1_GPIO_Port GPIOC
#define CS2_2_Pin GPIO_PIN_1
#define CS2_2_GPIO_Port GPIOC
#define RS485_1_TX_Pin GPIO_PIN_0
#define RS485_1_TX_GPIO_Port GPIOA
#define RS485_1_RX_Pin GPIO_PIN_1
#define RS485_1_RX_GPIO_Port GPIOA
#define CS1_1_Pin GPIO_PIN_4
#define CS1_1_GPIO_Port GPIOA
#define CS1_2_Pin GPIO_PIN_4
#define CS1_2_GPIO_Port GPIOC
#define CS1_3_Pin GPIO_PIN_5
#define CS1_3_GPIO_Port GPIOC
#define CS1_4_Pin GPIO_PIN_0
#define CS1_4_GPIO_Port GPIOB
#define CS1_5_Pin GPIO_PIN_1
#define CS1_5_GPIO_Port GPIOB
#define RS485_2_RX_Pin GPIO_PIN_7
#define RS485_2_RX_GPIO_Port GPIOE
#define RS485_2_TX_Pin GPIO_PIN_8
#define RS485_2_TX_GPIO_Port GPIOE
#define Set_0_Pin GPIO_PIN_9
#define Set_0_GPIO_Port GPIOE
#define Set_1_Pin GPIO_PIN_10
#define Set_1_GPIO_Port GPIOE
#define Set_2_Pin GPIO_PIN_11
#define Set_2_GPIO_Port GPIOE
#define CS2_3_Pin GPIO_PIN_13
#define CS2_3_GPIO_Port GPIOE
#define CS2_4_Pin GPIO_PIN_14
#define CS2_4_GPIO_Port GPIOE
#define CS2_5_Pin GPIO_PIN_15
#define CS2_5_GPIO_Port GPIOE
#define CAN2_Rs_Pin GPIO_PIN_11
#define CAN2_Rs_GPIO_Port GPIOB
#define RS485_2_Rs_Pin GPIO_PIN_14
#define RS485_2_Rs_GPIO_Port GPIOB
#define RS485_1_Rs_Pin GPIO_PIN_15
#define RS485_1_Rs_GPIO_Port GPIOB
#define LED_B_Pin GPIO_PIN_13
#define LED_B_GPIO_Port GPIOD
#define LED_G_Pin GPIO_PIN_14
#define LED_G_GPIO_Port GPIOD
#define LED_R_Pin GPIO_PIN_15
#define LED_R_GPIO_Port GPIOD
#define CAN1_Rs_Pin GPIO_PIN_6
#define CAN1_Rs_GPIO_Port GPIOC
#define SDIO_Detect_Pin GPIO_PIN_7
#define SDIO_Detect_GPIO_Port GPIOC
#define OUT_8_Pin GPIO_PIN_0
#define OUT_8_GPIO_Port GPIOD
#define OUT_7_Pin GPIO_PIN_1
#define OUT_7_GPIO_Port GPIOD
#define OUT_6_Pin GPIO_PIN_3
#define OUT_6_GPIO_Port GPIOD
#define OUT_5_Pin GPIO_PIN_4
#define OUT_5_GPIO_Port GPIOD
#define CS4_1_Pin GPIO_PIN_5
#define CS4_1_GPIO_Port GPIOD
#define CS4_2_Pin GPIO_PIN_6
#define CS4_2_GPIO_Port GPIOD
#define CS4_3_Pin GPIO_PIN_7
#define CS4_3_GPIO_Port GPIOD
#define OUT_4_Pin GPIO_PIN_6
#define OUT_4_GPIO_Port GPIOB
#define OUT_3_Pin GPIO_PIN_7
#define OUT_3_GPIO_Port GPIOB
#define OUT_2_Pin GPIO_PIN_8
#define OUT_2_GPIO_Port GPIOB
#define OUT_1_Pin GPIO_PIN_9
#define OUT_1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
