#include "basic_functions.h"
#include "usart.h"

void uprintf(char* str) {
    uint8_t len = 0;
    while (str[len] != '\0') {  // Länge der Zeichenkette ermitteln
        len++;
    }
    
    uint8_t buffer[len];  // Puffer mit der gleichen Länge wie die Zeichenkette
    for (uint8_t i = 0; i < len; i++) {
        buffer[i] = str[i];  // Zeichen in den Puffer kopieren
    }

    HAL_UART_Transmit(&huart2, buffer, len, HAL_MAX_DELAY);  // Den gesamten Puffer auf einmal senden
}

// Umwandlung einer Zahl in eine Zeichenkette
void number_to_string(uint32_t number, char* buffer) {
    uint8_t i = 0;
    uint8_t is_negativ = 0;

    // Handle 0 speziell
    if (number == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        buffer[i + 1] = '\r';  // Carriage Return (Cursor ans Zeilenanfang)
        buffer[i + 2] = '\n';  // '\n' hinzufügen für Zeilenumbruch
        buffer[i + 3] = '\0';  // Nullterminator setzen
        return;
    }

    // Handle negative Zahlen
    if (number < 0) {
        is_negativ = 1;
        number = -number;
    }

    // Zahl in den Puffer umwandeln
    while (number != 0) {
        int rem = number % 10;
        buffer[i++] = rem + '0';  // Rest in Zeichen umwandeln
        number = number / 10;
    }

    // Negative Zahl mit Minuszeichen behandeln
    if (is_negativ) {
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
