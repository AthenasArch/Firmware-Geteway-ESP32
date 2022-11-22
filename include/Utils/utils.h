#ifndef UTILS_H_
#define UTILS_H_

#include <Arduino.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// #include <conio.h>
#include <time.h>
// #include "Type.h"
#include <sys/types.h>
//#include "uGUI/ugui.h"

#define MASK_CPF "###.###.###-##"
#define MASK_CNPJ "##.###.###/####-##"
#define MASK_CEI "##.###.#####/##"
#define MASK_PIS "####.#####.##/#"
#define MASK_MAC "##:##:##:##:##:##"
#define MASK_IP "###.###.###.###"
#define MASK_IPV6 "####:####:####:####:####:####:####:####"
#define MASK_DATE "##/##/####"
#define MASK_HOUR "##:##:##"

#define DATE_FORMAT_DAY_IDENTIFIER 'd'
#define DATE_FORMAT_MONTH_IDENTIFIER 'M'
#define DATE_FORMAT_YEAR_IDENTIFIER 'y'
#define DATE_FORMAT_HOUR_24H_IDENTIFIER 'H'
#define DATE_FORMAT_HOUR_12H_IDENTIFIER 'h'
#define DATE_FORMAT_MINUTE_IDENTIFIER 'm'
#define DATE_FORMAT_SECOND_IDENTIFIER 's'
#define DATE_FORMAT1 "dd/MM/yy HH:mm"
#define DATE_FORMAT2 "dd/MM/yyyy HH:mm"
#define DATE_FORMAT3 "dd/MM/yyyy HH:mm:ss"
#define DATE_FORMAT3_NEW_LINE "dd/MM/yyyy HH:mm:ss\r\n"
#define DATE_FORMAT4 "dd/MM/yyyy"
#define DATE_FORMAT5 "HH:mm:ss"

char DATE_WEEKDAY_SUNDAY_STR[] PROGMEM = "Dom";
char DATE_WEEKDAY_MONDAY_STR[] PROGMEM = "Seg";
char DATE_WEEKDAY_TUESDAY_STR[] PROGMEM = "Ter";
char DATE_WEEKDAY_WEDNESDAY_STR[] PROGMEM = "Qua";
char DATE_WEEKDAY_THURSDAY_STR[] PROGMEM = "Qui";
char DATE_WEEKDAY_FRIDAY_STR[] PROGMEM = "Sex";
char DATE_WEEKDAY_SATURDAY_STR[] PROGMEM = "Sab";

// #define DATE_WEEKDAY_SUNDAY_STR "Dom"
// #define DATE_WEEKDAY_MONDAY_STR "Seg"
// #define DATE_WEEKDAY_TUESDAY_STR "Ter"
// #define DATE_WEEKDAY_WEDNESDAY_STR "Qua"
// #define DATE_WEEKDAY_THURSDAY_STR "Qui"
// #define DATE_WEEKDAY_FRIDAY_STR "Sex"
// #define DATE_WEEKDAY_SATURDAY_STR "Sab"

#define DATE_FORMAT_OK					0
#define DATE_FORMAT_ERROR_DOESNT_MATCH 	-1
#define DATE_FORMAT_ERROR_INVALID_DATE 	-2

typedef unsigned int UINT;

//macros auxiliares
#define INSIDE_LIMITS(val, min, max) (val < min ? 0 : val > max ? 0 : 1)
#define APPLY_LIMIT(value, minLimit, maxLimit) (value > maxLimit ? maxLimit : \
    value < minLimit ? minLimit : value)
#define BCD_TO_BIN(val) (((val)&0x0F) + ((val)>>4)*10)
#define BIN_TO_BCD(val) ((((val)/10)<<4) + (val)%10)
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

#define CHAR_TO_INT(chr) (chr - 48)
#define INT_TO_CHAR(num) (num + 48)

