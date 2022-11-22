#include "Gateway/gateway.h"
#include "System/system.h"
#include "Hardware/hardware.h"
#include "Modules/eeprom/eepromArch.h"
#include "Gateway/gatewayMode.h"

#define GETEWAY_DEBUG_ENABLE // descomente esta linha para habilitar o debug. 
#ifdef GETEWAY_DEBUG_ENABLE
  #define GETEWAY_DEBUG_PRINT(...) { Serial.print(__VA_ARGS__); }
  #define GETEWAY_DEBUG_PRINTLN(...) { Serial.println(__VA_ARGS__); }
#else
  #define GETEWAY_DEBUG_PRINT(...) {}
  #define GETEWAY_DEBUG_PRINTLN(...) {}
#endif

#define TIME_DEBUG_STATUS 1000

void geteway_debugStatus(SystemStatus* systemStatus);

/**
 * @brief 
 * 
 * @param systemStatus 
 */
void gateway_init(SystemStatus* systemStatus){
	
    eeprmArch_initialize();
	
    gatewayMode_init(systemStatus);
}

/**
 * @brief 
 * 
 * @param systemStatus 
 */
void gateway_run(SystemStatus* systemStatus){
	
	// If using a static IP, comment out the next line
	// Ethernet.maintain();    // comentei pq estou usando IP estatico.
	    
    gatewayMode_run(systemStatus);

    geteway_debugStatus(systemStatus);
}

void geteway_debugStatus(SystemStatus* systemStatus){
    static unsigned long timerDebugStatus = millis();

    if( millis() - timerDebugStatus > TIME_DEBUG_STATUS){
        timerDebugStatus = millis();

        GETEWAY_DEBUG_PRINT("STATUS: ");
        GETEWAY_DEBUG_PRINTLN(systemStatus->network.status);
    }
    
}