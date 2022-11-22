#ifndef DS18B20_H
#define DS18B20_H

// #include "Ds18b20.h"
#include <Arduino.h>

//setup one wire sensor
#define PIN_ONE_WIRE_BUS    15

uint8_t DS18b20_init(void);
float getTemperature_DS18B20();


/*
////    Baseado em:
// https://www.best-microcontroller-projects.com/ds18b20.html

// Data wire is plugged into port 2 on the Arduino

#define ONE_WIRE_BUS 4

// Setup a oneWire
// instance to communicate with any OneWire devices (not just Maxim/Dallas
// temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our
// oneWire reference to Dallas Temperature.
DallasTemperature DS18b20_sensors(&oneWire);

unsigned long oldTimeGetTemp = 0;
#define _TIMER_GET_TEMP_ 1000

unsigned long msCounter = 0;

float getTemperature_DS18B20(bool _DS18B20_serialDebug_);
void DS18b20_init(void);

void DS18b20_init(void){

    DS18b20_sensors.begin();
    DS18b20_sensors.setWaitForConversion(true);
}

float getTemperature_DS18B20(bool _DS18B20_serialDebug_){

    // if((millis()-oldTime) > _TIMER_GET_TEMP_ )
    if((millis()-oldTimeGetTemp) > 100 )
    {
        DS18b20_sensors.requestTemperatures();
        // ASYNC mode
        if(DS18b20_sensors.getWaitForConversion())
        {
            if(_DS18B20_serialDebug_)
            {
                Serial.print("Temperature for the device 1 (index 0) is: ");
                Serial.println(DS18b20_sensors.getTempCByIndex(0));
            }

            return DS18b20_sensors.getTempCByIndex(0);
        }else{
            if(_DS18B20_serialDebug_) Serial.println("Temperature no Ready");

            return -404;
        }
        oldTimeGetTemp = millis();
    }
    return DS18b20_sensors.getTempCByIndex(0);
}

*/




#endif  /* DS18B20_H */
