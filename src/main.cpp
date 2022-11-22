#include <main.h>
#include "Database/Structures/systemStatus.h"
#include "Hardware/hardware.h"
#include "Gateway/gateway.h"

/**
 * @brief Arquivo main do firmware.
 * @name 
 * @version | 4.0
 * @date    | 22/11/2022     
 * @github  | First update: 20/06/2020.
 * @author  | leonardohilgemberg@gmail.com  | laonardo Hilgemberg Lopes |
 * @file    | main.h
 * @note    | fone WPP (41)99661-6761
 * @warning | 
 **/

#define MAIN_DEBUG_ENABLE // descomente esta linha para habilitar o debug. 
#ifdef MAIN_DEBUG_ENABLE
  #define MAIN_DEBUG_PRINT(...) { Serial.print(__VA_ARGS__); }
  #define MAIN_DEBUG_PRINTLN(...) { Serial.println(__VA_ARGS__); }
  #define DEBUG_SERIAL_BEGIN(a)    Serial.begin(a)
#else
  #define MAIN_DEBUG_PRINT(...) {}
  #define MAIN_DEBUG_PRINTLN(...) {}
  #define DEBUG_SERIAL_BEGIN(a)    do{}while(0)
#endif

SystemStatus systemStatus;

void debugMeanInfo(SystemStatus *systemStatus);

void setup() {

    Serial.begin(115200); // ok
    MAIN_DEBUG_PRINTLN("\tSerial Comm Started\r\n");

    hardware_initialize();

    systemStatus_initialize(&systemStatus);

    system_initialize();

    gateway_init(&systemStatus); // OK
}

void loop(){

    system_wdtReset(); // alimenta wdt

    gateway_run(&systemStatus); 
}