#ifndef AD_ARCH_H_
#define AD_ARCH_H_

#include <Arduino.h>

unsigned int adArch_simpleAverage(const unsigned char pinChannalAd, const unsigned int qttySamples);
float adArch_convertToVoltage(const unsigned int averageAd);

#endif /* AD_ARCH_H_ */
