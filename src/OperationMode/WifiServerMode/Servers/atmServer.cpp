#include "OperationMode/WifiServerMode/Servers/atmServer.h"
#include "OperationMode/WifiServerMode/serverConstant.h"

#if defined(USE_SERVER_ATM)

// site oficial.
// https://atm-iot-app.herokuapp.com/app/dashboard

// Dados brutos.
// https://atm-exp-api.herokuapp.com/events

// Apenas Dados.
// https://atm-iot-app.herokuapp.com/events

#define PROTOCOL_MSG 2

void atmServer_getPayloadInfo(SystemStatus* systemStatus, String *buff);
void atmServer_getPayloadMsg1(SystemStatus* systemStatus, String *buff);
void atmServer_getPayloadMsg2(SystemStatus* systemStatus, String *buff);

/**
 * @brief
 * 
 * @param
 * 
 * @return 
 **/
void atmServer_getServer(String *serverBuff, String *postDataBuff){

    *serverBuff = "POST /events HTTP/1.1\r\n";
    *serverBuff += "Host: " + String(serverName) + "\r\n";
    *serverBuff += "Content-Type: application/json\r\n";
    *serverBuff += "Content-Length: " + String(postDataBuff->length()) + "\r\n"; 
    *serverBuff += "\r\n";
    *serverBuff += *postDataBuff;
}

/**
 * @brief
 * 
 * @param
 * 
 * @return 
 **/
void atmServer_getPayloadInfo(SystemStatus* systemStatus, String *buff){


    String msgCode="";

    msgCode = "002";

    *buff = "{";
    *buff += "\"date\":\"2020-08-31T23:31:37.072Z\",";
    *buff += "\"device\":\"" + String(GATEWAY_ID_ADDR) + "\",";
    *buff += "\"message\":\"" + msgCode + "\",";
    // *buff = "{";
    // *buff += "\"gateway\":\"" + String(GATEWAY_ID_ADDR) + "\",";
    // *buff += "\"date\":\"2020-08-31T23:31:37.072Z\",";
    // *buff += "\"lat\":-25.3819539,";
    // *buff += "\"lon\":-49.3246685,";
    // *buff += "\"code\":\"001\",";
}

/**
 * @brief
 * 
 * @param
 * 
 * @return 
 **/
void atmServer_getPayload(SystemStatus* systemStatus, String *buff){

    atmServer_getPayloadInfo(systemStatus, buff);
    
    *buff += "\"data\":[";

    atmServer_getPayloadMsg2(systemStatus, buff);

    buff->setCharAt((buff->length()-1), ']'); 
    *buff += "}";
}

void atmServer_getPayloadMsg1(SystemStatus* systemStatus, String *buff){
    
    *buff += systemStatus->nobreakMono.inpA.VRMS + ","; // v in
    *buff += systemStatus->nobreakMono.outA.VRMS + ",";
    *buff += systemStatus->nobreakMono.bat.VDC + ",";
    // Corrente
    *buff += systemStatus->nobreakMono.inpA.IRMS + ",";
    *buff += systemStatus->nobreakMono.outA.IRMS + ",";
    *buff += systemStatus->nobreakMono.bat.ICHARG + ",";
    // Potencia
    *buff += systemStatus->nobreakMono.inpA.POT + ",";
    *buff += systemStatus->nobreakMono.outA.POT + ",";
    *buff += systemStatus->nobreakMono.bat.IDISCHARG + ",";
    // Frequencia
    *buff += systemStatus->nobreakMono.inpA.FREQ + ",";
    *buff += systemStatus->nobreakMono.outA.FREQ + ",";
    *buff += systemStatus->nobreakMono.bat.PCHARG + ",";
    // More Info
    *buff += systemStatus->nobreakMono.info.NFAULTS + ",";
    *buff += systemStatus->nobreakMono.info.PREACTIVE + ",";
    *buff += systemStatus->nobreakMono.info.PACTIVE + ",";

    *buff += "25.6,";
    *buff += "27.2,";
}

void atmServer_getPayloadMsg2(SystemStatus* systemStatus, String *buff){

    *buff += systemStatus->nobreakMono.inpA.VRMS + ","; // 0
    *buff += systemStatus->nobreakMono.outA.VRMS + ","; // 1
    *buff += systemStatus->nobreakMono.bat.VDC + ","; // 2
    // Corrente
    *buff += systemStatus->nobreakMono.inpA.IRMS + ","; // 3
    *buff += systemStatus->nobreakMono.outA.IRMS + ","; // 4
    *buff += systemStatus->nobreakMono.bat.ICHARG + ","; // 5
    // Potencia
    *buff += systemStatus->nobreakMono.inpA.POT + ","; // 6
    *buff += systemStatus->nobreakMono.outA.POT + ","; // 7
    *buff += systemStatus->nobreakMono.bat.IDISCHARG + ","; // 8
    // Frequencia
    *buff += systemStatus->nobreakMono.inpA.FREQ + ","; // 9
    *buff += systemStatus->nobreakMono.outA.FREQ + ","; // 10
    *buff += systemStatus->nobreakMono.bat.PCHARG + ","; // 11
    // More Info
    *buff += systemStatus->nobreakMono.info.NFAULTS + ","; // 12 
    // *buff += systemStatus->nobreakMono.info.PACTIVE + ","; // 13
    *buff += "0.03,"; // 13
    *buff += systemStatus->nobreakMono.info.PREACTIVE + ","; // 14

    *buff += systemStatus->nobreakMono.info.AUTONOMIA + ","; // 15
    *buff += "4.03,";
    *buff += "0,";

    *buff += systemStatus->nobreakMono.info.NB_TEMPERATURE + ",";
    *buff += systemStatus->nobreakMono.info.ROOM_TEMPERATURE + ",";
    // *buff += "25.0,";
}

#endif /* */