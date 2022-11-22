#ifndef SYSTEM_H_
#define SYSTEM_H_

// #include "system/system.h"


#include <Arduino.h>
#include <stdio.h.>
#include <stdlib.h>
#include <string.h>
// #include <avr/wdt.h>

#define WDT_SECOND 1000000

#define TIME_TO_INITIALIZE_SYSTEM 2000

void system_forceRestart(void);
void system_initialize(void);
void system_manualWdtInitialize(void);
void system_wdtReset(void);
boolean system_timeOut(unsigned long _timeOut);
boolean system_timeOut_2(unsigned long _timeOut);

// DEBUG:
void system_printPack(String msgHead, uint8_t*ptrBuff, uint16_t buffLen);
void system_printCharBuff(String msgHead, uint8_t*ptrBuff, uint16_t buffLen);

//
// // Example Timeout
// while(system_timeOut(5000)){
//     if((millis()-oldTime)>500){
//         oldTime=millis();
//         Serial.println("timeOut_1");
//     }
// }

#endif /* #ifndef SYSTEM_H_ */
