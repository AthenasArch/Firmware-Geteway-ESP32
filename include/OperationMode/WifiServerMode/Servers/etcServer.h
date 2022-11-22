#ifndef ETC_SERVER_H_
#define ETC_SERVER_H_

#include <Arduino.h>
#include "Database/Structures/systemStatus.h"

#define GATEWAY_ETC_ID_ADDR "ETC0001"

void etcServer_getServer(String *serverBuff, String *postDataBuff);
void etcServer_getPayload(SystemStatus* systemStatus, String *buff);

#endif /* ETC_SERVER_H_ */