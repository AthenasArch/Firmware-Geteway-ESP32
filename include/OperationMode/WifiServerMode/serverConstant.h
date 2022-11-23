#ifndef SERVER_CONSTANT_H_
#define SERVER_CONSTANT_H_

#include <Arduino.h>

#define USE_SERVER_ETC
// #define USE_SERVER_TAGO
// #define USE_SERVER_ATM

#if defined(USE_SERVER_ATM) 
    const char serverName[] = "atm-exp-api.herokuapp.com";
    #define SERVER_PORT 80 // change to your server's port
#elif defined(USE_SERVER_TAGO)
    const char serverName[] = "api.tago.io";  //Change to your server domain
    #define SERVER_PORT 80 // change to your server's port
#elif defined(USE_SERVER_ETC)
    const char serverName[] = "easytennis-api.herokuapp.com";  //Change to your server domain
    #define SERVER_PORT 80 // change to your server's port
#else
    DEFINA_UM_SERVIDOR
#endif

#endif /* SERVER_CONSTANT_H_ */