#ifndef GETEWAY_H_
#define GETEWAY_H_

#include <Arduino.h>
#include "Database/Structures/systemStatus.h"

void gateway_init(SystemStatus* systemStatus);
void gateway_run(SystemStatus* systemStatus);

#endif /* GETEWAY_H_ */