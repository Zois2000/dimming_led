/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    button_led_config.h
  * @brief   This file contains the header for the button_led_config function
  * @author  Andreas Schweizer (andreas.schweizer@mailbox.org).
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023.
  * All rights reserved.
  *
 ******************************************************************************
  */
/* USER CODE END Header */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#pragma once

#include "gpio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

// Structure to store button configuration
typedef struct {
    GPIO_TypeDef* port;           // GPIO port for the button
    uint16_t pin;                 // GPIO pin for the button
    uint32_t button_last_time_ms; // Last time the button was pressed (in ms)
} button_config;

// Structure to store LED configuration
typedef struct {
    GPIO_TypeDef* port;           // GPIO port for the LED
    uint16_t pin;                 // GPIO pin for the LED
    uint16_t led_on_ms;           // LED on time in milliseconds
    uint16_t led_off_ms;          // LED off time in milliseconds
    uint32_t led_last_time_ms;    // Last time the LED was toggled (in ms)
    uint8_t led_duty_time;        // LED duty cycle in percentage (0-100)
    uint8_t led_duty_cycle_state; // State of the LED (e.g., increasing or decreasing brightness)
} led_config;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

// Number of buttons and LEDs in the system
#define NUM_BUTTONS 5           // Number of buttons
#define NUM_LEDS 5              // Number of LEDs
#define DEBOUNCE_TIME_MS 200    // Debounce time for buttons in milliseconds

/* USER CODE END PD */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */

// Externally declared arrays for button and LED configurations, and variables to store their counts
extern button_config button_configs[NUM_BUTTONS]; // Array for button configurations
extern led_config led_configs[NUM_LEDS];          // Array for LED configurations
extern const int num_buttons;                     // Number of buttons
extern const int num_leds;                        // Number of LEDs

/* USER CODE END EFP */

