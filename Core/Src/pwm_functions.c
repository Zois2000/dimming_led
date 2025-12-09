#include "pwm_functions.h"
#include "button_led_config.h"
#include "gpio.h"

void custom_pwm(uint8_t duty_cycle, uint8_t frequency, uint8_t index) {

    if (index >= num_leds || duty_cycle > 100 || frequency <= 0) {
        return;
    }

    uint32_t time_now = HAL_GetTick();
    uint16_t led_on_ms = (duty_cycle * 10) / frequency;
    uint16_t led_off_ms = (100 * 10) / frequency - led_on_ms;

    if (led_configs[index].led_state) {
        custom_led_on(time_now, led_on_ms, index);

    } else {
        custom_led_off(time_now, led_off_ms, index);
    }
}

void custom_led_on(uint32_t time_now, uint16_t led_on_ms, uint8_t index) {
    if (time_now - led_configs[index].led_last_time_ms >= led_on_ms) {
        HAL_GPIO_WritePin(led_configs[index].port, led_configs[index].pin, GPIO_PIN_RESET);
        led_configs[index].led_state = 0;
        led_configs[index].led_last_time_ms = time_now;
    }
}

void custom_led_off(uint32_t time_now, uint16_t led_off_ms, uint8_t index) {
    if (time_now - led_configs[index].led_last_time_ms >= led_off_ms) {
        HAL_GPIO_WritePin(led_configs[index].port, led_configs[index].pin, GPIO_PIN_SET);
        led_configs[index].led_state = 1;
        led_configs[index].led_last_time_ms = time_now;
    }
}

void custom_frequency(uint8_t index) {

    uint32_t time_now = HAL_GetTick();

    if (time_now - button_configs[index].button_last_time_ms >= DEBOUNCE_TIME_MS && HAL_GPIO_ReadPin(button_configs[index].port, button_configs[index].pin) == GPIO_PIN_RESET) {
    
    }
}
