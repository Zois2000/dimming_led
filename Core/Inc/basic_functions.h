#include "stm32f1xx_hal.h"
#include "usart.h"
#include "button_led_config.h"

void uprintf(char* str);
void number_to_string(int num, char* buffer);
void custom_pwm_frequency(uint16_t led_on_ms, uint16_t led_off_ms, uint8_t index);
void custom_pwm(uint8_t duty_cycle, uint8_t frequency, uint8_t index);