#define QTTY_MEMBERS_LIST(_list_) (sizeof(_list_)/sizeof(_list_[0]))
#define SIZE_CHAR_ARRAY(char_array) (sizeof(char_array)/sizeof(char_array[0]))

int charToInt(char chr);

unsigned char bcd(unsigned char dec);
unsigned char unbcd(unsigned char bcd);

/*
 * Converte uma string hexa em decimal (16 bits).
 * Ex: "0xFF" ou "ff" em 255
 */
unsigned int htoi(const char s[]);

/*
 * Converte um inteiro em string.
 * OBS: não trata número negativo.
 */
int itoa_2(int number, char string[]);

/*
 * Converte um inteiro 64 bits em string.
 * OBS: não trata número negativo.
 */
int i64toa(uint64_t number, char string[]);

/**
 * Realiza um split simples. Só funciona quando há um único separador.
 * Ex:
 *    string ->  str1  |  str2
 *    ABC.DE ->  ABC   |   DE
 *
 * @param string String que será operada
 * @param str1 Retorno da primeira parte
 * @param str2 Retorno da segunda parte (após o delimitador)
 * @param sep Separador
 * @param maxLenght Tamanho máximo de str1 e str2
 */
int simpleSplit(const char* string, char* str1, char* str2, char sep,
		int maxLenght);


/**
 * Verifica se uma string comporta um número inteiro.
 * @param str String que será operada
 * @return boolean
 */
__attribute__ ((weak)) int isNumber(const char* str);
__attribute__ ((weak)) int isNumber_withoutSign(const char* str);


/**
 * Verifica se uma string possui somente caracteres hexadecimais
 * @param str String que será operada
 * @return int
 */
int isHexadecimal(char* str);


/**
 * Verifica se determinado valor está no array - INTEGER ARRAY.
 */
int contains(int temp, const int temps[], int tempsSize);

/**
 * Verifica se determinado valor está no array - CHAR ARRAY.
 */
int containsChar(char temp, const char temps[], int tempsSize);

/**
 * Remove caracteres inválidos da string. Substitui pelo valor informado em
 * replacement.
 * Ex de uso:
 * char param[] = "Te.s-t/e";
 * char output[16] = "";
 * removeInvalidChar(param, output, ' ', 3, '.', '-', '/');
 * output -> "Teste"
 *
 * @param str String que será operada
 * @param output String de saída
 * @param replacement Char que será colocado no lugar dos chars inválidos
 * @param invalidChars Quantidade de caracteres inválidos
 * @param ... Lista dos caracteres inválidos separados por vírgula
 */
int removeInvalidChar(const char* str, char* output, char replacement,
		int invalidChars, ...);
int removeInvalidnChar(const char* str, int strLen, char* output,
		char replacement, int invalidChars, ...);
int replace_str(char* str, char* orig, const char *rep);
int replace_nstr(char* str, char* orig, const char *rep, int repLen);

void stringToWord(char* word, unsigned char* buffer);

/**
 * Aplica máscara desejada sobre uma string.
 * @param str String que será tratada.
 * @param mask Máscara que será operada.
 * @param output String de saída.
 */
int applyMask(const char* str, const char* mask, char* output);
int applyMask2(const char* str, const char* mask, char* output,
		char replaceChar);
int removeMask(const char* str, const char* mask, char* output);

/**
 * Valida CEI. Retorna 1 caso CEI válido.
 */
int isValidCEI(char *cei);
int isValidnCEI(char *cei, int len);

/**
 * Valida PIS. Retorna 1 caso PIS válido.
 */
int isValidPIS(char *pis);
int isValidnPIS(char *pis, int len);

/**
 * Valida CPF. Retorna 1 caso CPF válido.
 */
int isValidCPF(char *cpf);
int isValidnCPF(char *cpf, int len);

/**
 * Valida CNPJ. Retorna 1 caso CNPJ válido.
 */
int isValidCNPJ(char *cnpj);
int isValidnCNPJ(char *cnpj, int len);
int isValidString(char *str);

