#include "OperationMode/WifiServerMode/Servers/etcServer.h"
#include "OperationMode/WifiServerMode/serverConstant.h"

void etcServer_payloadFmt(String*payload, String var, String value);


// User-Agent: insomnia/2022.6.0
// Content-Type: application/json
// Accept: /
// Content-Length: 29

void etcServer_getServer(String *serverBuff, String *postDataBuff){
    *serverBuff = "POST /gadgets HTTP/1.1\r\n";
    *serverBuff += "Host: " + String(serverName) + "\r\n";
    *serverBuff += "Content-Type: application/json\r\n";
    *serverBuff += "Accept: /\r\n";
    *serverBuff += "Content-Length: " + String(postDataBuff->length()) + "\r\n"; 
    *serverBuff += "\r\n";
    *serverBuff += *postDataBuff;
}

/**
 * @brief
 * 
 * @note nao precisa retirar a virgula do pacote, porque ele esta 
 * programado para montar o ultimo pacote sem ela.
 * 
 * @param
 * 
 * @return 
 **/
void etcServer_payloadFmt(String*payload, String var, String value){

    // *payload += "{\"sn\":\"" + String(GATEWAY_ID_ADDR) + "\",\"cnt\":\"" + value  + "\"}";
    *payload += "\"sn\":\"" + String(GATEWAY_ETC_ID_ADDR) + "\",\"cnt\":" + value  + ",";
    // *payload += "{\"sn\":\"teste\",\"cnt\":2922}";
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
void etcServer_getPayload(SystemStatus* systemStatus, String *buff){

    static uint8_t cntPack=0;
    *buff = "{";
    etcServer_payloadFmt(buff, "cnt", String(cntPack++));
    buff->setCharAt((buff->length()-1), '}'); 
}


