#include <Arduino.h>
#include "Hardware/hardware.h"
#include "Gateway/gatewayStatus.h"

#define MAIN_DEBUG_ENABLE // descomente esta linha para habilitar o debug. 
#ifdef MAIN_DEBUG_ENABLE
  #define GATEWAY_STATUS_DEBUG_PRINT(...) { Serial.print(__VA_ARGS__); }
  #define GATEWAY_STATUS_DEBUG_PRINTLN(...) { Serial.println(__VA_ARGS__); }
#else
  #define GATEWAY_STATUS_DEBUG_PRINT(...) {}
  #define GATEWAY_STATUS_DEBUG_PRINTLN(...) {}
#endif

void gatewayStatus_initialize(void){
    ledRgb_initialize();
    ledRgb_checkLeds();
    delay(100);
}

char gatewayStatus_ledStatus(SystemStatus* systemStatus, uint8_t blinkError){

    char result=EXIT_SUCCESS;
    LED_RGB_BASIC_COLOR setColor;

    switch(systemStatus->network.status){
        case GATEWAY_AP_MODE_START:
            // GATEWAY_STATUS_DEBUG_PRINTLN(F("GETEWAY_AP_MODE_START"));
            setColor = RGB_COLOR_BLUE;
            break;
        case GATEWAY_TRY_CONNECT_MODEM:
            setColor = RGB_COLOR_RED;
            // GATEWAY_STATUS_DEBUG_PRINTLN(F("GETEWAY_TRY_CONNECT_MODEM"));
            break;
        case GATEWAY_CONNECT_SERVER_OK:
            setColor = RGB_COLOR_CYAN;
            break;
        case GATEWAY_MODEM_CONNECTED:
            // GATEWAY_STATUS_DEBUG_PRINTLN(F("GETEWAY_MODEM_CONNECTED"));
            setColor = RGB_COLOR_GREEN;
            break;        
        case GATEWAY_SENDING_POST_OK:
            // GATEWAY_STATUS_DEBUG_PRINTLN(F("GETEWAY_SENDING_POST_OK"));
            setColor = RGB_COLOR_PURPLE;
            break;
        case GATEWAY_ERROR_SEND_POST:
            // GATEWAY_STATUS_DEBUG_PRINTLN(F("GETEWAY_ERROR_SEND_POST"));
            setColor = RGB_COLOR_YELLOW;
            break;                    
        default:
            // GATEWAY_STATUS_DEBUG_PRINTLN(F("GETEWAY_ERROR_GENERIC"));
            setColor = RGB_COLOR_WHITE;
            break;
    }

    ledRgb_basicCollors(setColor, blinkError);
    return result;
}

