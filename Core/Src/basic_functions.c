#include "basic_functions.h"
#include "button_led_config.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include <stdint.h>

void uprintf(char* str) {
    uint16_t len = 0;
    while (str[len] != '\0') {  // Länge der Zeichenkette ermitteln
        len++;
    }
    
    uint8_t buffer[len];  // Puffer mit der gleichen Länge wie die Zeichenkette
    for (uint16_t i = 0; i < len; i++) {
        buffer[i] = str[i];  // Zeichen in den Puffer kopieren
    }

    HAL_UART_Transmit(&huart2, buffer, len, HAL_MAX_DELAY);  // Den gesamten Puffer auf einmal senden
}

// Umwandlung einer Zahl in eine Zeichenkette
void number_to_string(int num, char* buffer) {
    int i = 0;
    int isNegative = 0;

    // Handle 0 speziell
    if (num == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        buffer[i + 1] = '\r';  // Carriage Return (Cursor ans Zeilenanfang)
        buffer[i + 2] = '\n';  // '\n' hinzufügen für Zeilenumbruch
        buffer[i + 3] = '\0';  // Nullterminator setzen
        return;
    }

    // Handle negative Zahlen
    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    // Zahl in den Puffer umwandeln
    while (num != 0) {
        int rem = num % 10;
        buffer[i++] = rem + '0';  // Rest in Zeichen umwandeln
        num = num / 10;
    }

    // Negative Zahl mit Minuszeichen behandeln
    if (isNegative) {
        buffer[i++] = '-';
    }

    // String umkehren
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }

    // Füge '\r' und '\n' hinzu
    buffer[i++] = '\r';  // Cursor an den Anfang der Zeile setzen
    buffer[i++] = '\n';  // Zeilenumbruch hinzufügen
    buffer[i] = '\0';  // Nullterminator setzen
}

void custom_pwm(uint8_t duty_cycle, uint8_t frequency, uint8_t index) {

    if (index >= num_leds || duty_cycle > 100) {
        return;
    }

    uint32_t time_now = HAL_GetTick();
    uint16_t led_on_ms = (duty_cycle * 10) / frequency;
    uint16_t led_off_ms = (100 * 10) / frequency - led_on_ms;

    if (led_configs[index].led_state) {
        if (time_now - led_configs[index].time >= led_on_ms) {
            HAL_GPIO_WritePin(led_configs[index].port, led_configs[index].pin, GPIO_PIN_RESET);
            led_configs[index].led_state = 0;
            led_configs[index].time = time_now;
        }

    } else {
        if (time_now - led_configs[index].time >= led_off_ms) {
            HAL_GPIO_WritePin(led_configs[index].port, led_configs[index].pin, GPIO_PIN_SET);
            led_configs[index].led_state = 1;
            led_configs[index].time = time_now;
        }
    }
}
