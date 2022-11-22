#include "Gateway/gatewayMode.h"
#include "modules/eeprom/MAP_FLASH.h"
#include "OperationMode/WifiServerMode/ServerComm.h"
#include "OperationMode/ApMode/apMode.h"
#include "Gateway/gatewayStatus.h"
#include "System/system.h"

#define CONNECT_WIFI_TIMER_CONNECTION 1500
#define CONNECT_WIFI_QTTY_ATTEMPTS 10

// set this to the number of milliseconds delay
// this is 30 seconds
#define TIME_SEND_DATA_SERVER 30000

#define GATEWAY_MODE_DEBUG_ENABLE // descomente esta linha para habilitar o debug. 
#ifdef GATEWAY_MODE_DEBUG_ENABLE
  #define GATEWAY_MODE_DEBUG_PRINT(...) { Serial.print(__VA_ARGS__); }
  #define GATEWAY_MODE_DEBUG_PRINTLN(...) { Serial.println(__VA_ARGS__); }
#else
  #define GATEWAY_MODE_DEBUG_PRINT(...) {}
  #define GATEWAY_MODE_DEBUG_PRINTLN(...) {}
#endif


/**
 * @brief Inicializa o modo de operacao.
 *      - Se ja foi gravado na eeprom a SSID e PASS, entao entra em modo server.
 *      - Caso contrario, entra em modo AP.
 * 
 * @par void
 * 
 * @return 
 */
void gatewayMode_init(SystemStatus* systemStatus){

    static unsigned long timerTryConnect=0;
    NetApConf netApConf;
    
    uint8_t buff_SSID[FLASH_SSID_LEN]; 
	uint8_t buff_PASS[FLASH_PASS_LEN];
    uint8_t buff_TimeSendData[FLASH_SEND_TIME_LEN];
	
    uint8_t tryToConnectWifi=0;

    netApConf.ssid = buff_SSID;
    netApConf.pass = buff_PASS;
    netApConf.timeSendData = buff_TimeSendData;

    gatewayStatus_initialize();

    GATEWAY_MODE_DEBUG_PRINTLN("HTTP server started");
	
	// se houver dados para carregar, entao carrega
	if(apMode_verifyNetworkConf(&netApConf)==EXIT_SUCCESS){

		system_printCharBuff("Conecta na rede: ", buff_SSID, FLASH_SSID_LEN);
        system_printCharBuff("Conecta na Senha: ", buff_PASS, FLASH_PASS_LEN);
        system_printCharBuff("Tempo de envio: ", buff_TimeSendData, FLASH_SEND_TIME_LEN);

		WiFi.begin((char*)buff_SSID, (char*)buff_PASS); 

        // ajusta o tempo de envio das informacoes para o servidor
        systemStatus->network.TIME_SEND_PACK = atol((const char*)buff_TimeSendData);
        if(systemStatus->network.TIME_SEND_PACK < 10){
            systemStatus->network.TIME_SEND_PACK = 30000;
        } else {
            systemStatus->network.TIME_SEND_PACK *= 1000;
        }

        systemStatus->network.status = GATEWAY_TRY_CONNECT_MODEM; 
        gatewayStatus_ledStatus(systemStatus, BLK_LED_STATUS_OFF);

		while (WiFi.status() != WL_CONNECTED) { //Check for the connection
			
            if((millis()-timerTryConnect)>CONNECT_WIFI_TIMER_CONNECTION){
                timerTryConnect=millis();
                GATEWAY_MODE_DEBUG_PRINT(systemStatus->network.TIME_SEND_PACK);
                GATEWAY_MODE_DEBUG_PRINTLN(" - Try to Connect WiFi...");
                tryToConnectWifi++;
            }

			if(tryToConnectWifi<CONNECT_WIFI_QTTY_ATTEMPTS){
				system_wdtReset(); // alimenta wdt
			}else{
                systemStatus->network.status = GATEWAY_TRY_CONNECT_MODEM; 
                gatewayStatus_ledStatus(systemStatus, BLK_LED_STATUS_ON);
				// reseta o UC
			}
		}

        systemStatus->network.status = GATEWAY_MODEM_CONNECTED; 
		gatewayStatus_ledStatus(systemStatus, BLK_LED_STATUS_OFF);
		GATEWAY_MODE_DEBUG_PRINTLN("Connected to the WiFi network");

	}else{ // Se nao, entra em modo AP.
        apMode_initialize();
        systemStatus->network.status = GATEWAY_AP_MODE_START; 
		gatewayStatus_ledStatus(systemStatus, BLK_LED_STATUS_OFF);
		GATEWAY_MODE_DEBUG_PRINTLN("RUN AP MODE...");
		apMode_run();
	}
}

/**
 * @brief 
 * 
 * @param systemStatus 
 */
void gatewayMode_run(SystemStatus* systemStatus){

    static unsigned long timerSendDataServer = 0;

	if((millis()-timerSendDataServer) > systemStatus->network.TIME_SEND_PACK){

		timerSendDataServer = millis();

        GATEWAY_MODE_DEBUG_PRINT(F("\r\nQTDE FALHAS: "));
        GATEWAY_MODE_DEBUG_PRINT(systemStatus->network.netServer.cntFailConnectServer);

		if(serverComm_connectServerAndSendData(systemStatus)==EXIT_FAILURE){
            systemStatus->network.status = GATEWAY_ERROR_SEND_POST; 
            gatewayStatus_ledStatus(systemStatus, BLK_LED_STATUS_OFF);
            GATEWAY_MODE_DEBUG_PRINT(F("\r\nFail "));
            systemStatus->network.netServer.cntFailConnectServer++;
        }else{
            systemStatus->network.status = GATEWAY_SENDING_POST_OK; 
            gatewayStatus_ledStatus(systemStatus, BLK_LED_STATUS_OFF);
            GATEWAY_MODE_DEBUG_PRINT(F("\r\nPass "));
            systemStatus->network.netServer.cntFailConnectServer=0;
        }	
	}

    if(systemStatus->network.netServer.cntFailConnectServer>RST_QTTY_TRY_CONNECT_SERVER){
        GATEWAY_MODE_DEBUG_PRINT(F("RESETANDO POR FALHA NA COMUNICACAO COM O SERVER..."));
        system_forceRestart();
    }
}