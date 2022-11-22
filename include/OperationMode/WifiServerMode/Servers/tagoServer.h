#ifndef TAGO_SERVER_H_
#define TAGO_SERVER_H_

#include <Arduino.h>
#include "Database/Structures/systemStatus.h"

// Token da athenasArch na tago
const String token = "74a775ca-e2c3-4856-ac59-424405dd16cf";

void tagoServer_getServer(String *serverBuff, String *postDataBuff);
void tagoServer_getPayload(SystemStatus* systemStatus, String *buff);

#endif /* TAGO_SERVER_H_ */ 