/**
 * Verifica se string contém apenas caracteres alpha numéricos ou com acento (ASCII extendido)
 */
int isValidnString(char *str, int len);

void reverseString(char *str);

/**
 * Coloca string em letras maiúsculas
 */
void strToUpper(char *str);
void removeAccents(char data[], uint8_t option);

/**
 * Remove espaço em branco em torno da string informada.
 * Ex: "   teste de string  " -> "teste de string"
 * @param data String que será verificada.
 * @param output Ponteiro para a string de saída da rotina. Deve ser previamente alocada.
 * @param onlyRight Indica se tira só do lado direito...
 */
int removeWhiteSpaceAround(const char* data, char* output, uint8_t onlyRight);

/**
 * Verifica se a string informada é um IP válido. Retorna o IP formatado
 * já no segundo parâmetro, caso ele seja diferente de nulo.
 *
 * @param address String contendo o endereço que será validado.
 * @param newIPStr String de saída que retornará o IP formatado.
 *
 */
int formatIPAddress(const char *ip, char *newIPStr);

/**
 * Verifica se a string informada é um MAC válido. Retorna o MAC formatado
 * já no segundo parâmetro.
 * @param address String contendo o endereço que será validado.
 * @param newIPStr String de saída que retornará o MAC formatado.
 */
int formatMACAddress(const char *mac, char *newMAC);

/**
 * Valida data/hora (dd mm aa hh mm ss)
 * @param day	dia
 * @param month	mes
 * @param year	ano
 * @param hour	hora
 * @param minute	minuto
 * @param second	segundo
 * @return	resultado da validação
 */
int validateDate(uint8_t day, uint8_t month, uint8_t year, uint8_t hour,
		uint8_t minute, uint8_t second);

/*
 * 	Complementa a string de dados, colocando ' ' a frente até ter o numero de dígitos informado em tamanho
 * 	entrada de no maximo 20 digitos válidos
 */
void complementaString(char dados[], uint8_t tamanho);
void strFill(const char* data, UINT size, char character, uint8_t left,
		char* outputString);

/**
 * Varre a string e separa utilizando o delimitador informado.
 * Ex: "abc.def", usando delimitador ".", retornará "abc", "def" no strArr.
 *
 * 	int arrLen = 5;
 int i = 0;
 char* strArr[arrLen];
 for (i = 0; i < arrLen; i++) {
 strArr[i] = (char*) malloc(sizeof(char) * 128);
 }

 strSplit("TESTE1.TESTE2.TESTE3.TESTE4", "", &strArr[0], arrLen, 127);

 for (i = 0; i < arrLen; i++) {
 sprintf(strMessage, "Pos: %d", i);
 display_print(strMessage); display_printXY(strArr[i], 1, 0);
 }

 for (i = 0; i < arrLen; i++) {
 free(strArr[i]);
 }
 * @param str String que será tratada pela rotina.
 * @param delimiter Delimitador que será utilizado para separar a string.
 * @param strArr Array que armazenará as strings separadas.
 * @param arrSize Tamanho do array.
 * @param maxLenArr Tamanho máximo de uma string que pode ser armazenada no array.
 */
int strSplit(const char* str, const char* delimiter, char* strArr,
        int arrSize, int maxLenArr);

int strtokCustom(const char* str, char delimiter, char* strAux, int maxLen);

/**
 * Remove os zeros à esquerda da string.
 * @param data String de entrada.
 * @param outputString String de saída.
 */
int removeLeftZero(const char* data, char* outputString);

int verifyExtension(const char* file, const char* extension);

int decrypt(unsigned char* in, long size, int startKey, int multKey,
		int addKey, unsigned char* out);
int encrypt(unsigned char* in, long size, int startKey, int multKey,
		int addKey, unsigned char* out);

int diffDate(struct tm* date1, struct tm * date2);
uint8_t betweenDate(struct tm* date1, struct tm* date2, struct tm* verifiedDate);

