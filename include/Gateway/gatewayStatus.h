#ifndef GETEWAY_STATUS_H_
#define GETEWAY_STATUS_H_

#include <Arduino.h>
#include "Peripheral/LedRgb/ledRgb.h"
#include "Database/Structures/systemStatus.h"


void gatewayStatus_initialize(void);
char gatewayStatus_ledStatus(SystemStatus* systemStatus, uint8_t blinkError);

#endif /* GETEWAY_STATUS_H_ */