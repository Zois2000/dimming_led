#pragma once

void custom_pwm_frequency(uint16_t led_on_ms, uint16_t led_off_ms, uint8_t index);
void custom_pwm(uint8_t duty_cycle, uint8_t frequency, uint8_t index);
void custom_led_on(uint32_t time_now, uint16_t led_on_ms, uint8_t index);
void custom_led_off(uint32_t time_now, uint16_t led_off_ms, uint8_t index);