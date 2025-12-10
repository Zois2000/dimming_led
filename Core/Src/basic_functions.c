/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    basic_functions.c
  * @brief   Contains basic utility functions like string handling and UART transmission.
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
#include "basic_functions.h"
#include "usart.h"
/* USER CODE END Includes */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private functions ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/**
  * @brief  Sends a string via UART.
  * @param  str: Pointer to the string to be sent.
  * @retval None
  */
void uprintf(char* str) {
    uint8_t len = 0;
    while (str[len] != '\0') {  // Determine string length
        len++;
    }

    uint8_t buffer[len];  // Create a buffer of the same length as the string
    for (uint8_t i = 0; i < len; i++) {
        buffer[i] = str[i];  // Copy each character into the buffer
    }

    HAL_UART_Transmit(&huart2, buffer, len, HAL_MAX_DELAY);  // Send the entire buffer at once
}

/**
  * @brief  Converts a number to a string.
  * @param  number: The number to be converted.
  * @param  buffer: Pointer to the buffer where the string will be stored.
  * @retval None
  */
void number_to_string(uint32_t number, char* buffer) {
    uint8_t i = 0;
    uint8_t is_negative = 0;

    // Special handling for 0
    if (number == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        buffer[i + 1] = '\r';  // Add carriage return (move cursor to the beginning)
        buffer[i + 2] = '\n';  // Add newline
        buffer[i + 3] = '\0';  // Null-terminate the string
        return;
    }

    // Handle negative numbers
    if (number < 0) {
        is_negative = 1;
        number = -number;
    }

    // Convert the number to string
    while (number != 0) {
        int rem = number % 10;
        buffer[i++] = rem + '0';  // Convert remainder to character
        number = number / 10;
    }

    // Handle negative number by adding minus sign
    if (is_negative) {
        buffer[i++] = '-';
    }

    // Reverse the string
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }

    // Add carriage return and newline
    buffer[i++] = '\r';  // Move cursor to the beginning of the line
    buffer[i++] = '\n';  // Add newline
    buffer[i] = '\0';    // Null-terminate the string
}

/* USER CODE END 0 */