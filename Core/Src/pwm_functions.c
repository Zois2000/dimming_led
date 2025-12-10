/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    pwm_functions.c
  * @brief   Contains the functions for PWM control and LED dimming.
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
#include "pwm_functions.h"
#include "basic_functions.h"
#include "stm32f1xx_hal_gpio.h"
#include <stdint.h>
/* USER CODE END Includes */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void turn_led_on_if_time(uint32_t time_now, uint8_t index);
void turn_led_off_if_time(uint32_t time_now, uint8_t index);
void adjust_duty_cycle(uint8_t index);
void update_duty_cycle_direction(uint8_t index);
/* USER CODE END PFP */

/* Private functions ---------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/**
  * @brief  Adjusts the duty cycle of the LED.
  * @param  index: The index of the LED to adjust.
  * @retval None
  */
void adjust_duty_cycle(uint8_t index) {
    if (led_configs[index].led_duty_cycle_state == 1) {
        led_configs[index].led_duty_time += 10; // Increase duty cycle
    }
    if (led_configs[index].led_duty_cycle_state == 0) {
        led_configs[index].led_duty_time -= 10; // Decrease duty cycle
    }
}

/**
  * @brief  Updates the direction of the duty cycle (increasing or decreasing).
  * @param  index: The index of the LED to update.
  * @retval None
  */
void update_duty_cycle_direction(uint8_t index) {
    if (led_configs[index].led_duty_time == 100) {
        led_configs[index].led_duty_cycle_state = 0; // Reverse direction (decrease brightness)
    }
    if (led_configs[index].led_duty_time == 0) {
        led_configs[index].led_duty_cycle_state = 1; // Reverse direction (increase brightness)
    }
}

/**
  * @brief  Turns the LED on if the time for turning on has passed.
  * @param  time_now: The current time in milliseconds.
  * @param  index: The index of the LED to control.
  * @retval None
  */
void turn_led_on_if_time(uint32_t time_now, uint8_t index) {
    if (time_now - led_configs[index].led_last_time_ms >= led_configs[index].led_on_ms && 
        HAL_GPIO_ReadPin(led_configs[index].port, led_configs[index].pin) == GPIO_PIN_SET) {
        HAL_GPIO_WritePin(led_configs[index].port, led_configs[index].pin, GPIO_PIN_RESET); // Turn LED on
        led_configs[index].led_last_time_ms = time_now; // Update the last time
    }
}

/**
  * @brief  Turns the LED off if the time for turning off has passed.
  * @param  time_now: The current time in milliseconds.
  * @param  index: The index of the LED to control.
  * @retval None
  */
void turn_led_off_if_time(uint32_t time_now, uint8_t index) {
    if (time_now - led_configs[index].led_last_time_ms >= led_configs[index].led_off_ms && 
        HAL_GPIO_ReadPin(led_configs[index].port, led_configs[index].pin) == GPIO_PIN_RESET) {
        HAL_GPIO_WritePin(led_configs[index].port, led_configs[index].pin, GPIO_PIN_SET); // Turn LED off
        led_configs[index].led_last_time_ms = time_now; // Update the last time
        update_duty_cycle_direction(index); // Update duty cycle direction
        adjust_duty_cycle(index); // Adjust the duty cycle
    }
}

/**
  * @brief  Updates the dimming of the LED based on the frequency and duty cycle.
  * @param  frequency: The frequency at which the LED is dimmed.
  * @param  index: The index of the LED to control.
  * @retval None
  */
void update_led_dimming(uint16_t frequency, uint8_t index) {
    if (index >= num_leds || led_configs[index].led_duty_time > 100 || frequency <= 0) {
        return; // Return if index is out of range, or if frequency is invalid
    }

    uint32_t time_now = HAL_GetTick(); // Get the current time
    if (led_configs[index].led_duty_time > 0) {
        led_configs[index].led_on_ms = (led_configs[index].led_duty_time * 10) / frequency; // Calculate on time
    } else {
        led_configs[index].led_on_ms = 0;
    }
    led_configs[index].led_off_ms = (100 * 10) / frequency - led_configs[index].led_on_ms; // Calculate off time

    // Based on the duty cycle state, update the LED behavior
    switch (led_configs[index].led_duty_cycle_state) {
        case 0:
            turn_led_on_if_time(time_now, index);  // Turn LED on if time
            turn_led_off_if_time(time_now, index); // Turn LED off if time
            break;

        case 1:
            turn_led_on_if_time(time_now, index);  // Turn LED on if time
            turn_led_off_if_time(time_now, index); // Turn LED off if time
            break;
    }
}
/* USER CODE END 1 */
