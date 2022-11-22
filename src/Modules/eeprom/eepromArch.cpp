#include <Arduino.h>
#include "Modules/eeprom/eepromArch.h"
#include <EEPROM.h>
#include "Modules/eeprom/MAP_FLASH.h"
#include "Hardware/hardware.h"

#define EEPROM_DEBUG_ENABLE // descomente esta linha para habilitar o debug. 
#ifdef EEPROM_DEBUG_ENABLE
  #define EEPROM_DEBUG_PRINT(...) { Serial.print(__VA_ARGS__); }
  #define EEPROM_DEBUG_PRINTLN(...) { Serial.println(__VA_ARGS__); }
#else
  #define EEPROM_DEBUG_PRINT(...) {}
  #define EEPROM_DEBUG_PRINTLN(...) {}
#endif

uint8_t eeprmArch_initialize(void){

    uint8_t result=EXIT_FAILURE;

    // initialize EEPROM with predefined size
    EEPROM.begin(FLASH_ADDR_SIZE_END);

    eeprmArch_resetMemory();
    eeprmArch_manualResetMemory();

    return result;
}

uint8_t eeprmArch_manualResetMemory(void){
	
    uint8_t result=0;
    
    if(digitalRead(PIN_BUTTON_CLR_EEPROM)==0){

        EEPROM_DEBUG_PRINTLN("\n\n\r\rZerando a Flash - MANUAL...\r\r\n\n");
        
        // se o endereco de status for diferente de zero, entao zera SSID e PASS.
        if(EEPROM.read(FLASH_ADDR_SSID_STATUS)!=0){

            EEPROM_DEBUG_PRINTLN("Zerando por SSID");

            for (uint16_t idx=ADDR_MEM_NET_DATA_INI; idx<=ADDR_MEM_NET_DATA_END; idx++){
                eeprmArch_clearPos(idx);
        
                EEPROM_DEBUG_PRINT("Zerando: ");
                EEPROM_DEBUG_PRINTLN(idx);
            }
        }
        // se o Pass != de zero, tambem zera SSID e PASS
        else if (EEPROM.read(FLASH_ADDR_PASS_STATUS)!=0){

            EEPROM_DEBUG_PRINTLN("Zerando por PASS");
            

            for (uint16_t idx=ADDR_MEM_NET_DATA_INI; idx<=ADDR_MEM_NET_DATA_END; idx++){
                eeprmArch_clearPos(idx);
                EEPROM_DEBUG_PRINT("Zerando: ");
                EEPROM_DEBUG_PRINTLN(idx);
            }
        }else{
            EEPROM_DEBUG_PRINTLN("Memoria ja esta zerada...");
        }
	}
    return result;
}


/**
  * @method: Se o valor do endereco 511, for difernete de 0x80 (128d),
  * Entao o equipamento zera totalmente a flash... 
  * 
  * @param void
  * 
  * @return: 
  * 
  **/
uint8_t eeprmArch_resetMemory(void){

    uint8_t result=EXIT_FAILURE;

    EEPROM_DEBUG_PRINT("Valor do Addr ");
    EEPROM_DEBUG_PRINT(ADDR_CLR_FULL_MEM);
    EEPROM_DEBUG_PRINT(" = ");
    EEPROM_DEBUG_PRINT(eeprmArch_readByte(ADDR_CLR_FULL_MEM));
    
    if(eeprmArch_readByte(ADDR_CLR_FULL_MEM)!=VALUE_CLR_FULL_MEM){
    
        EEPROM_DEBUG_PRINTLN("\n\n\r\rZerando a Flash...\r\r\n\n");
    
        eeprmArch_clearAll();
        eeprmArch_writeByte(ADDR_CLR_FULL_MEM, VALUE_CLR_FULL_MEM);
    }else{
        EEPROM_DEBUG_PRINTLN("\n\n\r\rFlash ja foi zerada...\r\r\n\n");
    }
    return result;
}

////////////////////////////////////////////////////////////////////////////////
////
////    Limpa a memoria 
////
////////////////////////////////////////////////////////////////////////////////
/*
 * Method:  Limpa toda a memoria Flash
 * 
 * Param:
 * 
 * Return:
 * 
 */
uint8_t eeprmArch_clearAll(void){

    uint16_t i=0;


    EEPROM_DEBUG_PRINTLN("Limpando toda memoria...:");

    for (i=0; i < FLASH_ADDR_SIZE_END ; i++) {
        EEPROM.write(i, 0);
        EEPROM.commit();
        delay(1);
        
        EEPROM_DEBUG_PRINTLN("Zerando: ");
        EEPROM_DEBUG_PRINTLN(i);
    }
    return 1;
}

