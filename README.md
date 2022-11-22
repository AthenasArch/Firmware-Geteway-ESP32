# Firmware-Geteway-ESP32

/**
 * @brief Arquivo main do firmware.
 * @name 
 * @version | 4.0
 * @date    | 22/11/2022     
 * @github  | First update: 20/06/2020.
 * @author  | leonardohilgemberg@gmail.com  | laonardo Hilgemberg Lopes |
 * @file    | main.h
 * @note    | fone WPP (41)99661-6761
 * @warning | 
 **/

- Estou disponibilizando de forma gratuida este firmware. 

- Para utilizar este firmware, será necesário ao menos um botão conectado 
ao pino 15 - (PIN_BUTTON_CLR_EEPROM 15), para gravar os dados 
da flash do ESP32. (Pull-Down).

- o sistema inicializa verificando a existencia de uma rede salva.
Se não existe uma rede salva ou se os valores da memoria estão diferentes do 
que deveria estar, então a placa Zera os endereços utilizaveis da Flahs.

- Após zerar a memoria, salvar os bytes de verificação da memoria a placa 
tenta entrar no modo ponto de acesso (AP).

- Se entrar no modo AP com sucesso, irá aparecer em uma rede Wi-fi sua 
com as seguintes id:

    //O SSID e a senha de acesso sao:
    
        SSID = GATEWAY_ESP32
    
        PASS = 123456789

Após se conectar na placa ESP, va a qualquer browser e digite o seguinte ip 
na barra de pesquisa: 
    
    AP_MODE_LOCAL_IP = 192.168.1.1

    // nao é necessário digitar a porta.
    Porta so servidor = 80

Se tudo der certo, irá aparecer uma pagina Web solicitando os dados de onde sua placa ESP32 irá se conetar;
Apenas digite o SSID, PASS e o tempo de envio de pacotes e pronto.

Agora é só você trabalhar nos dados do seu servidor para receber os dados da placa esp32 com o metodo POST.


Hardware:

    PIN_LED_RGB_RED		19
    PIN_LED_RGB_GREEN 	18
    PIN_LED_RGB_BLUE	5

    // utilizado com pull-Down - placa geteway
    PIN_BUTTON_CLR_EEPROM 15

