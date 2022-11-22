/*

 */

#ifndef MAP_FLASH_H_
#define MAP_FLASH_H_

#include <Arduino.h>

#define EEPROM_BUSY_ADDR   0xFF

/*
 *  Se o valor do endereco 511, for difernete de 0x80 (128d),
 *  Entao o equipamento zera totalmente a flash... 
 * 
 */

#define ADDR_CLR_FULL_MEM 511
#define VALUE_CLR_FULL_MEM 0x80



/*
 * Especifica o tamanho da flash...
 * 0 a 512 endrecos disponiveis, sendo 
 * que cada endereco pode receber um byte (0 a 255).
 */
#define FLASH_ADDR_SIZE_INI     0
#define FLASH_ADDR_SIZE_END     512

/*
 *
 * 
 */

#define FLASH_ADDR_SSID_STATUS  100 // INFORMA SE EXISTE UM SSID CADASTRADO
#define FLASH_ADDR_SSID_INI     101
#define FLASH_ADDR_SSID_END     165
#define FLASH_SSID_LEN (FLASH_ADDR_SSID_END - FLASH_ADDR_SSID_INI) 

/*
 *
 * 
 */
#define FLASH_ADDR_PASS_STATUS  166 // INFORMA SE EXISTE UMA SENHA CADASTRADA
#define FLASH_ADDR_PASS_INI     167
#define FLASH_ADDR_PASS_END     231
#define FLASH_PASS_LEN (FLASH_ADDR_PASS_END - FLASH_ADDR_PASS_INI)

/*
 *
 * 
 */
#define FLASH_ADDR_TIME_SEND_STATUS     232 // INFORMA SE EXISTE UM DETERMINADO TEMPO DE ENVIO CADASTRADO
#define FLASH_ADDR_TIME_SEND_INI        233
#define FLASH_ADDR_TIME_SEND_END        240
#define FLASH_SEND_TIME_LEN (FLASH_ADDR_TIME_SEND_END - FLASH_ADDR_TIME_SEND_INI)


#define ADDR_MEM_NET_DATA_INI FLASH_ADDR_SSID_STATUS
#define ADDR_MEM_NET_DATA_END FLASH_ADDR_TIME_SEND_END

#endif /* MAP_FLASH_H_ */
