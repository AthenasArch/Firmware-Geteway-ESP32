#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "System/system.h"
#include "OperationMode/ApMode/apMode.h"
#include "Modules/eeprom/MAP_FLASH.h"
#include "Modules/eeprom/eepromArch.h"

// https://circuits4you.com/2019/03/20/esp8266-receive-post-get-request-data-from-website/

#define AP_MODE_DEBUG_ENABLE // descomente esta linha para habilitar o debug. 
#ifdef AP_MODE_DEBUG_ENABLE
  #define AP_MODE_DEBUG_PRINT(...) { Serial.print(__VA_ARGS__); }
  #define AP_MODE_DEBUG_PRINTLN(...) { Serial.println(__VA_ARGS__); }
#else
  #define AP_MODE_DEBUG_PRINT(...) {}
  #define AP_MODE_DEBUG_PRINTLN(...) {}
#endif

 /* Put IP Address details */
IPAddress AP_MODE_LOCAL_IP(192,168,1,1);
IPAddress AP_MODE_GETEWAY(192,168,1,1);
IPAddress AP_MODE_SUBNET(255,255,255,0);

WebServer server(80);

//SSID and Password of your WiFi router
#define AP_MODE_SSID "GATEWAY_ESP32"
#define AP_MODE_PASS "123456789"
// const char* ssid = "MONITOR_ESP";
// const char* password = "12345678";

void htmlTextNewLine(String *buff);
void htmlTextInformation(String nameInfo, String info, String *buff);
 

//**********************************************************************************************
//
//                                          GLOBAL FUNCTIONS
//
//**********************************************************************************************

/**
  * @method:
  * 
  * @param:
  * 
  * @return:
  *  
  **/
void apMode_initialize(void){

    AP_MODE_DEBUG_PRINTLN("apMode_initialize()");

    AP_MODE_DEBUG_PRINT("AP_MODE_SSID: ");
    AP_MODE_DEBUG_PRINTLN(AP_MODE_SSID);

    WiFi.persistent(false);
    WiFi.softAP(AP_MODE_SSID, AP_MODE_PASS);
	WiFi.softAPConfig(AP_MODE_LOCAL_IP, AP_MODE_GETEWAY, AP_MODE_SUBNET);
	
    delay(100);

	server.on("/", apMode_handleRoot);      //Which routine to handle at root location
	server.on("/action_page", apMode_handleForm); //form action is handled here

	server.begin();                  //Start server
}

/**
 * @brief 
 * 
 */
void apMode_run(void){

    AP_MODE_DEBUG_PRINTLN("apMode_run");
    
    while(true){
        system_wdtReset(); // alimenta wdt
        server.handleClient();          //Handle client requests
    }
}


/**
 * @brief Verifica se existe uma rede e senha ja salva na memoria ... 
 * 
 * @param netApConf
 * 
 * @return 
 */
uint8_t apMode_verifyNetworkConf(NetApConf *netApConf){

    uint8_t result=EXIT_FAILURE;

    // le se existe SSID e PASS gravados na eeprom.
    AP_MODE_DEBUG_PRINT("ADDR SSID: ");
    AP_MODE_DEBUG_PRINTLN(eeprmArch_readByte(FLASH_ADDR_SSID_STATUS));
    AP_MODE_DEBUG_PRINT("ADDR PASS: ");
    AP_MODE_DEBUG_PRINTLN(eeprmArch_readByte(FLASH_ADDR_PASS_STATUS));

    if(eeprmArch_readByte(FLASH_ADDR_SSID_STATUS)==EEPROM_BUSY_ADDR){
        if(eeprmArch_readByte(FLASH_ADDR_PASS_STATUS)==EEPROM_BUSY_ADDR){
            result=EXIT_SUCCESS;
        }
    }

    // se houver dados para cerregar, entao carrega...
    if(result==EXIT_SUCCESS){
        apMode_loadNetworkConf(netApConf);
    }

    return result;
}

/**
 * @brief Salva na memoria as novas credencias da rede a se conectar 
 * 
 * @param newNet_SSID - 
 * @param newNet_PASS -
 * 
 * @return 
 **/
