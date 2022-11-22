#include <Arduino.h>
#include "Modules/ADC/adArch.h"

unsigned int adArch_simpleAverage(const unsigned char pinChannalAd, const unsigned int qttySamples){
	unsigned int idx=0;
	uint64_t calcAverage=0;
	for (idx=0; idx<qttySamples; idx++){
		calcAverage+=analogRead(pinChannalAd);
        delayMicroseconds(1);
	}
	calcAverage/=idx;
    return calcAverage;
}

float adArch_convertToVoltage(const unsigned int averageAd){
    float result = (float)((10+(10*averageAd))/131.0);
    return result;
}
