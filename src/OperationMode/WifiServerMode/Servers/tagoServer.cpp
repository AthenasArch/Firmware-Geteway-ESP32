#include "OperationMode/WifiServerMode/Servers/tagoServer.h"
#include "OperationMode/WifiServerMode/serverConstant.h"

void tagoServer_payloadFmt(String*payload, String var, String value);

void tagoServer_getServer(String *serverBuff, String *postDataBuff){
    *serverBuff = "POST /data? HTTP/1.1\n";
    *serverBuff += "Host: " + String(serverName) + "\n";
    *serverBuff += "Device-Token: " + token + "\n";
    *serverBuff += "_ssl: false\n";
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
void tagoServer_payloadFmt(String*payload, String var, String value){

    *payload += "{\"variable\":\"" + var + "\",\"value\":" + value  + "},";
    // Serial.print("Var: ");
    // Serial.print(var);
    // Serial.print("\t------value: ");
    // Serial.println(value);
}


/**
 * @brief
 * 
 * @param
 * 
 * @return 
 **/
void tagoServer_getPayload(SystemStatus* systemStatus, String *buff){

    static uint8_t cntPack=0;
    *buff = "[";
    tagoServer_payloadFmt(buff, "CNT", String(cntPack++));
    buff->setCharAt((buff->length()-1), ']'); 
}


