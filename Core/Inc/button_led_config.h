/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    button_led_config.h
  * @brief   This file contains the header for the button_led_config function
  * @author  Andreas Schweizer (andreas.schweizer@studmail.htw-aalen.de).
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

// Struktur zur Aufbewahrung von Informationen über Tasten
typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
    uint32_t button_last_time_ms;
} button_config;

// Struktur zur Aufbewahrung von Informationen über LEDs
typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
    uint16_t led_on_ms;      // Einschaltzeit in Millisekunden
    uint16_t led_off_ms;     // Ausschaltzeit in Millisekunden
    uint32_t led_last_time_ms;
    uint8_t led_duty_time;
    uint8_t led_duty_cycle_state;
} led_config;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

// Anzahl der Tasten und LEDs
#define NUM_Buttons 5
#define NUM_LEDS 5
#define DEBOUNCE_TIME_MS 200

/* USER CODE END PD */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */

// Arrays für Tasten- und LED-Konfigurationen sowie Variablen zur Speicherung der Anzahl

extern button_config button_configs[NUM_Buttons];
extern led_config led_configs[NUM_LEDS];
extern const int num_buttons;
extern const int num_leds;

/* USER CODE END EFP */