/*
 * Method:
 * 
 * Param:
 * 
 * Return:
 * 
 */
uint8_t eeprmArch_clearPos(const int _addr){
    EEPROM.write(_addr, 0);
    EEPROM.commit();
    delay(1);
    return EEPROM.read(_addr);
}
/*
 * Method:
 * 
 * Param:
 * 
 * Return:
 * 
 */
uint8_t eeprmArch_clearSection(const int _clrIni, const int _clrEnd){
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
////
////    Grava na memoria
////
////////////////////////////////////////////////////////////////////////////////
/*
 * Method:
 * 
 * Param:
 * 
 * Return:
 * 
 */
uint8_t eeprmArch_writeByte(const int _addr, uint8_t _eepromByte){
    EEPROM.write(_addr, _eepromByte);
    EEPROM.commit();
    return EEPROM.read(_addr);
}

/**
 * @brief
 * 
 * @param
 * 
 * @return
 */
uint8_t eeprmArch_writeBuff(const int _addrIni, uint8_t *_eepromBuff, const int _buffLen){
    return 0;
}

/**
 * @brief
 * 
 * @param
 * 
 * @return
 */
uint8_t eeprmArch_writeString(const int _addrIni, String *str, const int _buffLen){
    
    uint8_t byte=0;
    uint16_t idx=0;

    for (idx=_addrIni; idx<_buffLen; idx++){
        byte = str->charAt(idx-_addrIni);
        if(byte==0){
            EEPROM_DEBUG_PRINT("Encontrou zero na pos: ");
            EEPROM_DEBUG_PRINTLN(idx);
            break;
        }else{
            EEPROM_DEBUG_PRINT(byte);
            EEPROM_DEBUG_PRINT(".");
            eeprmArch_writeByte(idx, byte);
        }
    }
    
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
////
////    Grava somente dados novos na memoria
////
////////////////////////////////////////////////////////////////////////////////
// uint8_t eeprmArch_safeWriteByte(const int _addr, uint8_t _eepromByte){
//     EEPROM.update(_addr, _eepromByte);
//     return EEPROM.read(_addr);
// }

// uint8_t eeprmArch_safeWriteBuff(const int _addrIni, uint8_t *_eepromBuff, const int _buffLen){
//     return 0;
// }

////////////////////////////////////////////////////////////////////////////////
////
////    Leitura de dados da memoria
////
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief le um byte na eeprom
 * 
 * @param addr do byte
 * 
 * @return:byte lido
 * 
 */
uint8_t eeprmArch_readByte(const int _addr){
    return EEPROM.read(_addr);
}

/**
 * @brief le um buffer ate encontrar \0 == 0
 * 
 * @param _addrIni endereco inicial do buffer.
 * @param _eepromBuff local de armazenamento do buffer.
 * 
 * @return SUCCESS or FAIL.
 * 
 */
uint8_t eeprmArch_readBuff(const int _addrIni, uint8_t *_eepromBuff){

    uint8_t result=EXIT_FAILURE;
    uint8_t idx=0;

    for (idx = _addrIni; idx<ADDR_CLR_FULL_MEM; idx++){
        _eepromBuff[idx-_addrIni] = eeprmArch_readByte(idx);
        if(eeprmArch_readByte(idx)==0){
            break;
        }
    }

    if(idx!=ADDR_CLR_FULL_MEM){
        result=EXIT_SUCCESS;
    }else{
        result=EXIT_FAILURE;
    }
    return result;
}

/**
 * @brief
 * 
 * @param
 * 
 * @return
 */
uint8_t eeprmArch_readBuffUntil(const int _addrIni, uint8_t *_eepromBuff, uint8_t _endByte){
    uint8_t result=EXIT_FAILURE;
    return result;
}

/**
 * @brief
 * 
 * @param
 * 
 * @return
 */
uint8_t eeprmArch_readBuffLen(const int _addrIni, uint8_t *_eepromBuff, uint16_t _buffLen){
    uint8_t result=EXIT_FAILURE;
    return result;
}

////////////////////////////////////////////////////////////////////////////////
////
////    Status da memoria...
////
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief
 * 
 * @param
 * 
 * @return
 */
unsigned int eeprmArch_eepromLen(void){
    return EEPROM.length();
}
