#ifndef GETEWAY_MODE_H_
#define GETEWAY_MODE_H_

#include <Arduino.h>
#include "Database/Structures/systemStatus.h"

void gatewayMode_init(SystemStatus* systemStatus);
void gatewayMode_run(SystemStatus* systemStatus);

#endif /* GETEWAY_MODE_H_ */