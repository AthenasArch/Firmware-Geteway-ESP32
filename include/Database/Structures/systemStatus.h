#ifndef SYSTEM_STATUS_H_
#define SYSTEM_STATUS_H_

#include <Arduino.h>
#include "systemStructures.h"

typedef struct SYSTEM_STATUS {
	
    DbUcStatus ucStatus;
    DbAlarm currAlarm;
    NetworkStatus network;
    // DbTennisMachineStatus machineStatus; //
} SystemStatus;

void systemStatus_initialize(SystemStatus* systemStatus);
SystemStatus* systemSystem_getSystemStatus();

#endif /* SYSTEM_STATUS_H_ */