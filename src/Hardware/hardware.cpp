#include "Hardware/hardware.h"
#include <Arduino.h>

void hardware_initialize(void){

    // Led RGB
    pinMode(PIN_LED_RGB_RED, OUTPUT);
    pinMode(PIN_LED_RGB_GREEN, OUTPUT);
    pinMode(PIN_LED_RGB_BLUE, OUTPUT);

    // btn de controle da eeprom...
    pinMode(PIN_BUTTON_CLR_EEPROM, INPUT);
}
