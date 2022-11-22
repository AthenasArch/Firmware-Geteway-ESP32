#ifndef HARDWARE_DEFINITION_H_
#define HARDWARE_DEFINITION_H_

// #include "Hardware/hardware.h"

#include <Arduino.h>
#include <stdio.h.>
#include <stdlib.h>
#include <string.h>


#define PIN_LED_RGB_RED		19
#define PIN_LED_RGB_GREEN 	18
#define PIN_LED_RGB_BLUE	5

#define PIN_BUTTON_CLR_EEPROM 15 // utilizado com pull-Down - placa geteway

void hardware_initialize(void);

#endif /* HARDWARE_DEFINITION_H_ */
