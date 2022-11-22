#ifndef POST_H_
#define POST_H_

#include <Arduino.h>
#include "Database/Structures/systemStatus.h"

#define TIMEOUT_SERVER_WAIT_RESPONSE 5000

#define SERVER_CLIENT_DISCONNECTED 0 
#define SERVER_CLIENT_CONNECTED 1

uint8_t serverComm_connectServerAndSendData(SystemStatus* systemStatus);

#endif /* POST_H_ */