/* deve receber no formado dd/mm/yyyy hh:mm:ss*/
int validDateTime(char* dateTime);

/* deve receber no formado dd/mm/yyyy */
int validDate(char* date);

/* deve receber no formado hh:mm:ss */
int validTime(char* time);
int validateDateTm(struct tm* dateTime);
int validDate(char* date);
int validTime(char* time);
int isBissexto(int year);

/**
 * Insere valores na estrutura tm a partir da string 'str' informada de
 * acordo com o formato indicado. A função possui os seguintes retornos:
 * DATE_FORMAT_OK - dados carregados sem erro
 * DATE_FORMAT_ERROR_DOESNT_MATCH - formato informado não confere com dados da string
 * DATE_FORMAT_ERROR_INVALID_DATE - data contida na string não é uma data válida, porém
 * dados foram carregados na estrutura
 */
int dateStrToTm(struct tm* date, char* str, char* format);
int dateTmToStr(struct tm* date, char* str, int strSize, char* format);

/*
 *	convertIntToBytes: Converte uma int em dois bytes. 
 * 
 * 	convertBytesToInt: Converte dois bytes em uma int.
 */
uint8_t convertIntToBytes(const uint16_t dataToConvert, uint8_t*convertedBytes);
uint8_t convertBytesToInt(uint16_t*convertedData, const uint8_t*bytesToConvert);

/*
 * Atualiza estrutura date com os offsets informados. Com excessão dos offsets
 * de mês e ano, o offset é calculado pelo valor correspondente de segundos.
 * Já para os offsets de ano e mês, o offset pode variar de acordo com a data
 * informada, pelo fato de alguns meses e anos conterem numero de dias diferentes,
 * por exemplo:
 * 31/03/2013 com offset de -1 mes -> 28/02/2013
 * 15/06/2013 com offset de -1 mes -> 15/05/2013
 * O algoritmo aplicado para os offsets de mes e ano é o seguinte:
 * 1 - soma-se o offset no ano ou mes
 * 2 - valida data
 */
void makeDateOffset(struct tm* date, int dayOffset, int monthOffset,
		int yearOffset, int hourOffset, int minuteOffset, int secondOffset);
void fixDate(struct tm* date);
char* getActualDayOfWeekStr(struct tm* date);
char* getDayOfWeekStr(int dayOfWeek);

int base64_decode(char* data, int dataSize, uint8_t* decodedData,
		int decodedDataSize);
int base64_encode(uint8_t* data, int dataSize, char* encodedData,
		int encodedDataSize);
void hex_decode(char* data, int dataSize, uint8_t* decodedData,
		int decodedDataSize);
void hex_encode(uint8_t* data, int dataSize, char* encodedData,
		int encodedDataSize);
int base32_decode(const uint8_t *encoded, int encodedSize, uint8_t *result,
		int bufSize);
int base32_encode(const uint8_t *data, int length, uint8_t *result, int bufSize);
char char_hexToChar(char c);
uint32_t bioImage_rgbToGray(uint8_t r, uint8_t g, uint8_t b);
//transformacao string para uint32
//  1) evita a utilizacao de buffer auxiliar
//  2) se nao for numero UINT retorna 0
int str_to_uint32(const char* string, size_t size, uint32_t* uint);

/*
 * Method:  monta o pacote de dados do payload
 * 			Formato de 16bits, unsigned int...
 *
 * Param: payload: 
 * Param: dataToSend: vetor de dados a serem enviados...
 * Param: qttyData: tamanho do vetor de dados...
 *
 * return: ok or error
*/
uint8_t mountPayloadPackage_16_t(uint8_t*payload, uint16_t*dataPackage, const uint16_t lenDataPackage);
uint8_t unmountPayloadPackage_16_t(uint8_t*payload, uint16_t*dataPackage, const uint16_t lenDataPackage);


#endif /* UTILS_H_ */
