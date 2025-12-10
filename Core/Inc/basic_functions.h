/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    basic_functions.h
  * @brief   Header file for basic utility functions like string conversion and UART transmission.
  * @author  Andreas Schweizer (andreas.schweizer@mailbox.org)
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023.
  * All rights reserved.
  ******************************************************************************
  */
/* USER CODE END Header */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#pragma once
#include "usart.h"
/* USER CODE END Includes */

/* Exported function prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */
void uprintf(char* str);
void number_to_string(uint32_t number, char* buffer);
/* USER CODE END EFP */

/* Private function prototypes ---------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private defines ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private functions ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
