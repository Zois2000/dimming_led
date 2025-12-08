/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    button_led_config.c
  * @brief   This file contains the cunstroctions for the buttons and leds
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

/* Includes ------------------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "button_led_config.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

// Struktur zur Aufbewahrung von Informationen zu Tasten
button_config button_configs[NUM_Buttons] = {
		{button_1_GPIO_Port, button_1_Pin},
		{button_2_GPIO_Port, button_2_Pin},
		{button_3_GPIO_Port, button_3_Pin},
		{button_4_GPIO_Port, button_4_Pin},
		{button_user_GPIO_Port, button_user_Pin},
};
const int num_buttons = NUM_Buttons;  // Speichert die Anzahl der Tasten

// Struktur zur Aufbewahrung von Informationen zu LEDs
led_config led_configs[NUM_LEDS] = {
		{led_1_GPIO_Port, led_1_Pin, 0, 0},
		{led_2_GPIO_Port, led_2_Pin, 0, 0},
		{led_3_GPIO_Port, led_3_Pin, 0, 0},
		{led_4_GPIO_Port, led_4_Pin, 0, 0},
		{led_user_GPIO_Port, led_user_Pin, 0, 0},
};
const int num_leds = NUM_LEDS;  // Speichert die Anzahl der LEDs
/* USER CODE END PV */
