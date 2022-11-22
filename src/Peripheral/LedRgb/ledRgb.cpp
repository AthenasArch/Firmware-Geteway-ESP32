#include <Arduino.h>
#include "Peripheral/LedRgb/ledRgb.h"
#include "Hardware/hardware.h"

unsigned long oldTimeLedRgb=0;

void ledRgb_Status(uint8_t setColoer, const uint16_t timeDelay){

    if((millis()-oldTimeLedRgb)>timeDelay){
        oldTimeLedRgb=millis();
    }
}

void ledRgb_initialize(void){
    pinMode(PIN_LED_RGB_RED, OUTPUT);
    pinMode(PIN_LED_RGB_GREEN, OUTPUT);
    pinMode(PIN_LED_RGB_BLUE, OUTPUT);
}

uint8_t ledRgb_basicCollors(uint8_t setColor, uint8_t blinkError){
	
	uint8_t result=EXIT_FAILURE;
    static unsigned long timerBlkLedStatus=0;
    static uint8_t toogleLEdStatus=0;

    if(blinkError==BLK_LED_STATUS_ON){
        if((millis()-timerBlkLedStatus)>TIME_INTERVAL_BLK_LED_STATUS){
            timerBlkLedStatus=millis();
            
            if(toogleLEdStatus==0){
                toogleLEdStatus=1;
            }else{
                toogleLEdStatus=0;
            }
        }
    }else{
        toogleLEdStatus=1;
    }

    if(toogleLEdStatus==1){
        switch(setColor){
            case RGB_COLOR_BLUE:
                // 	Azul - RGB (0, 0, 1)
                digitalWrite(PIN_LED_RGB_RED,   LED_RGB_OFF);
                digitalWrite(PIN_LED_RGB_GREEN, LED_RGB_OFF);
                digitalWrite(PIN_LED_RGB_BLUE,  LED_RGB_ON);
                break;
            case RGB_COLOR_GREEN:
                digitalWrite(PIN_LED_RGB_RED,   LED_RGB_OFF);
                digitalWrite(PIN_LED_RGB_GREEN, LED_RGB_ON);
                digitalWrite(PIN_LED_RGB_BLUE,  LED_RGB_OFF);
                break;
            case RGB_COLOR_CYAN:
                digitalWrite(PIN_LED_RGB_RED,   LED_RGB_OFF);
                digitalWrite(PIN_LED_RGB_GREEN, LED_RGB_ON);
                digitalWrite(PIN_LED_RGB_BLUE,  LED_RGB_ON);
                break;	
            case RGB_COLOR_RED:
                digitalWrite(PIN_LED_RGB_RED,   LED_RGB_ON);
                digitalWrite(PIN_LED_RGB_GREEN, LED_RGB_OFF);
                digitalWrite(PIN_LED_RGB_BLUE,  LED_RGB_OFF);
                break;
            case RGB_COLOR_PURPLE:
                digitalWrite(PIN_LED_RGB_RED,   LED_RGB_ON);
                digitalWrite(PIN_LED_RGB_GREEN, LED_RGB_OFF);
                digitalWrite(PIN_LED_RGB_BLUE,  LED_RGB_ON);
                break;
            case RGB_COLOR_YELLOW:
                digitalWrite(PIN_LED_RGB_RED,   LED_RGB_ON);
                digitalWrite(PIN_LED_RGB_GREEN, LED_RGB_ON);
                digitalWrite(PIN_LED_RGB_BLUE,  LED_RGB_OFF);
                break;
            case RGB_COLOR_WHITE:
                digitalWrite(PIN_LED_RGB_RED,   LED_RGB_ON);
                digitalWrite(PIN_LED_RGB_GREEN, LED_RGB_ON);
                digitalWrite(PIN_LED_RGB_BLUE,  LED_RGB_ON);
                break;
            default:
                digitalWrite(PIN_LED_RGB_RED,   LED_RGB_OFF);
                digitalWrite(PIN_LED_RGB_GREEN, LED_RGB_OFF);
                digitalWrite(PIN_LED_RGB_BLUE,  LED_RGB_OFF);
                break;
        }
    }else{
        digitalWrite(PIN_LED_RGB_RED,   LED_RGB_OFF);
        digitalWrite(PIN_LED_RGB_GREEN, LED_RGB_OFF);
        digitalWrite(PIN_LED_RGB_BLUE,  LED_RGB_OFF);
    }
	return result; 
}

void ledRgb_checkLeds(void){
    digitalWrite(PIN_LED_RGB_RED,   LED_RGB_ON);
    digitalWrite(PIN_LED_RGB_GREEN, LED_RGB_ON);
    digitalWrite(PIN_LED_RGB_BLUE,  LED_RGB_ON);
}
