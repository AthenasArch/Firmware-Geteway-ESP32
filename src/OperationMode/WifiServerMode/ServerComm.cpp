#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "Hardware/hardware.h"
#include "Gateway/gatewayStatus.h"
#include "OperationMode/WifiServerMode/serverConstant.h"
#include "OperationMode/WifiServerMode/ServerComm.h"
#include "OperationMode/WifiServerMode/Servers/atmServer.h"
#include "OperationMode/WifiServerMode/Servers/tagoServer.h"
#include "OperationMode/WifiServerMode/Servers/etcServer.h"

#define SERVER_COMM_DEBUG_ENABLE // descomente esta linha para habilitar o debug. 
#ifdef SERVER_COMM_DEBUG_ENABLE
  #define SERVER_COMM_DEBUG_PRINT(...) { Serial.print(__VA_ARGS__); }
  #define SERVER_COMM_DEBUG_PRINTLN(...) { Serial.println(__VA_ARGS__); }
#else
  #define SERVER_COMM_DEBUG_PRINT(...) {}
  #define SERVER_COMM_DEBUG_PRINTLN(...) {}
#endif

#define USE_TAGO_SERVER 1

void serverComm_getServer(String *serverBuff, String *postDataBuff);
void serverComm_setInfoToSend(SystemStatus* systemStatus, String *buff);
void serverComm_getPayload(SystemStatus* systemStatus, String *buff);

WiFiClient client;


/**
 * @brief
 * 
 * @param systemStatus
 * 
 * @return (EXIT_FAILURE or SUCCESS)
 */
uint8_t serverComm_connectServerAndSendData(SystemStatus* systemStatus){

    String serverStr = "";
	String post_data="";

    serverComm_getPayload(systemStatus, &post_data);

    SERVER_COMM_DEBUG_PRINT("\r\nDados post:");
    SERVER_COMM_DEBUG_PRINTLN(post_data);

	SERVER_COMM_DEBUG_PRINTLN(F("connecting..."));

	if(client.connect(serverName, SERVER_PORT) == 1) {

        systemStatus->network.status = GATEWAY_CONNECT_SERVER_OK; 
        gatewayStatus_ledStatus(systemStatus, BLK_LED_STATUS_OFF);
		SERVER_COMM_DEBUG_PRINTLN(F("connected"));

        serverComm_getServer(&serverStr, &post_data);

        client.println(serverStr);

        SERVER_COMM_DEBUG_PRINTLN("Pagina: \r\n\r\n");
        SERVER_COMM_DEBUG_PRINTLN(serverStr);
        SERVER_COMM_DEBUG_PRINTLN("\r\n\r\n");
        
        unsigned long timeout = millis();

        while (client.available() == SERVER_CLIENT_DISCONNECTED){
            if(millis() - timeout > TIMEOUT_SERVER_WAIT_RESPONSE){
                SERVER_COMM_DEBUG_PRINTLN("\t>>> Timeout !\r\n");
                client.stop();
                return EXIT_FAILURE;
            }
        }

        while (client.available()){
            String resposta = client.readStringUntil('\r');
            SERVER_COMM_DEBUG_PRINT("\r\n-->SERVER RESP: ");
            SERVER_COMM_DEBUG_PRINTLN(resposta);
        }
        client.stop();
		// send the body (variables)
		//client.print(thisData);
	}else{
		SERVER_COMM_DEBUG_PRINTLN(F("failed"));
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

/**
 * @brief seta os detalhes do servidor a ser enviado os dados.
 * 
 * @param
 * 
 * @return 
 **/
void serverComm_getServer(String *serverBuff, String *postDataBuff){
#if defined(USE_SERVER_ATM) 
    atmServer_getServer(serverBuff, postDataBuff);
#elif defined(USE_SERVER_TAGO)
    tagoServer_getServer(serverBuff, postDataBuff);
#elif defined(USE_SERVER_ETC)
    etcServer_getServer(serverBuff, postDataBuff);
#else
    DEFINA_UM_SERVIDOR
#endif 
}

/**
 * @brief
 * 
 * @param
 * 
 * @return 
 **/
void serverComm_getPayload(SystemStatus* systemStatus, String *buff){    
#if defined(USE_SERVER_ATM) 
    atmServer_getPayload(systemStatus, buff);
#elif defined(USE_SERVER_TAGO)
    tagoServer_getPayload(systemStatus, buff);
#elif defined(USE_SERVER_ETC)
    etcServer_getPayload(systemStatus, buff);
#else
    DEFINA_UM_SERVIDOR
#endif 
}