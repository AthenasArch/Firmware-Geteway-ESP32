#include <Arduino.h>
#include "System/system.h"

#define SYSTEM_DEBUG_ENABLE // descomente esta linha para habilitar o debug. 
#ifdef SYSTEM_DEBUG_ENABLE
  #define SYSTEM_DEBUG_PRINT(...) { Serial.print(__VA_ARGS__); }
  #define SYSTEM_DEBUG_PRINTLN(...) { Serial.println(__VA_ARGS__); }
#else
  #define SYSTEM_DEBUG_PRINT(...) {}
  #define SYSTEM_DEBUG_PRINTLN(...) {}
#endif

hw_timer_t *timer = NULL; //faz o controle do temporizador (interrupção por tempo)
// #include <avr/wdt.h>


static unsigned long _sysTimeOut=0;
boolean timeOutStart=false;

static unsigned long _sysTimeOut_2=0;
boolean timeOutStart_2=false;

/*
 * Method: Callback: função que o temporizador irá chamar, para reiniciar o ESP32 
 * 
 * Param:
 * 
 * Return: 
 */
void IRAM_ATTR resetModule(){
    ets_printf("(watchdog) reiniciar\n"); //imprime no log
    // esp_restart_noos(); //reinicia o chip
    ESP.restart();
}

void system_forceRestart(void){
    ets_printf("\r\n\t(MANUAL)RESTART\r\r\n\n"); //imprime no log
    // esp_restart_noos(); //reinicia o chip
    ESP.restart();
}

void system_manualWdtInitialize(void){

   //hw_timer_t * timerBegin(uint8_t num, uint16_t divider, bool countUp)
    /*
       num: é a ordem do temporizador. Podemos ter quatro temporizadores, então a ordem pode ser [0,1,2,3].
      divider: É um prescaler (reduz a frequencia por fator). Para fazer um agendador de um segundo, 
      usaremos o divider como 80 (clock principal do ESP32 é 80MHz). Cada instante será T = 1/(80) = 1us
      countUp: True o contador será progressivo
    */
    timer = timerBegin(0, 80, true); //timerID 0, div 80
    //timer, callback, interrupção de borda
    timerAttachInterrupt(timer, &resetModule, true);
    //timer, tempo (us), repetição
    timerAlarmWrite(timer, (8 * WDT_SECOND), true);
    timerAlarmEnable(timer); //habilita a interrupção 
}

void system_initialize(void){
    SYSTEM_DEBUG_PRINTLN("Inicializando Systema");
    delay(TIME_TO_INITIALIZE_SYSTEM); // demora s para inicializar, para garantir q nao va travar o bootloader 
    system_manualWdtInitialize();
    SYSTEM_DEBUG_PRINTLN("Systema iniciado");
    // wdt_enable(WDTO_8S); // WDT habilitado em 8s
    // system_wdtReset();
}

/*
 * Method: alimenta o watchdog
 * 
 * Param:
 * 
 * Return: 
 */
void system_wdtReset(void){
    timerWrite(timer, 0); //reseta o temporizador (alimenta o watchdog) 
}

/*  Sistema de timeout, utilizar com while.
 *
 * 
 * 
 */
boolean system_timeOut(unsigned long _timeOut){

    system_wdtReset();
    if(timeOutStart==false){
        timeOutStart=true;
        _sysTimeOut=millis();
    }

    if((millis()-_sysTimeOut)<_timeOut){
        return true;
    }else{
        _sysTimeOut = 0;
        timeOutStart=false;
        return false;
    }
}

/*  
 *
 * 
 * 
 */
boolean system_timeOut_2(unsigned long _timeOut){

    system_wdtReset();
    if(timeOutStart_2==false){
        timeOutStart_2=true;
        _sysTimeOut_2=millis();
    }

    if((millis()-_sysTimeOut_2)<_timeOut){
        return true;
    }else{
        _sysTimeOut_2 = 0;
        timeOutStart_2=false;
        return false;
    }
}

/**
 * @method: printa um pacote em hexadecimal.
 * 
 * @param msgHead  
 * @param ptrBuff
 * @param buffLen
 * 
 * @return: void
 **/
void system_printHexPack(String msgHead, uint8_t*ptrBuff, uint16_t buffLen){
	uint16_t idx;
	SYSTEM_DEBUG_PRINT(msgHead);
	for (idx=0; idx<buffLen; idx++){
		SYSTEM_DEBUG_PRINT("[");
		SYSTEM_DEBUG_PRINT(ptrBuff[idx], HEX);
		SYSTEM_DEBUG_PRINT("] ");
	}
	SYSTEM_DEBUG_PRINTLN("\r\n");
}

/**
 * @method: printa um pacote char ate \0 == 0.
 * 
 * @param msgHead  
 * @param ptrBuff
 * @param buffLen
 * 
 * @return: void
 **/
void system_printCharBuff(String msgHead, uint8_t*ptrBuff, uint16_t buffLen){
	uint16_t idx;
	SYSTEM_DEBUG_PRINT(msgHead);
	for (idx=0; idx<buffLen; idx++){
		if(ptrBuff[idx]==0){
            break;
        }
        SYSTEM_DEBUG_PRINT(char(ptrBuff[idx]));
	}
	SYSTEM_DEBUG_PRINTLN("\r\n");
}