#ifndef EEPROM_ARCH_H_
#define EEPROM_ARCH_H_

#include <Arduino.h>
#include <stdio.h.>
#include <stdlib.h>
#include <string.h>

// #include "modules/eeprom/eepromArch.h"

enum EEPROM_MAP{
    EEPROM_MAP_RF_CONTROLLER_1=2,
    EEPROM_MAP_RF_CONTROLLER_2,
    EEPROM_MAP_RF_CONTROLLER_3,
};

uint8_t eeprmArch_initialize(void);

uint8_t eeprmArch_manualResetMemory(void);
uint8_t eeprmArch_resetMemory(void);

uint8_t eeprmArch_clearAll(void);
uint8_t eeprmArch_clearPos(const int _addr);
uint8_t eeprmArch_clearSection(const int _clrIni, const int _clrEnd);

uint8_t eeprmArch_writeByte(const int _addr, uint8_t _eepromByte);
uint8_t eeprmArch_writeBuff(const int _addrIni, uint8_t *_eepromBuff, const int _buffLen);
uint8_t eeprmArch_writeString(const int _addrIni, String *str, const int _buffLen);

/* write method*/
uint8_t eeprmArch_safeWriteByte( const int _addr, uint8_t _eepromByte);
uint8_t eeprmArch_safeWriteBuff(const int _addrIni, uint8_t *_eepromBuff, const int _buffLen);

/* read method*/
uint8_t eeprmArch_readByte(const int _addr);
uint8_t eeprmArch_readBuff(const int _addrIni, uint8_t *_eepromBuff);
uint8_t eeprmArch_readBuffUntil(const int _addrIni, uint8_t *_eepromBuff, uint8_t _endByte);
uint8_t eeprmArch_readBuffLen(const int _addrIni, uint8_t *_eepromBuff, uint16_t _buffLen);

unsigned int eeprmArch_eepromLen(void);

#endif /* EEPROM_ARCH_H_ */
