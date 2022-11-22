#ifndef SYSTEM_STRUCTURES_H_
#define SYSTEM_STRUCTURES_H_

#include <Arduino.h>
#include "Database/Structures/systemConstants.h"

typedef enum DB_ALARM{
    ERROR_NONE_MACHINE_OK = 0,
    ERROR_GENERIC = 1
} DbAlarm;

typedef struct DB_UC_STATUS{
    uint8_t cntTimeMillis;
} DbUcStatus;

// ------------------------------------------------------------------------------
//
//  Structs network.
//
// ------------------------------------------------------------------------------

typedef struct NET_ACCESS_POINT{

}NetAccessPoint;

typedef struct NET_SERVER{
    uint8_t cntFailConnectServer;
}NetServer;

typedef enum DB_GETWAY_STATUS{
    GATEWAY_AP_MODE_START       = 0,
    GATEWAY_TRY_CONNECT_MODEM   = 1,
    // GETEWAY_ERROR_CONNECT_MODEM,
    GATEWAY_MODEM_CONNECTED     = 2,
    GATEWAY_CONNECT_SERVER_OK   = 3,
    GATEWAY_SENDING_POST_OK     = 4,
    GATEWAY_ERROR_SEND_POST     = 5
}DbGetwayStatus;

typedef struct NETWORK_STATUS{
    NetAccessPoint netAccessPoint;
    NetServer netServer;
    DbGetwayStatus status;
    unsigned long TIME_SEND_PACK;
}NetworkStatus;

#endif /* SYSTEM_STRUCTURES_H_ */