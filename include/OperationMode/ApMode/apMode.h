#ifndef AP_MODE_H_
#define AP_MODE_H_

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// ip para se conectar a placa ESP
//
//  192.168.1.1

/**
 * @brief: Edicao do codigo HTML em: https://htmleditor.tools/
 * 
 * 
 */

/*

    No editor de html, e consumido automaticamente o cabecalho, entao colar antes:

<!DOCTYPE html>
<html>
<head>
<style>
body { background-color: #92a8d1; }
</style>
</head>
<body>
</body>
</html>

*/

const char HTML_PAGE_MAIN_HEADER[] PROGMEM = R"(<!DOCTYPE html>
    <html>
        <head>
            <style>
                body { background-color: #92a8d1; }
            </style>
        </head>
        <body>

        </body>
    </html>)";

const char HTML_PAGE_MAIN_TITLE[] PROGMEM = R"(<h3 style="text-align: center;">AthenasArch - Leonardo Hilgemberg</h3>)";

const char HTML_PAGE_ADITIONAL_TEXT_INI[] PROGMEM = R"(
    <p style="text-align: center;">
)";
const char HTML_PAGE_ADITIONAL_TEXT_END[] PROGMEM = R"(
    </p>
)";

const char HTML_PAGE_MAIN_INFORMATION[] PROGMEM = R"(
    <p style="text-align: center;">Digite os dados da rede a se conectar</p>
    <p></p>
)";

const char HTML_PAGE_MAIN_INTERACTION[] PROGMEM = R"(
    <form action="/action_page">
    <p style="text-align: center;">NOME DA REDE - SSID</p>
    <p style="text-align: center;">&nbsp; &nbsp;<input type="text" name="net_ssid" value="" /></p>
    <p style="text-align: center;"><br /><br />NOME DA SENHA - PASS</p>
    <p style="text-align: center;"><input type="text" name="net_pass" value="" /></p>
    <p style="text-align: center;"><br /><br />TEMPO DE ENVIO (s)</p>
    <p style="text-align: center;"><input type="text" name="timeSend" value="" /></p>
    <p style="text-align: center;"></p>
    <p style="text-align: center;"><br /> <input type="submit" value="Conectar" /></p>
    </form>
)";



// const char MAIN_page[] PROGMEM = R"(<!DOCTYPE html>
//     <html>
//         <head>
//             <style>
//                 body { background-color: #92a8d1; }
//             </style>
//         </head>
//         <body>

//         </body>
//     </html>

//     <h3 style="text-align: center;">MONITOR</h3>
//     <p style="text-align: center;">Digite os dados da rede a se conectar</p>
//     <p></p>
//     <form action="/action_page">
//     <p style="text-align: center;">NOME DA REDE - SSID</p>
//     <p style="text-align: center;">&nbsp; &nbsp;<input type="text" name="net_ssid" value="" /></p>
//     <p style="text-align: center;"><br /><br />NOME DA SENHA - PASS</p>
//     <p style="text-align: center;"><input type="text" name="net_pass" value="" /></p>
//     <p style="text-align: center;"></p>
//     <p style="text-align: center;"><br /> <input type="submit" value="Conectar" /></p>
//     </form>)";

typedef struct NET_AP_CONF{
    uint8_t *ssid;
    uint8_t *pass;
    uint8_t *timeSendData;
}NetApConf;

void apMode_run(void);
void apMode_initialize(void);
void apMode_handleForm(void);
void apMode_handleRoot(void);

uint8_t apMode_saveNetworkConf(String *newNet_SSID, String *newNet_PASS, String *newNetTime);
uint8_t apMode_loadNetworkConf(NetApConf *netApConf);
uint8_t apMode_verifyNetworkConf(NetApConf *netApConf);

#endif /* AP_MODE_H_ */