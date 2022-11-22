#ifndef ATM_SERVER_H_
#define ATM_SERVER_H_

#include <Arduino.h>
#include "Database/Structures/systemStatus.h"

#define GATEWAY_ID_ADDR "FA15DFCCA101"

void atmServer_getServer(String *serverBuff, String *postDataBuff);
void atmServer_getPayload(SystemStatus* systemStatus, String *buff);

#endif /* ATM_SERVER_H_ */