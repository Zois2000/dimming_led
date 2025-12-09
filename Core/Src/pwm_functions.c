#include "pwm_functions.h"
#include "basic_functions.h"
#include "stm32f1xx_hal_gpio.h"
#include <stdint.h>

void custom_led_on(uint32_t time_now, uint8_t index);
void custom_led_off(uint32_t time_now, uint8_t index);
void cycle_update(uint8_t index);
void satus_update(uint8_t index);

void cycle_update(uint8_t index) {
    if (led_configs[index].led_duty_cycle_state == 1) {
        led_configs[index].led_duty_time += 10;
    }
    if (led_configs[index].led_duty_cycle_state == 0) {
        led_configs[index].led_duty_time -= 10;
    }
}

void satus_update(uint8_t index) {
    if (led_configs[index].led_duty_time == 100) {
        led_configs[index].led_duty_cycle_state = 0;
    }
    if (led_configs[index].led_duty_time == 0) {
        led_configs[index].led_duty_cycle_state = 1;
    }
}

void custom_led_on(uint32_t time_now, uint8_t index) {
    if (time_now - led_configs[index].led_last_time_ms >= led_configs[index].led_on_ms && HAL_GPIO_ReadPin(led_configs[index].port, led_configs[index].pin) == GPIO_PIN_SET) {
        HAL_GPIO_WritePin(led_configs[index].port, led_configs[index].pin, GPIO_PIN_RESET);
        led_configs[index].led_last_time_ms = time_now;
    }
}

void custom_led_off(uint32_t time_now, uint8_t index) {
    if (time_now - led_configs[index].led_last_time_ms >= led_configs[index].led_off_ms && HAL_GPIO_ReadPin(led_configs[index].port, led_configs[index].pin) == GPIO_PIN_RESET) {
        HAL_GPIO_WritePin(led_configs[index].port, led_configs[index].pin, GPIO_PIN_SET);
        led_configs[index].led_last_time_ms = time_now;
        satus_update(index);
        cycle_update(index);
    }
}

void dimming_state_maschine(uint16_t frequency, uint8_t index) {

    if (index >= num_leds || led_configs[index].led_duty_time > 100 || frequency <= 0) {
        return;
    }

    uint32_t time_now = HAL_GetTick();
    if (led_configs[index].led_duty_time > 0) {
        led_configs[index].led_on_ms = (led_configs[index].led_duty_time * 10) / frequency;
    } else {
        led_configs[index].led_on_ms = 0;
    }
    led_configs[index].led_off_ms = (100 * 10) / frequency - led_configs[index].led_on_ms;

    switch (led_configs[index].led_duty_cycle_state) {
        case 0:
        custom_led_on(time_now, index);
        custom_led_off(time_now, index);
        break;


        case 1:
        custom_led_on(time_now, index);
        custom_led_off(time_now, index);
        break;
    }
}