uint8_t apMode_saveNetworkConf(String *newNet_SSID, String *newNet_PASS, String *newNetTime){

    uint8_t result=EXIT_FAILURE;

    AP_MODE_DEBUG_PRINTLN("SALVA REGISTRO SSID E PASS...");
    eeprmArch_writeByte(FLASH_ADDR_SSID_STATUS, EEPROM_BUSY_ADDR);
    eeprmArch_writeByte(FLASH_ADDR_PASS_STATUS, EEPROM_BUSY_ADDR);
    eeprmArch_writeByte(FLASH_ADDR_TIME_SEND_STATUS, EEPROM_BUSY_ADDR);

    AP_MODE_DEBUG_PRINT("Saving SSID: ");
    eeprmArch_writeString(FLASH_ADDR_SSID_INI, newNet_SSID, FLASH_ADDR_SSID_END);

    AP_MODE_DEBUG_PRINT("\r\r\n\nSaving PASS: ");
    eeprmArch_writeString(FLASH_ADDR_PASS_INI, newNet_PASS, FLASH_ADDR_PASS_END);

    AP_MODE_DEBUG_PRINT("\r\r\n\nSaving SEND TIME: ");
    eeprmArch_writeString(FLASH_ADDR_TIME_SEND_INI, newNetTime, FLASH_ADDR_TIME_SEND_END);

    return result;
}

/**
 * @brief carrega da memoria credencias da rede a se conectar 
 * 
 * @param newNet_SSID - 
 * @param newNet_PASS -
 * 
 * @return 
 */
uint8_t apMode_loadNetworkConf(NetApConf *netApConf){
    
    uint8_t result=EXIT_FAILURE;

    eeprmArch_readBuff(FLASH_ADDR_SSID_INI, netApConf->ssid);
    system_printCharBuff("CARREGOU SSID: ", netApConf->ssid, FLASH_SSID_LEN);

    eeprmArch_readBuff(FLASH_ADDR_PASS_INI, netApConf->pass);
    system_printCharBuff("CARREGOU PASS: ", netApConf->pass, FLASH_PASS_LEN);

    eeprmArch_readBuff(FLASH_ADDR_TIME_SEND_INI, netApConf->timeSendData);
    system_printCharBuff("CARREGOU TIME SEND: ", netApConf->timeSendData, FLASH_SEND_TIME_LEN);

    return result;
}



/**
 * @brief This routine is executed when you open its IP in browser 
 * 
 */
void apMode_handleRoot(void) {
    
    String s; //Read HTML contents

    s = HTML_PAGE_MAIN_HEADER;
    s += HTML_PAGE_MAIN_TITLE;
    htmlTextNewLine(&s);
    htmlTextInformation("- DEVICE INFORMATION -", "", &s);
    htmlTextInformation("MAC: ", WiFi.macAddress(), &s);
    htmlTextNewLine(&s);
    s += HTML_PAGE_MAIN_INFORMATION;
    s += HTML_PAGE_MAIN_INTERACTION;

    server.send(200, "text/html", s); //Send web page
}

/**
 * @brief This routine is executed when you press submit
 * 
 */
void apMode_handleForm(void) {

    String newNetSSID = server.arg("net_ssid"); 
    String newNetPASS = server.arg("net_pass"); 
    String newNetSendTime = server.arg("timeSend"); 

    AP_MODE_DEBUG_PRINT("Nome da rede:");
    AP_MODE_DEBUG_PRINTLN(newNetSSID);

    AP_MODE_DEBUG_PRINT("Senha da rede:");
    AP_MODE_DEBUG_PRINTLN(newNetPASS);

    // verifica se o tempo NAO esta vazio
    if(!newNetSendTime.isEmpty()) {
        // verifica se o tempo e menor que 10
        if(newNetSendTime.toInt() > 10) {
            AP_MODE_DEBUG_PRINT("Tempo de envio: ");
            AP_MODE_DEBUG_PRINTLN(newNetSendTime);
        } else {
            AP_MODE_DEBUG_PRINT("Time send invalid!");
            AP_MODE_DEBUG_PRINTLN(newNetSendTime);
            newNetSendTime = "30";
        }
    } else {
        AP_MODE_DEBUG_PRINT("Time send is Empty");
        AP_MODE_DEBUG_PRINTLN(newNetSendTime);
        newNetSendTime = "30";
    }
    AP_MODE_DEBUG_PRINT("\r\n");

    String s = "<a href='/'> Go Back </a>";
    server.send(200, "text/html", s); //Send web page

    // salva os dados na memoria.
    apMode_saveNetworkConf(&newNetSSID, &newNetPASS, &newNetSendTime);
    delay(500);
    ESP.restart();
}


//**********************************************************************************************
//
//                                          LOCAL FUNCTIONS
//
//**********************************************************************************************

/**
 * @brief 
 * 
 * @param nameInfo 
 * @param info 
 * @param buff 
 */
void htmlTextInformation(String nameInfo, String info, String *buff){

    /** @brief texto adicional*/
    *buff += HTML_PAGE_ADITIONAL_TEXT_INI;
    *buff += nameInfo;
    *buff += info;
    *buff += HTML_PAGE_ADITIONAL_TEXT_END;
}

/**
 * @brief 
 * 
 * @param buff 
 */
void htmlTextNewLine(String *buff){
    *buff += "<p></p>;";
}