
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Ds18b20.h"

#define DS18B20_DEBUG_ENABLE // descomente esta linha para habilitar o debug. 
#ifdef DS18B20_DEBUG_ENABLE
    #define DS18B20_DEBUG_PRINT(...) { Serial.print(__VA_ARGS__); }
    #define DS18B20_DEBUG_PRINTLN(...) { Serial.println(__VA_ARGS__); }
#else
    #define DS18B20_DEBUG_PRINT(...) {}
    #define DS18B20_DEBUG_PRINTLN(...) {}
#endif /* MAIN_DEBUG_ENABLE */

#define TIME_TEMP_DS18B20 1000

#define TIMEOUT_START_SENSOR 3000

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(PIN_ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature DS18b20_sensors(&oneWire);

// arrays to hold device address
DeviceAddress DSAddress;

uint8_t DS18b20_init(void){

    uint8_t result=EXIT_SUCCESS;
    unsigned long timeoutTemp=0;
    DS18B20_DEBUG_PRINTLN("DS18b20_init(ini)");
    //setup one wire
    DS18b20_sensors.begin();
    // DS18b20_sensors.setWaitForConversion(true);

	DS18b20_sensors.getAddress(DSAddress, 0);

	DS18b20_sensors.setWaitForConversion(false);

	DS18b20_sensors.requestTemperatures(); // Send the command to get temperatures
	
    timeoutTemp = millis();
    while (DS18b20_sensors.isConversionAvailable(DSAddress)==false){
		//wait for first temp to prevent false reading at startup
		delay(1);

        if(millis() - timeoutTemp > TIMEOUT_START_SENSOR){
            result = EXIT_FAILURE;
            break;
        }
	}

    if(result == EXIT_SUCCESS){
        DS18b20_sensors.getTempCByIndex(0);   //get first temp
	    DS18b20_sensors.requestTemperatures(); // Send the command to get temperatures
        DS18B20_DEBUG_PRINTLN("OK - DS18b20_init(end)");
    }else{
        DS18B20_DEBUG_PRINTLN("ERROR - DS18b20_init(end)");
    }

    return result;
}

float currentStaticTemp = 0.1;

float getTemperature_DS18B20(void){

    static unsigned long oldTimeGetTemp=0;

    // if((millis()-oldTime) > _TIMER_GET_TEMP_ )
    if((millis()-oldTimeGetTemp) > TIME_TEMP_DS18B20)
    {
        oldTimeGetTemp = millis();

        if (DS18b20_sensors.isConversionAvailable(DSAddress))
        {
            // tempF=DS18b20_sensors.getTempF(DSAddress);
            currentStaticTemp = DS18b20_sensors.getTempCByIndex(0);
            DS18b20_sensors.requestTemperatures(); // Send the command to get temperatures
        }else{
            return currentStaticTemp;
        }

        DS18B20_DEBUG_PRINT("Temperature for the device 1 (index 0) is: ");
        DS18B20_DEBUG_PRINTLN(currentStaticTemp);

    }
    return currentStaticTemp;
}