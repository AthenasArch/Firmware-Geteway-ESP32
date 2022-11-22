/*
 * utils.c
 *
 *  Created on: 06/01/2011
 *      Author: Eduardo Andrade
 */
#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include "Utils/utils.h"
// #include "Type.h"
//#include "uGUI/ugui.h"
//#include "inc/database/structures/repBiometricConfig.h"
//#include "inc/res/menu/menuAtenas.h"

#define OK 0
#define ERROR -1

typedef	unsigned int	uint;
typedef	unsigned char	u_char;

void removeAccents(char data[], uint8_t changeToUpperCase) {
    /* Caracteres suportados
     * Cálculo do acento é feito assim: (valor do acento em hexa) - 256.
     *
     * áéíóúÁÉÍÓÚàèìòùÀÈÌÒÙäëïöüÄËÏÖÜâêîôûÂÊÎÔÛãõÃÕçÇñÑ
     */
    int i;
    for (i = 0; i < strlen(data); i++) {
        signed char tmp = data[i];
        
        switch (tmp) {

            case -28:
            case -29:
            case -30:
            case -31:
            case -32:
            case -92:
            case -93:
            case -94:
            case -95:
            case -96:
                data[i] = 'a'; //a
                break;
            case -21:
            case -22:
            case -23:
            case -24:
            case -85:
            case -86:
            case -87:
            case -88:
                data[i] = 'e'; //e
                break;
            case -17:
            case -18:
            case -19:
            case -20:
            case -81:
            case -82:
            case -83:
            case -84:
                data[i] = 'i'; //i
                break;
            case -10:
            case -11:
            case -12:
            case -13:
            case -14:
            case -74:
            case -75:
            case -76:
            case -77:
            case -78:
                data[i] = 'o'; //o
                break;
            case -4:
            case -5:
            case -6:
            case -7:
            case -68:
            case -69:
            case -70:
            case -71:
                data[i] = 'u'; //u
                break;
            case -60:
            case -61:
            case -62:
            case -63:
            case -64:
            case -124:
            case -125:
            case -126:
            case -127:
            case -128:
                data[i] = 'A'; //A
                break;
            case -53:
            case -54:
            case -55:
            case -56:
            case -117:
            case -118:
            case -119:
            case -120:
                data[i] = 'E'; //E
                break;
            case -49:
            case -50:
            case -51:
            case -52:
            case -113:
            case -114:
            case -115:
            case -116:
                data[i] = 'I'; //I
                break;
            case -42:
            case -43:
            case -44:
            case -45:
            case -46:
            case -106:
            case -107:
            case -108:
            case -109:
            case -110:
                data[i] = 'O'; //O
                break;
            case -36:
            case -37:
            case -38:
            case -39:
            case -100:
            case -101:
            case -102:
            case -103:
            case -104:
                data[i] = 'U'; //U
                break;
            case -25:
            case -89:
                data[i] = 'c'; //c
                break;
            case -57:
            case -121:
                data[i] = 'C'; //C
                break;
            case -15:
            case -79:
                data[i] = 'n'; //n
                break;
            case -47:
            case -111:
                data[i] = 'N'; //N
                break;
            default:
                if (tmp > 0) {
                    data[i] = data[i];
                }
        }
        if (changeToUpperCase)
            data[i] = toupper(data[i]);

    }
    return;
}

int removeWhiteSpaceAround(const char* data, char* output, uint8_t onlyRight) {
    register int i;
    int initPos = 0; //Posi��o inicial
    int endPos = strlen(data) - 1; //Posi��o final

    if (!onlyRight) {
        for (i = 0; i < strlen(data); i++) {
            if (data[i] != ' ') { //Se n�o for espa�o em branco
                initPos = i; //ok, encontrou posi��o inicial
                break;
            }
        }
    }
    for (i = endPos; i > initPos; i--) {
        if (data[i] != ' ') { //Se n�o for espa�o em branco
            endPos = i; //ok, encontrou posi��o inicial
            break;
        }
    }
    //Copiando para string X bytes � partir da posi��o inicial
    strncpy(output, &data[initPos], (endPos - initPos) + 1);
    output[(endPos - initPos) + 1] = '\0';
    return OK;
}

int charToInt(char chr) {
    return chr - 48;
}

unsigned char bcd(unsigned char dec) {
    return ((dec / 10) << 4) + (dec % 10);
}

unsigned char unbcd(unsigned char bcd) {
    return ((bcd >> 4) * 10) +bcd % 16;
}

unsigned int htoi(const char s[]) {
    unsigned int val = 0;
    int x = 0;

    if (s[x] == '0' && (s[x + 1] == 'x' || s[x + 1] == 'X'))
        x += 2;

    while (s[x] != '\0') {
        if (val > 0xFFFF)
            return 0;
        else if (s[x] >= '0' && s[x] <= '9') {
            val = val * 16 + s[x] - '0';
        } else if (s[x] >= 'A' && s[x] <= 'F') {
            val = val * 16 + s[x] - 'A' + 10;
        } else if (s[x] >= 'a' && s[x] <= 'f') {
            val = val * 16 + s[x] - 'a' + 10;
        } else
            return 0;

        x++;
    }
    return val;
}

int itoa_2(int number, char string[]) {
    register int i = 0, j = 0, k = 0;
    if (number != 0) {
        char temp[16] = {0};
        while (number != 0) {
            register int tmp = number % 10; //obt�m o primeiro d�gito
            temp[i++] = (char) (tmp + 0x30); //char to int
            number /= 10; //movendo uma casa para a direita
        }
        for (j = i - 1; j >= 0; j--) {
            string[k++] = temp[j]; //reordenando string
        }
    } else {
        i++; //length
        string[k++] = '0';
    }
    string[k] = '\0';
    return i;
}

int i64toa(uint64_t number, char string[]) {
    int i = 0, j = 0, k = 0;
    if (number != 0) {
        char temp[16] = {0};
        while (number != 0) {
            uint64_t tmp = number % 10; //obt�m o primeiro d�gito
            temp[i++] = (char) (tmp + 0x30); //char to int
            number /= 10; //movendo uma casa para a direita
        }
        for (j = i - 1; j >= 0; j--) {
            string[k++] = temp[j]; //reordenando string
        }
    } else {
        i++; //length
        string[k++] = '0';
    }
    string[k] = '\0';
    return i;
}

int simpleSplit(const char* string, char* str1, char* str2, char sep,
        int maxLength) {
    int i;
    for (i = 0; (*string != sep) && (*string != '\0') && (i < maxLength); string++) {
        str1[i++] = *string;
    }
    str1[i] = '\0'; //end string
    if ((*string != sep) && (str2 != NULL)) {
        str1[0] = '\0';
        return 0; // String inv�lida (terminou antes do separador)
    }
    string++; //pulando separador
    if (str2 != NULL) { //se o segundo par�metro for desejado...
        for (i = 0; (*string != '\0') && (i < maxLength); string++) {
            str2[i++] = *string;
        }
        str2[i] = '\0'; //end string
    }
    return 1;
}

int _isNumber(const char* str, uint8_t withSign) {
    if (str != NULL) {
        if (*str == '\0')
            return 0;
        if (withSign) {
            if ((*str == '-') || (*str == '+'))
                str++; // Pula sinal do n�mero
        }
        for (; *str != '\0'; str++) {
            if (!isdigit(*str)) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

int isNumber(const char* str) {
    return _isNumber(str, 1);
}

int isNumber_withoutSign(const char* str) {
    return _isNumber(str, 0);
}

int isHexadecimal(char* str) {
    int result = OK;
    int i;
    
    for (i = 0; i < strlen(str); i++) {
        if ((str[i] < '0') || (str[i] > 'F')
                || ((str[i] > '9') && (str[i] < 'A'))) {
            result = ERROR;
            break;
        }
    }
    return result;
}

int contains(int temp, const int temps[], int tempsSize) {
    register int i;
    for (i = 0; i < tempsSize; i++) {
        if (temp == temps[i])
            return i;
    }
    return ERROR;
}

int containsChar(char temp, const char temps[], int tempsSize) {
    register int i;
    for (i = 0; i < tempsSize; i++) {
        if (temp == temps[i])
            return i;
    }
    return ERROR;
}

int removeInvalidChar(const char* str, char* output, char replacement,
        int invalidChars, ...) {
    int i;
    va_list listPointer; //parameter list
    va_start(listPointer, invalidChars); //initialize
    strcpy(output, str);
    for (i = 0; i < invalidChars; i++) { //for each invalid char
        char* tmp = (char*) output;
        char* outputTmp = output;
        char invalidChar = va_arg(listPointer, int); //take invalid char
        while (*tmp) { //go through string
            if (*tmp == invalidChar) {
                if (replacement != '\0') {
                    *outputTmp = replacement;
                    outputTmp++;
                }
            } else {
                *outputTmp = *tmp;
                outputTmp++;
            }
            tmp++; //go on, move one char forward
        }
        *outputTmp = '\0'; //Finalizando string
    }
    va_end(listPointer); //ending
    return 0; //ok, return
}

int removeInvalidnChar(const char* str, int strLen, char* output,
        char replacement, int invalidChars, ...) {
    int i;

    va_list listPointer; //parameter list
    va_start(listPointer, invalidChars); //initialize
    memcpy(output, str, strLen); //Copiando conte�do que ser� validado
    output[strLen] = '\0';
    for (i = 0; i < invalidChars; i++) { //for each invalid char
        char* tmp = (char*) output;
        char* outputTmp = output;
        char invalidChar = va_arg(listPointer, int); //take invalid char
        while (*tmp) { //go through string
            if (*tmp == invalidChar) {
                if (replacement != '\0') {
                    *outputTmp = replacement;
                    outputTmp++;
                }
            } else {
                *outputTmp = *tmp;
                outputTmp++;
            }
            tmp++; //go on, move one char forward
        }
        *outputTmp = '\0'; //Finalizando string
    }
    va_end(listPointer); //ending
    return 0; //ok, return
}

int replace_str(char* str, char* orig, const char *rep) {
    return replace_nstr(str, orig, rep, strlen(rep));
}

int replace_nstr(char* str, char* orig, const char *rep, int repLen) {
    int len = strlen(str);
    int nLen = 0;
    int nPlus;
    int i;
    char* p = strstr(str, orig);

    if (p == NULL) { // Is 'orig' even in 'str'?
        return 0;
    }

    nLen = p - str;

    nPlus = repLen - strlen(orig);
    if (nPlus > 0) {
        for (i = 0; i < (len - nLen); ++i) {
            str[len + nPlus - i] = str[len - i];
        }
        str[len + nPlus] = 0;
    } else if (nPlus < 0) {
        for (i = 0; i < (len - nLen); ++i) {
            str[nLen + i] = str[nLen - nPlus + i];
        }
        str[len + nPlus] = 0;
    }

    for (i = 0; i < repLen; i++) {
        str[nLen + i] = rep[i];
    }
    return 1;
}

void stringToWord(char* word, unsigned char* buffer) {
    uint32_t len = strlen(word) / 2; //converte cada 2 caracteres em 1 byte
    uint32_t i;
    for (i = 0; i < len; i++) {
        char temp[3] = {0};
        strncpy(temp, &word[i * 2], 2); //copiando 2 bytes
        buffer[i] = atoi(temp); //inserindo byte no array
    }
}

int applyMask(const char* str, const char* mask, char* output) {
    return applyMask2(str, mask, output, '0');
}

int applyMask2(const char* str, const char* mask, char* output,
        char replaceChar) {
    int i = 0; //Contador auxiliar
    int j = 0; //Contador auxiliar

    for (i = 0; i < strlen(mask); i++) {
        if (mask[i] == '#') { //Se for cerquilha, � para copiar n�mero...
            output[i] = ((j < strlen(str)) ? str[j] : replaceChar); //Se h� dados copia, sen�o copia um '0'
            j++;
        } else {
            output[i] = mask[i]; //Copiando ponto, tra�o, ou outro caractere
        }
    }
    return OK;
}

int removeMask(const char* str, const char* mask, char* output) {
    int i = 0; //Contador auxiliar
    int j = 0; //Contador auxiliar

    for (i = 0; i < strlen(mask); i++) {
        if (mask[i] == '#') { //Se for cerquilha, � para copiar n�mero...
            output[j] = ((i < strlen(str)) ? str[i] : '0');
            j++;
        }
    }
    output[j] = '\0';
    return OK;
}

int isValidCEI(char *cei) {
    return isValidnCEI(cei, strlen(cei));
}

int isValidnCEI(char *cei, int len) {
    //CEI "00.000.00000/00"
    //size_t found;
    uint32_t sizeMask = 12;

    //   found = cei.find('.');
    //   while (found != string::npos) {
    //       cei.replace(found, 1, "");
    //       found = cei.find('.');
    //   }
    //   found = cei.find('/');
    //   while (found != string::npos) {
    //       cei.replace(found, 1, "");
    //       found = cei.find('/');
    //   }
    //   found = cei.find('-');
    //   while (found != string::npos) {
    //       cei.replace(found, 1, "");
    //       found = cei.find('-');
    //   }

    char outputString[32] = "";
    removeInvalidnChar(cei, len, outputString, '\0', 3, '.', '-', '/');

    const int size = 11;
    const char *invalidos[size] = { "111111111111", "222222222222", "333333333333", "444444444444", "555555555555",
                                    "666666666666", "777777777777", "888888888888", "999999999999", "000000000000",
                                    "            " };

    if (strcmp(outputString, invalidos[10]) == 0) {
        return 1; //Cei em branco � v�lido
    }

    uint32_t i;
    for (i = 0; i < size; i++) {
        if (strcmp(outputString, invalidos[0]) == 0) {
            return 0;
        }
    }

    if (strlen(outputString) == sizeMask) {
        if (isNumber(outputString)) {

            //            //valid sizes of numbers CEI "00.000.00000/00"
            //            if ((charToint(cei.at(0))) + (charToint(cei.at(1))) < 0) return false;
            //            if ((charToint(cei.at(2))) + (charToint(cei.at(3))) +
            //                    (charToint(cei.at(4)))< 0) return false;
            //            if ((charToint(cei.at(5))) + (charToint(cei.at(6))) +
            //                    (charToint(cei.at(7))) +
            //                    (charToint(cei.at(8))) +
            //                    (charToint(cei.at(9))) < 0) return false;
            //            if ((charToint(cei.at(10))) != 7 ) return false;


            int pesos[11] = {7, 4, 1, 8, 5, 2, 1, 6, 3, 7, 4};
            int somatorio = 0;
            int result;

            char aux[6] = {0};
            //stringstream aux;
            //Multiplicar os �ltimos 11 algarismos pelos seus respectivos pesos
            //Somar todos os produtos obtidos no item anterior
            //Somar de o algarismo da unidade com o da dezena obtido no item anterior.
            //subtrair de 10 o algarismo da unidade do resultado
            //O algarismo da unidade do resultado da subtra��o ser� o d�gito verificador.

            uint32_t i;
            for (i = 0; i < sizeMask - 1; i++) {
                somatorio += charToInt(outputString[i]) * pesos[i];
            }
            //aux.str("");
            //aux << somatorio;
            itoa_2(somatorio, aux);
            if (somatorio > 9) {
                result = (charToInt(aux[strlen(aux) - 2]) + charToInt(
                        aux[strlen(aux) - 1]));
            } else {
                result = 0 + charToInt(aux[strlen(aux) - 1]);
            }

            //aux.str("");
            //aux << result;
            memset(aux, 0, 6);
            itoa_2(result, aux);
            //unidade do resultado
            result = 10 - charToInt(aux[strlen(aux) - 1]);

            memset(aux, 0, 6);
            itoa_2(result, aux);
            //aux.str("");
            //aux << result;

            if (outputString[sizeMask - 1] == aux[strlen(aux) - 1])
                return 1;
        }
    }
    return 0;
}

int isValidPIS(char *pis) {
    return isValidnPIS(pis, strlen(pis));
}

int isValidnPIS(char *pis, int len) {
    //Formato : NNNNNNNNNND
    //Onde:
    //NNNNNNNNN - N�mero do Identificador
    //D - D�gito Verificador
    //
    //a) Multiplicar os 10 primeiros algarismos pelos pesos conforme ilustra��o abaixo:
    //
    //pesos 3 2 9 8 7 6 5 4 3 2 d�gito verificador
    //X X X X X X X X X X - D
    //
    //b) Somar todos os produtos obtidos no item "a".
    //c) Dividir o somat�rio do item "b" por 11.
    //d) Subtrair de 11 o resto da divis�o do item "c".
    //
    //O resultado ser� o d�gito verificador. Caso o resultado da subtra��o seja 10 ou 11, o d�gito ser� 0.

    //PIS "0000.00000.00/0"
    //size_t found;
    uint32_t sizeMask1 = 12;
    uint32_t sizeMask2 = 11;
    char temp[32] = "";
    char* outputString = temp;

    removeInvalidnChar(pis, len, outputString, '\0', 3, '.', '-', '/');
    if (!isNumber(outputString)) {
        return 0;
    }
    if (strlen(outputString) == sizeMask1) {
        if (outputString[0] != '0')
            return 1; // Valida todos PIS com 12 d�gitos (que n�o iniciam com 0)

        outputString++; // Altera o ponteiro de in�cio da string
    }

    const int size = 10;
    const char *invalidos[size] = { "111111111111", "222222222222", "333333333333", "444444444444", "555555555555",
                                    "666666666666", "777777777777", "888888888888", "999999999999", "000000000000"};

    uint32_t i;
    for (i = 0; i < size; i++) {
        if (strcmp(outputString, invalidos[i]) == 0)
            return 0;
    }

    if (strlen(outputString) == sizeMask2) {
        if (isNumber(outputString)) {

            //pesos 3 2 9 8 7 6 5 4 3 2 d�gito verificador
            int pesos[10] = {3, 2, 9, 8, 7, 6, 5, 4, 3, 2};
            int somatorio = 0;
            int result;

            uint32_t i;
            for (i = 0; i < sizeMask2 - 1; i++) {
                somatorio += charToInt(outputString[i]) * pesos[i];
            }
            //c) Dividir o somat�rio do item "b" por 11.

            //d) Subtrair de 11 o resto da divis�o do item "c".
            result = 11 - (somatorio % 11);

            //O resultado ser� o d�gito verificador.
            //Caso o resultado da subtra��o seja 10 ou 11, o d�gito ser� 0.

            if (charToInt(outputString[sizeMask2 - 1]) == result)
                return 1;
            if ((charToInt(outputString[sizeMask2 - 1]) == 0)
                    && ((result == 10) || result == 11))
                return 1;
        }
    }
    return 0;
}

int isValidCPF(char *cpf) {
    return isValidnCPF(cpf, strlen(cpf));
}

int isValidnCPF(char *cpf, int len) {
    if (len > 0) {
        int d1, d2;
        int digito1, digito2, resto;
        int digitoCPF;
        int size = 10;
        char nDigResult[65] = {0};
        char outputString[32] = "";
        removeInvalidnChar(cpf, len, outputString, '\0', 3, '.', '-', '/');

        // char* invalidos[10];
        const char *invalidos[10] = { "111111111111", "222222222222", "333333333333", "444444444444", "555555555555",
                                    "666666666666", "777777777777", "888888888888", "999999999999", "000000000000"};
        uint32_t i;
        for (i = 0; i < size; i++) {
            if (strcmp(outputString, invalidos[i]) == 0)
                return 0;
        }

        d1 = d2 = 0;
        digito1 = digito2 = resto = 0;

        unsigned int nCount;
        for (nCount = 1; nCount < strlen(outputString) - 1; nCount++) {
            //string aux = strCpf.substr(nCount - 1, nCount);
            digitoCPF = charToInt(outputString[nCount - 1]);
            //aux.erase(aux.begin(), aux.end());
            //multiplique a ultima casa por 2 a seguinte por 3 a seguinte por 4 e assim por diante.
            d1 = d1 + (11 - nCount) * digitoCPF;

            //para o segundo digito repita o procedimento incluindo o primeiro digito calculado no passo anterior.
            d2 = d2 + (12 - nCount) * digitoCPF;
        }

        //Primeiro resto da divis�o por 11.
        resto = (d1 % 11);

        //Se o resultado for 0 ou 1 o digito � 0 caso contr�rio o digito � 11 menos o resultado anterior.
        if (resto < 2) {
            digito1 = 0;
        } else {
            digito1 = 11 - resto;
        }

        d2 += 2 * digito1;

        //Segundo resto da divis�o por 11.
        resto = (d2 % 11);

        //Se o resultado for 0 ou 1 o digito � 0 caso contr�rio o digito � 11 menos o resultado anterior.
        if (resto < 2) {
            digito2 = 0;
        } else {
            digito2 = 11 - resto;
        }

        //Digito verificador do CPF que est� sendo validado.
        char nDigVerific[3] = {outputString[strlen(outputString) - 2],
            outputString[strlen(outputString) - 1], 0};

        //Concatenando o primeiro resto com o segundo.
        char strAux[32] = {0};
        sprintf(strAux, "%d", digito1);
        strcat(nDigResult, strAux); // nDigResult.append(strAux);
        char strAux1[32] = {0};
        sprintf(strAux1, "%d", digito2);
        strcat(nDigResult, strAux1); //nDigResult.append(strAux1);
        //nDigResult = String.valueOf(digito1) + String.valueOf(digito2);

        //comparar o digito verificador do cpf com o primeiro resto + o segundo resto.,
        if (strcmp(nDigVerific, nDigResult) == 0) {
            return 1;
        } else {
            return 0;
        }
    } else { //se CPF for em branco...
        return 0;
    }
}

int isValidCNPJ(char *cnpj) {
    return isValidnCNPJ(cnpj, strlen(cnpj));
}

int isValidnCNPJ(char *cnpj, int len) {
    if (len > 0) {
        register int soma = 0;
        register int size = 10;

        char outputString[32] = "";

        removeInvalidnChar(cnpj, len, outputString, '\0', 3, '.', '-', '/');

        const char *invalidos[10] = {   "111111111111", "222222222222", "333333333333", "444444444444", "555555555555",
                                        "666666666666", "777777777777", "888888888888", "999999999999", "000000000000"};

        int i, j;
        for (i = 0; i < size; i++) {
            if (strcmp(outputString, invalidos[i]) == 0)
                return 0;
        }

        if (strlen(outputString) == 14) {
            for (i = 0, j = 5; i < 12; i++) {
                soma += j-- * (outputString[i] - '0');
                if (j < 2) {
                    j = 9;
                }
            }
            soma = 11 - (soma % 11);
            if (soma > 9) {
                soma = 0;
            }
            if (soma == (outputString[12] - '0')) {
                soma = 0;
                int i;
                for (i = 0, j = 6; i < 13; i++) {
                    soma += j-- * (outputString[i] - '0');
                    if (j < 2) {
                        j = 9;
                    }
                }
                soma = 11 - (soma % 11);
                if (soma > 9) {
                    soma = 0;
                }
                if (soma == (outputString[13] - '0')) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int isValidString(char *str) {
    return isValidnString(str, strlen(str));
}

int isValidnString(char *str, int len) {
    int i = 0;
    while (i < len) {
        if ((str[i] >= 0x20 && str[i] <= 0x7E) || (str[i] >= 0x80 && str[i]
                <= 0xA5) || str[i] == 0x00) {
            i++;
        } else {
            break;
        }
    }
    if (i == len)
        return 1;
    return 0;
}

void complementaString(char dados[], uint8_t tamanho) {
    char temp[21];
    memset(temp, 0x00, 21);
    memcpy(temp, dados, strlen(dados));
    if (strlen(temp) > tamanho) {
        memcpy(dados, &temp[strlen(temp) - tamanho], tamanho + 1);
    } else if (strlen(temp) < tamanho) {
        uint8_t i = tamanho - strlen(temp);
        memset(dados, ' ', i);
        sprintf(dados + i, "%s", temp);
    }
}

/**
 *
 */
void strFill(const char* data, uint size, char character, uint8_t left,
        char* outputString) {
    memset(outputString, character, size); //Completando string com complemento
    const int strDataLen = strlen(data);
    if (strDataLen < size) { //Verifica se tem espa�o para completar...
        if (left) { //Copia no final da string
            memcpy(&outputString[size - strDataLen], data, strDataLen);
        } else { //Copia no come�o da string
            memcpy(outputString, data, strDataLen);
        }
    } else { //Copiando pelo menos os bytes que cabem...
        memcpy(outputString, data, size);
    }
    outputString[size] = '\0';
    return;
}

int strSplit(const char* str, const char* delimiter, char* strArr,
        int arrSize, int maxLenArr) {
    int idxStr = 0;
    int idxCaracterStr = 0;
    int idx = 0;
    while (idx < strlen(str)) {
        if (str[idx] == delimiter[0]) {
            strArr[idxStr] = '\0';
            idxCaracterStr++;
            strArr += (maxLenArr + 1);
            idxStr = 0;
        } else {
            if (arrSize > idxCaracterStr) {
                if (idxStr < maxLenArr) {
                    strArr[idxStr] = str[idx];
                    idxStr = idxStr + 1;
                }
            } else {
                break;
            }
        }
        idx = idx + 1;
    }
    return 0;
}

int strtokCustom(const char* str, char delimiter, char* strAux, int maxLen) {
    int i = 0;
    //Enquanto não achou delimitador, não é fim, não estourou tamanho    
    while ((*str != delimiter) && (*str != 0x00) && (i++ < maxLen)) {
        *strAux = *str; //copia char para a string
        strAux++;
        str++;
    }
    *strAux = 0;
    return i;
}

int removeLeftZero(const char* data, char* outputString) {
    register int i;
    for (i = 0; i < strlen(data); i++) {
        if (data[i] != '0')
            break;
    }
    strcpy(outputString, &data[i]);
    return OK;
}

void reverseString(char *str) {
    int i, j, length = strlen(str);
    char c;

    if (length <= 1) //valida string de um �nico caractere...
        return;

    for (i = 0, j = length - 1; i < j; i++, j--) {
        c = str[i];
        str[i] = str[j];
        str[j] = c;
    }
}

void strToUpper(char *str) {
    char *auxStr = str;
    do {
        *auxStr = toupper(*auxStr);
        auxStr++;
    } while (*auxStr != '\0');
    return;
}

int formatIPAddress(const char *address, char *newIPStr) {
    //Formato: 127.0.0.1
    int result = ERROR;
    const unsigned int ipLen = strlen(address);

    //Validando tamanho da string informada
    if ((ipLen > 6) && (ipLen < 16)) {
        char tempIPAddress[16] = {0};
        int i, count;
        uint8_t positions[3]; //Posi��o dos caracteres '.' (ponto) na string

        strcpy(tempIPAddress, address);

        result = OK; //Reinicializando resultado

        count = 0;
        for (i = 0; i < ipLen; i++) {
            if (tempIPAddress[i] == '.') {
                if (count > 3) { //Se houver mais de 3 pontos, j� manda parar...
                    result = ERROR;
                    break; //Mais de 3 pontos na string
                }
                positions[count++] = i + 1;
                tempIPAddress[i] = '\0'; //Trocando ponto por \0 na posi��o
            }
        }

        if ((result == OK) && (count == 3)) { //Se houver exatamente 3 pontos...

            result = ERROR; //Reinicializando resultado

            //Validando cada um dos 4 octetos. Verifica se string � n�mero
            if (isNumber(tempIPAddress)) {
                if (isNumber(&tempIPAddress[positions[0]])) {
                    if (isNumber(&tempIPAddress[positions[1]])) {
                        if (isNumber(&tempIPAddress[positions[2]])) {
                            unsigned int add1, add2, add3, add4;
                            add1 = atoi(tempIPAddress);
                            add2 = atoi(&tempIPAddress[positions[0]]);
                            add3 = atoi(&tempIPAddress[positions[1]]);
                            add4 = atoi(&tempIPAddress[positions[2]]);

                            //Validando se endere�o � maior que 255
                            if (!((add1 > 255) || (add2 > 255) || (add3 > 255)
                                    || (add4 > 255))) {
                                if (!((add1 == 0) && (add2 == 0) && (add3 == 0)
                                        && (add4 == 0))) {

                                    if (!((add1 == 255) && (add2 == 255)
                                            && (add3 == 255) && (add4 == 255))) {
                                        //Se string de sa�da for diferente de nulo
                                        if (newIPStr != NULL) {
                                            //Copiando IP formatado para string
                                            sprintf(newIPStr,
                                                    "%03u.%03u.%03u.%03u",
                                                    add1, add2, add3, add4);
                                        }
                                        result = OK; //OK, IP v�lido
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            result = ERROR;
        }
    }
    return result;
}

int formatMACAddress(const char* mac, char* newMAC) {
    // Formato: AA:BB:CC:DD:EE:FF
    int result = ERROR;
    if (strlen(mac) == 17) {
        if ((mac[2] == ':') && (mac[5] == ':') && (mac[8] == ':') && (mac[11]
                == ':') && (mac[14] == ':')) {
            register int i;

            strcpy(newMAC, mac);
            strToUpper(newMAC);
            result = OK;

            for (i = 0; i < 17; i++) {
                if (i == 2 || i == 5 || i == 8 || i == 11 || i == 14) {
                    continue; //Se for posi��o dos ':' pula caractere
                }

                if ((newMAC[i] < '0') || (newMAC[i] > 'F')
                        || ((newMAC[i] > '9') && (newMAC[i] < 'A'))) {
                    result = ERROR;
                    break;
                }
            }
        }
    }
    return result;
}

int verifyExtension(const char* file, const char* extension) {
    int index = strlen(file);
    while (index > 0) {
        if (file[index] == '.') {
            index++;
            break;
        } else {
            index--;
        }
    }
    if (index > 0) {
        if (strcmp(&file[index], extension) == 0) {
            return 1;
        }
    }
    return 0;
}

int decrypt(unsigned char* in, long size, int startKey, int multKey,
        int addKey, unsigned char* out) {
    int i;
    memset(out, 0, size + 1);
    for (i = 0; i <= size; i++) {
        out[i] = in[i] ^ (startKey >> 8);
        startKey = (in[i] + startKey) * multKey + addKey;
    }
    out[size] = '\0';
    return 0;
}

int encrypt(unsigned char* in, long size, int startKey, int multKey,
        int addKey, unsigned char* out) {
    int i;
    memset(out, 0, size + 1);
    for (i = 0; i <= size; i++) {
        out[i] = in[i] ^ (startKey >> 8);
        startKey = (out[i] + startKey) * multKey + addKey;
    }
    out[size] = '\0';
    return 0;
}

int diffDate(struct tm* date1, struct tm * date2) {
    if (date1->tm_year == date2->tm_year) {
        if (date1->tm_mon == date2->tm_mon) {
            if (date1->tm_mday == date2->tm_mday) {
                if (date1->tm_hour == date2->tm_hour) {
                    if (date1->tm_min == date2->tm_min) {
                        if (date1->tm_sec == date2->tm_sec) {
                            return 0; //data hora � igual
                        } else {
                            return (date1->tm_sec > date2->tm_sec) ? 1 : 2;
                        }
                    } else {
                        return (date1->tm_min > date2->tm_min) ? 1 : 2;
                    }
                } else {
                    return (date1->tm_hour > date2->tm_hour) ? 1 : 2;
                }
            } else {
                return (date1->tm_mday > date2->tm_mday) ? 1 : 2;
            }
        } else {
            return (date1->tm_mon > date2->tm_mon) ? 1 : 2;
        }
    } else {
        return (date1->tm_year > date2->tm_year) ? 1 : 2;
    }
    return ERROR;
}

uint8_t betweenDate(struct tm* date1, struct tm* date2, struct tm* verifiedDate) {
    int diff1 = diffDate(date1, verifiedDate); //comparando com a inicial
    int diff2 = diffDate(date2, verifiedDate); //comparando com a final
    //se for maior ou igual a primeira, e menor ou igual � segunda...
    return (((diff1 == 0) || (diff1 == 2)) && ((diff2 == 0) || (diff2 == 1)));
}

int validateDate(uint8_t day, uint8_t month, uint8_t year, uint8_t hour,
        uint8_t minute, uint8_t second) {

    //Validando dia
    if ((day < 1) || (day > 31)) {
        return 0;
    }
    //Validando m�s
    if ((month < 1) || (month > 12)) {
        return 0;
    }
    //Validando ano
    if ((year < 10) || (year > 99)) {
        return 0;
    }
    //Validando hora, minuto e segundo...
    if ((hour > 23) || (minute > 59) || (second > 59)) {
        return 0;
    }

    //Verifica meses com apenas 30 dias...
    if ((month == 4) || (month == 6) || (month == 9) || (month == 11)) {
        if (day > 30) {
            return 0;
        }
    }

    //Verificando fevereiro...
    if (month == 2) {
        if ((year % 4) == 0) { // Ano bissexto
            if (day > 29) {
                return 0;
            }
        } else {
            if (day > 28) {
                return 0;
            }
        }
    }
    return 1; //OK data e hora ok
}

int validDateTime(char* dateTime) {
    register int idx = 0; //idx auxiliar

    char temp[64] = "";
    removeInvalidChar(dateTime, temp, '\0', 4, ':', '/', '-', ' ');
    if (!isNumber(temp)) {
        return ERROR;
    }
    if (strlen(dateTime) >= 19) {
        int day, month, year, hour, minute, second;
        day = charToInt(dateTime[idx++]) * 10;
        day += charToInt(dateTime[idx++]);
        idx++; //pulando '/'
        month = charToInt(dateTime[idx++]) * 10;
        month += charToInt(dateTime[idx++]);
        idx++; //pulando '/'
        year = charToInt(dateTime[idx++]) * 1000;
        year += charToInt(dateTime[idx++]) * 100;
        year += charToInt(dateTime[idx++]) * 10;
        year += charToInt(dateTime[idx++]);
        idx++; //pulando ' '
        hour = charToInt(dateTime[idx++]) * 10;
        hour += charToInt(dateTime[idx++]);
        idx++; //pulando ':'
        minute = charToInt(dateTime[idx++]) * 10;
        minute += charToInt(dateTime[idx++]);
        idx++; //pulando ':'
        second = charToInt(dateTime[idx++]) * 10;
        second += charToInt(dateTime[idx++]);

        month = APPLY_LIMIT(month, 1, 12);
        switch (month) {
            case 2:
                day = APPLY_LIMIT(day, 1, 28);
                break; //fevereiro
            case 1: //janeiro
            case 3: //mar�o
            case 5: //maio
            case 7: //julho
            case 8: //agosto
            case 10: //outubro
            case 12:
                day = APPLY_LIMIT(day, 1, 31);
                break; //dezembro
            case 4: //abril
            case 6: //junho
            case 9: //setembro
            case 11:
                day = APPLY_LIMIT(day, 1, 30);
                break; //novembro
            default:
                return ERROR;
        }
        year = APPLY_LIMIT(year, 2000, 2099);
        hour = APPLY_LIMIT(hour, 0, 23);
        minute = APPLY_LIMIT(minute, 0, 59);
        second = APPLY_LIMIT(second, 0, 59);

        sprintf(dateTime, "%02d/%02d/%04d %02d:%02d:%02d", day, month, year,
                hour, minute, second);
        return OK;
    }
    return ERROR;
}

int validDate(char* date) {
    char dateTime[18] = "";
    char time[10] = " 00:00:00";
    strcat(dateTime, date);
    strcat(dateTime, time);
    if (validDateTime(dateTime) == OK) {
        unsigned int len = strlen(date);
        unsigned int i;
        len = (len > 10) ? 10 : len;
        for (i = 0; i < len; i++) {
            date[i] = dateTime[i];
        }
        return OK;
    } else
        return ERROR;
}

int validTime(char* time) {
    char dateTime[22] = "";
    sprintf(dateTime, "%02d/%02d/%04d ", 1, 1, 2000);
    strcat(dateTime, time);
    dateTime[21] = '\0';
    if (validDateTime(dateTime) == OK) {
        register int i;
        for (i = 0; i < 8; i++) {
            time[i] = dateTime[i + 11];
        }
        return OK;
    } else
        return ERROR;
}

int isBissexto(int year) {
    if (year % 400 == 0) //Ex: 1600, 2000, 2400...
        return 1;
    else if ((year % 4 == 0) && (year % 100 != 0)) //Ex: 2008, 2012, 2016...
        return 1;
    else
        return 0; //Ex: 2100, 2010, 2011 ...
}

int validateDateTm(struct tm* dateTime) {
    if (dateTime->tm_hour < 0 || dateTime->tm_hour > 23) {
        return DATE_FORMAT_ERROR_INVALID_DATE;
    }
    if (dateTime->tm_min < 0 || dateTime->tm_min > 59) {
        return DATE_FORMAT_ERROR_INVALID_DATE;
    }
    if (dateTime->tm_sec < 0 || dateTime->tm_sec > 59) {
        return DATE_FORMAT_ERROR_INVALID_DATE;
    }
    if (dateTime->tm_mon < 0 || dateTime->tm_mon > 11) {
        return DATE_FORMAT_ERROR_INVALID_DATE;
    }
    if (dateTime->tm_mday < 1 || dateTime->tm_mday > 31) {
        return DATE_FORMAT_ERROR_INVALID_DATE;
    }
    switch (dateTime->tm_mon + 1) {
        case 2:
            if (isBissexto(dateTime->tm_year + 1900)) {
                if (dateTime->tm_mday > 29) {
                    return DATE_FORMAT_ERROR_INVALID_DATE;
                }
            } else if (dateTime->tm_mday > 28) {
                return DATE_FORMAT_ERROR_INVALID_DATE;
            }
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            if (dateTime->tm_mday > 30) {
                return DATE_FORMAT_ERROR_INVALID_DATE;
            }
            break;
    }
    return DATE_FORMAT_OK;
}

/**
 * retorna n�mero de caracteres lidos ou erro. Em 'value' � retornado
 * valor inteiro lido
 */
static int integerStrToInt(char* str, int numMaxChar, int* value) {
    int charIdx = 0;
    *value = 0;
    while (charIdx < numMaxChar) {
        if (isdigit(str[charIdx])) {
            int temp = (str[charIdx++] - '0');
            int mult = (numMaxChar - charIdx);
            while (mult-- > 0)
                temp *= 10;
            *value += temp;
        } else if (charIdx > 0) {
            int mult = (numMaxChar - charIdx);
            while (mult-- > 0)
                *value /= 10;
            break;
        } else {
            charIdx = ERROR;
            break;
        }
    }
    return charIdx;
}

int dateStrToTm(struct tm* date, char* str, char* format) {
    int result = DATE_FORMAT_OK;
    memset(date, 0x00, sizeof (struct tm));

    //valida formato
    int strIdx = 0, fmtIdx = 0;
    while (str[strIdx] != '\0' && format[fmtIdx] != '\0' && result
            == DATE_FORMAT_OK) {
        switch (format[fmtIdx]) {
            case DATE_FORMAT_DAY_IDENTIFIER:
            { //'d' ou 'dd'
                int res = integerStrToInt(&str[strIdx], 2, &date->tm_mday);
                if (res > 0) {
                    strIdx += res;
                    fmtIdx++;
                    //se for 'dd'
                    if (format[fmtIdx] == DATE_FORMAT_DAY_IDENTIFIER) {
                        fmtIdx++;
                        if (res != 2)
                            result = DATE_FORMAT_ERROR_DOESNT_MATCH;
                    }
                } else {
                    result = DATE_FORMAT_ERROR_DOESNT_MATCH;
                }
            }
                break;
            case DATE_FORMAT_MONTH_IDENTIFIER:
            { //'M' ou 'MM'
                int res = integerStrToInt(&str[strIdx], 2, &date->tm_mon);
                if (res > 0) {
                    strIdx += res;
                    fmtIdx++;
                    //se for 'MM'
                    if (format[fmtIdx] == DATE_FORMAT_MONTH_IDENTIFIER) {
                        fmtIdx++;
                        if (res != 2)
                            result = DATE_FORMAT_ERROR_DOESNT_MATCH;
                    }
                    date->tm_mon -= 1;
                } else {
                    result = DATE_FORMAT_ERROR_DOESNT_MATCH;
                }
            }
                break;
            case DATE_FORMAT_YEAR_IDENTIFIER:
            { //'yy' ou 'yyy' ou 'yyyy'
                int charCount = 2;
                fmtIdx++;
                if (format[fmtIdx] == DATE_FORMAT_YEAR_IDENTIFIER) { //'yy'
                    fmtIdx++;
                    if (format[fmtIdx] == DATE_FORMAT_YEAR_IDENTIFIER) { //'yyy'
                        fmtIdx++;
                        charCount++;
                        if (format[fmtIdx] == DATE_FORMAT_YEAR_IDENTIFIER) { //'yyyy'
                            fmtIdx++;
                            charCount++;
                        }
                    }
                } else {
                    result = DATE_FORMAT_ERROR_DOESNT_MATCH;
                }
                if (result == DATE_FORMAT_OK) {
                    int res = integerStrToInt(&str[strIdx], charCount,
                            &date->tm_year);
                    if (res == charCount) {
                        strIdx += res;
                        if (charCount == 2) {
                            date->tm_year += 2000;
                        }
                        if (charCount == 3) {
                            date->tm_year += 2000;
                        }
                        date->tm_year -= 1900;
                    } else {
                        result = DATE_FORMAT_ERROR_DOESNT_MATCH;
                    }
                }
            }
                break;
            case DATE_FORMAT_HOUR_24H_IDENTIFIER:
            case DATE_FORMAT_HOUR_12H_IDENTIFIER:
            {//'H' ou 'HH' ou 'h' ou 'hh'
                int res = integerStrToInt(&str[strIdx], 2, &date->tm_hour);
                if (res > 0) {
                    strIdx += res;
                    fmtIdx++;
                    //se for 'HH' ou 'hh'
                    if (format[fmtIdx] == DATE_FORMAT_HOUR_12H_IDENTIFIER
                            || format[fmtIdx] == DATE_FORMAT_HOUR_24H_IDENTIFIER) {
                        fmtIdx++;
                        if (res != 2)
                            result = DATE_FORMAT_ERROR_DOESNT_MATCH;
                    }
                } else {
                    result = DATE_FORMAT_ERROR_DOESNT_MATCH;
                }
            }
                break;
            case DATE_FORMAT_MINUTE_IDENTIFIER:
            {//'m' ou 'mm'
                int res = integerStrToInt(&str[strIdx], 2, &date->tm_min);
                if (res > 0) {
                    strIdx += res;
                    fmtIdx++;
                    //se for 'mm'
                    if (format[fmtIdx] == DATE_FORMAT_MINUTE_IDENTIFIER) {
                        fmtIdx++;
                        if (res != 2)
                            result = DATE_FORMAT_ERROR_DOESNT_MATCH;
                    }
                } else {
                    result = DATE_FORMAT_ERROR_DOESNT_MATCH;
                }
            }
                break;
            case DATE_FORMAT_SECOND_IDENTIFIER:
            { // 's' ou 'ss'
                int res = integerStrToInt(&str[strIdx], 2, &date->tm_sec);
                if (res > 0) {
                    strIdx += res;
                    fmtIdx++;
                    //se for 'ss'
                    if (format[fmtIdx] == DATE_FORMAT_MINUTE_IDENTIFIER) {
                        fmtIdx++;
                        if (res != 2)
                            result = DATE_FORMAT_ERROR_DOESNT_MATCH;
                    }
                } else {
                    result = DATE_FORMAT_ERROR_DOESNT_MATCH;
                }
            }
                break;
            default:
            {
                if (str[strIdx++] != format[fmtIdx++]) {
                    result = DATE_FORMAT_ERROR_DOESNT_MATCH;
                }
            }
                break;
        }
    }

    //valida data
    if (result == DATE_FORMAT_OK) {
        result = validateDateTm(date);
    }

    return result;
}

int dateTmToStr(struct tm* date, char* str, int strSize, char* format) {
    int result = DATE_FORMAT_OK;
    int strIdx = 0, fmtIdx = 0;
    char mask[32] = "";
    char temp[32] = "";
    while (strIdx < strSize && format[fmtIdx] != '\0' && result
            == DATE_FORMAT_OK) {
        switch (format[fmtIdx]) {
            case DATE_FORMAT_DAY_IDENTIFIER:
            { //'d' ou 'dd'
                fmtIdx++;
                //se for 'dd'
                if (format[fmtIdx] == DATE_FORMAT_DAY_IDENTIFIER) {
                    fmtIdx++;
                    sprintf(mask, "%%02u");
                } else {
                    sprintf(mask, "%%u");
                }
                sprintf(temp, mask, date->tm_mday % 100);
                int i = 0;
                while (temp[i] != 0 && strIdx < strSize) {
                    str[strIdx++] = temp[i++];
                }
            }
                break;
            case DATE_FORMAT_MONTH_IDENTIFIER:
            { //'M' ou 'MM'
                fmtIdx++;
                //se for 'MM'
                if (format[fmtIdx] == DATE_FORMAT_MONTH_IDENTIFIER) {
                    fmtIdx++;
                    sprintf(mask, "%%02u");
                } else {
                    sprintf(mask, "%%u");
                }
                sprintf(temp, mask, (date->tm_mon + 1) % 100);
                int i = 0;
                while (temp[i] != 0 && strIdx < strSize) {
                    str[strIdx++] = temp[i++];
                }
            }
                break;
            case DATE_FORMAT_YEAR_IDENTIFIER:
            { //'yy' ou 'yyy' ou 'yyyy'
                int charCount = 2;
                fmtIdx++;
                if (format[fmtIdx] == DATE_FORMAT_YEAR_IDENTIFIER) { //'yy'
                    fmtIdx++;
                    if (format[fmtIdx] == DATE_FORMAT_YEAR_IDENTIFIER) { //'yyy'
                        fmtIdx++;
                        charCount++;
                        if (format[fmtIdx] == DATE_FORMAT_YEAR_IDENTIFIER) { //'yyyy'
                            fmtIdx++;
                            charCount++;
                        }
                    }
                } else {
                    result = DATE_FORMAT_ERROR_DOESNT_MATCH;
                }
                if (result == DATE_FORMAT_OK) {
                    sprintf(mask, "%%0%du", charCount);

                    if (charCount == 2) {
                        sprintf(temp, mask, (date->tm_year + 1900) % 100);
                    } else if (charCount == 3) {
                        sprintf(temp, mask, (date->tm_year + 1900) % 1000);
                    } else if (charCount == 4) {
                        sprintf(temp, mask, (date->tm_year + 1900));
                    }

                    int i = 0;
                    while (temp[i] != 0 && strIdx < strSize) {
                        str[strIdx++] = temp[i++];
                    }
                }
            }
                break;
            case DATE_FORMAT_HOUR_24H_IDENTIFIER:
            case DATE_FORMAT_HOUR_12H_IDENTIFIER:
            {//'H' ou 'HH' ou 'h' ou 'hh'
                fmtIdx++;
                //se for 'hh' ou 'HH'
                if (format[fmtIdx] == DATE_FORMAT_HOUR_12H_IDENTIFIER
                        || format[fmtIdx] == DATE_FORMAT_HOUR_24H_IDENTIFIER) {
                    fmtIdx++;
                    sprintf(mask, "%%02u");
                } else {
                    sprintf(mask, "%%u");
                }
                sprintf(temp, mask, date->tm_hour % 100);
                int i = 0;
                while (temp[i] != 0 && strIdx < strSize) {
                    str[strIdx++] = temp[i++];
                }
            }
                break;
            case DATE_FORMAT_MINUTE_IDENTIFIER:
            {//'m' ou 'mm'
                fmtIdx++;
                //se for 'mm'
                if (format[fmtIdx] == DATE_FORMAT_MINUTE_IDENTIFIER) {
                    fmtIdx++;
                    sprintf(mask, "%%02u");
                } else {
                    sprintf(mask, "%%u");
                }
                sprintf(temp, mask, date->tm_min % 100);
                int i = 0;
                while (temp[i] != 0 && strIdx < strSize) {
                    str[strIdx++] = temp[i++];
                }
            }
                break;
            case DATE_FORMAT_SECOND_IDENTIFIER:
            { // 's' ou 'ss'
                fmtIdx++;
                //se for 'ss'
                if (format[fmtIdx] == DATE_FORMAT_SECOND_IDENTIFIER) {
                    fmtIdx++;
                    sprintf(mask, "%%02u");
                } else {
                    sprintf(mask, "%%u");
                }
                sprintf(temp, mask, date->tm_sec % 100);
                int i = 0;
                while (temp[i] != 0 && strIdx < strSize) {
                    str[strIdx++] = temp[i++];
                }
            }
                break;
            default:
            {
                str[strIdx++] = format[fmtIdx++];
            }
                break;
        }
    }

    //insere final de string
    if (strIdx < strSize) {
        str[strIdx] = '\0';
    } else {
        str[strSize - 1] = '\0';
    }

    return result;
}

void makeDateOffset(struct tm* date, int dayOffset, int monthOffset,
        int yearOffset, int hourOffset, int minuteOffset, int secondOffset) {
    //atualiza data a partir dos offsets de dia, hora, minuto e segundo
    //TODO- verificar se mktime n�o vai ocasionar problemas de convers�o
    time_t now = mktime(date);
    now += (dayOffset * 86400 + hourOffset * 3600 + minuteOffset * 60
            + secondOffset);
    struct tm* timeinfo = localtime(&now);
    memcpy(date, timeinfo, sizeof (struct tm));

    //atualiza m�s
    int month = date->tm_mon + 1 + monthOffset;
    while (month > 12) {
        date->tm_year++;
        month -= 12;
    }
    if (month < 1) {
        month *= -1;
        while (month > 12) {
            date->tm_year--;
            month -= 12;
        }
        month = 12 - month;
    }
    date->tm_mon = month - 1;

    //atualiza ano
    date->tm_year += yearOffset;

    //verifica e corrige data
    fixDate(date);
}

void fixDate(struct tm* date) {

    date->tm_year = APPLY_LIMIT(date->tm_year + 1900, 2000, 2099) - 1900;
    date->tm_hour = APPLY_LIMIT(date->tm_hour, 0, 23);
    date->tm_min = APPLY_LIMIT(date->tm_min, 0, 59);
    date->tm_sec = APPLY_LIMIT(date->tm_sec, 0, 59);

    switch (date->tm_mon + 1) {
        case 2:
        {
            if (isBissexto(date->tm_year + 1900)) {
                date->tm_mday = APPLY_LIMIT(date->tm_mday, 1, 29);
            } else {
                date->tm_mday = APPLY_LIMIT(date->tm_mday, 1, 28);
            }
        }
            break; //fevereiro
        case 1: //janeiro
        case 3: //mar�o
        case 5: //maio
        case 7: //julho
        case 8: //agosto
        case 10: //outubro
        case 12:
            date->tm_mday = APPLY_LIMIT(date->tm_mday, 1, 31);
            break; //dezembro
        case 4: //abril
        case 6: //junho
        case 9: //setembro
        case 11:
            date->tm_mday = APPLY_LIMIT(date->tm_mday, 1, 30);
            break; //novembro
        default:
            date->tm_mday = 1;
            date->tm_mon = 0;
            break;
    }
}

char* getActualDayOfWeekStr(struct tm* date) {
    mktime(date);
    return getDayOfWeekStr(date->tm_wday);
}

char* getDayOfWeekStr(int dayOfWeek) {
    switch (dayOfWeek) {
        case 0:
            return DATE_WEEKDAY_SUNDAY_STR;
        case 1:
            return DATE_WEEKDAY_MONDAY_STR;
        case 2:
            return DATE_WEEKDAY_TUESDAY_STR;
        case 3:
            return DATE_WEEKDAY_WEDNESDAY_STR;
        case 4:
            return DATE_WEEKDAY_THURSDAY_STR;
        case 5:
            return DATE_WEEKDAY_FRIDAY_STR;
        case 6:
            return DATE_WEEKDAY_SATURDAY_STR;
        default:
            return (char*)"";
    }
}

int base64_decode(char* data, int dataSize, uint8_t* decodedData,
        int decodedDataSize) {
    // http://kevin.vanzonneveld.net
    // +   original by: Tyler Akins (http://rumkin.com)
    // +   improved by: Thunder.m
    // +      input by: Aman Gupta
    // +   improved by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
    // +   bugfixed by: Onno Marsman
    // +   bugfixed by: Pellentesque Malesuada
    // +   improved by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
    // +      input by: Brett Zamir (http://brett-zamir.me)
    // +   bugfixed by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
    // *     example 1: base64_decode('S2V2aW4gdmFuIFpvbm5ldmVsZA==');
    // *     returns 1: 'Kevin van Zonneveld'
    // mozilla has this native
    // - but breaks in 2.0.0.12!
    //if (typeof this.window['atob'] == 'function') {
    //    return atob(data);
    //}
    char b64[72] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    u_char o1, o2, o3;
    uint h1, h2, h3, h4;
    uint bits, i = 0, ac = 0;

    if (!data) {
        return ERROR;
    } else {
        while (i < dataSize && ac < decodedDataSize) { // unpack four hexets into three octets using index points in b64
            for (h1 = 0; h1 < 64; h1++) {
                if (data[i] == b64[h1])
                    break;
            }
            i++;
            for (h2 = 0; h2 < 64 && i < dataSize; h2++) {
                if (data[i] == b64[h2])
                    break;
            }
            i++;
            for (h3 = 0; h3 < 64 && i < dataSize; h3++) {
                if (data[i] == b64[h3])
                    break;
            }
            i++;
            for (h4 = 0; h4 < 64 && i < dataSize; h4++) {
                if (data[i] == b64[h4])
                    break;
            }
            i++;

            bits = h1 << 18 | h2 << 12 | h3 << 6 | h4;

            o1 = bits >> 16 & 0xff;
            o2 = bits >> 8 & 0xff;
            o3 = bits & 0xff;

            if (h3 == 64) {
                decodedData[ac++] = o1;
            } else if (h4 == 64) {
                decodedData[ac++] = o1;
                if (ac < decodedDataSize)
                    decodedData[ac++] = o2;
            } else {
                decodedData[ac++] = o1;
                if (ac < decodedDataSize)
                    decodedData[ac++] = o2;
                if (ac < decodedDataSize)
                    decodedData[ac++] = o3;
            }
        }
    }
    return ac;
}

int base64_encode(uint8_t* data, int dataSize, char* encodedData,
        int encodedDataSize) {
    // http://kevin.vanzonneveld.net
    // +   original by: Tyler Akins (http://rumkin.com)
    // +   improved by: Bayron Guevara
    // +   improved by: Thunder.m
    // +   improved by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
    // +   bugfixed by: Pellentesque Malesuada
    // +   improved by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
    // +   improved by: Rafal Kukawski (http://kukawski.pl)
    // *     example 1: base64_encode('Kevin van Zonneveld');
    // *     returns 1: 'S2V2aW4gdmFuIFpvbm5ldmVsZA=='
    // mozilla has this native
    // - but breaks in 2.0.0.12!
    //if (typeof this.window['btoa'] == 'function') {
    //    return btoa(data);
    //}
    char b64[72] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    u_char o1 = 0, o2 = 0, o3 = 0;
    uint h1, h2, h3, h4;
    uint bits, i = 0, ac = 0;

    if ((!data) || (encodedDataSize < (dataSize * 3 / 4))) {
        return ERROR;
    } else {
        do {
            o1 = (i < dataSize) ? data[i++] : 0;
            o2 = (i < dataSize) ? data[i++] : 0;
            o3 = (i < dataSize) ? data[i++] : 0;

            bits = (o1 << 16) | (o2 << 8) | o3;

            h1 = (bits >> 18) & 0x3f;
            h2 = (bits >> 12) & 0x3f;
            h3 = (bits >> 6) & 0x3f;
            h4 = bits & 0x3f;

            // use hexets to index into b64, and append result to encoded string
            encodedData[ac++] = b64[h1];
            encodedData[ac++] = b64[h2];
            encodedData[ac++] = b64[h3];
            encodedData[ac++] = b64[h4];
        } while (i < dataSize);

        encodedData[ac] = '\0';
        if ((i % 3) != 0) {
            encodedData[ac - 1] = '=';
            i++;
        }
        if ((i % 3) != 0) {
            encodedData[ac - 2] = '=';
            i++;
        }
        if ((i % 3) != 0) {
            encodedData[ac - 3] = '=';
            i++;
        }
    }

    return ac;
}

int strToHex(char c) {
    if ((c >= '0') && (c <= '9')) {
        return c - 48;
    } else if ((c >= 'A') && (c <= 'F')) {
        return c - 55;
    } else if ((c >= 'a') && (c <= 'f')) {
        return c - 87;
    }
    return 0;
}

//data deve conter um numero par de caracteres

void hex_decode(char* data, int dataSize, uint8_t* decodedData,
        int decodedDataSize) {
    if (dataSize) {
        int i, j;
        j = 0;
        for (i = 0; (i < (dataSize - 1)) && (j < decodedDataSize); i += 2) {
            decodedData[j++] = (strToHex(data[i]) << 4) + strToHex(data[i + 1]);
        }
    }
}

void hex_encode(uint8_t* data, int dataSize, char* encodedData,
        int encodedDataSize) {
    if (encodedDataSize) {
        int i, j;

        j = 0;
        for (i = 0; (i < dataSize) && (j < (encodedDataSize - 1)); i++) {
            sprintf(&encodedData[j], "%02X", data[i]);
            j += 2;
        }
    }
}

int base32_decode(const uint8_t *encoded, int encodedSize, uint8_t *result,
        int bufSize) {
    int buffer = 0;
    int bitsLeft = 0;
    int count = 0;
    int i;
    for (i = 0; (count < bufSize) && (i < encodedSize); i++) {
        uint8_t ch = encoded[i];
        if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' || ch == '-') {
            continue;
        }
        buffer <<= 5;

        // Deal with commonly mistyped characters
        if (ch == '0') {
            ch = 'O';
        } else if (ch == '1') {
            ch = 'L';
        } else if (ch == '8') {
            ch = 'B';
        }

        // Look up one base32 digit
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            ch = (ch & 0x1F) - 1;
        } else if (ch >= '2' && ch <= '7') {
            ch -= '2' - 26;
        } else {
            return -1;
        }

        buffer |= ch;
        bitsLeft += 5;
        if (bitsLeft >= 8) {
            result[count++] = buffer >> (bitsLeft - 8);
            bitsLeft -= 8;
        }
    }
    if (count < bufSize) {
        result[count] = '\000';
    }
    return count;
}

int base32_encode(const uint8_t *data, int length, uint8_t *result, int bufSize) {
    if (length < 0 || length > (1 << 28)) {
        return -1;
    }
    int count = 0;
    if (length > 0) {
        int buffer = data[0];
        int next = 1;
        int bitsLeft = 8;
        while (count < bufSize && (bitsLeft > 0 || next < length)) {
            if (bitsLeft < 5) {
                if (next < length) {
                    buffer <<= 8;
                    buffer |= data[next++] & 0xFF;
                    bitsLeft += 8;
                } else {
                    int pad = 5 - bitsLeft;
                    buffer <<= pad;
                    bitsLeft += pad;
                }
            }
            int index = 0x1F & (buffer >> (bitsLeft - 5));
            bitsLeft -= 5;
            result[count++] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567"[index];
        }
    }
    if (count < bufSize) {
        result[count] = '\000';
    }
    return count;
}

//transformacao de string para uint32
//  1) evita a utilizacao de buffer auxiliar
//  2) se nao for numero retorna ERRO

int str_to_uint8(const char* string, size_t size, uint8_t* uint) {
    int res = 1;
    if (size > 0) {
        size_t i = 0;
        *uint = 0;
        //verifica se tem negativo
        if (string[0] == '-') {
            res = 0;
        } else {
            //verifica se é tudo digito
            for (i = 0; i < size; i++) {
                if (!isdigit(string[i])) {
                    res = 0;
                    break;
                }
            }
            if (res == 1) {
                //transforma em uint8
                for (i = 0; i < size; i++) {
                    *uint = (10 * (*uint)) + (string[i] - '0');
                }
            }
        }
    } else {
        res = 0;
    }
    return res;
}

//transformacao de string para uint16
//  1) evita a utilizacao de buffer auxiliar
//  2) se nao for numero retorna ERRO

int str_to_uint16(const char* string, size_t size, uint16_t* uint) {
    int res = 1;
    if (size > 0) {
        size_t i = 0;
        *uint = 0;
        //verifica se tem negativo
        if (string[0] == '-') {
            res = 0;
        } else {
            //verifica se é tudo digito
            for (i = 0; i < size; i++) {
                if (!isdigit(string[i])) {
                    res = 0;
                    break;
                }
            }
            if (res == 1) {
                //transforma em uint16
                for (i = 0; i < size; i++) {
                    *uint = (10 * (*uint)) + (string[i] - '0');
                }
            }
        }
    } else {
        res = 0;
    }
    return res;
}

//transformacao de string para uint32
//  1) evita a utilizacao de buffer auxiliar
//  2) se nao for numero retorna ERRO

int str_to_uint32(const char* string, size_t size, uint32_t* uint) {
    int res = 1;
    if (size > 0) {
        size_t i = 0;
        *uint = 0;
        //verifica se tem negativo
        if (string[0] == '-') {
            res = 0;
        } else {
            //verifica se é tudo digito
            for (i = 0; i < size; i++) {
                if (!isdigit(string[i])) {
                    res = 0;
                    break;
                }
            }
            if (res == 1) {
                //transforma em uint32
                for (i = 0; i < size; i++) {
                    *uint = (10 * (*uint)) + (string[i] - '0');
                }
            }
        }
    } else {
        res = 0;
    }
    return res;
}
char char_hexToChar(char c) {
    if ((c >= 0) && (c <= 9)) {
        return c + 48;
    } else if ((c >= 0x0A) && (c <= 0x0F)) {
        return c + 87;
    }
    return 0;
}

uint8_t convertIntToBytes(const uint16_t dataToConvert, uint8_t*convertedBytes){
	
    uint8_t result;
    convertedBytes[0] = dataToConvert / 256;
	convertedBytes[1] = dataToConvert % 256;	
}

uint8_t convertBytesToInt(uint16_t *convertedData, const uint8_t*bytesToConvert){
	*convertedData = bytesToConvert[0] * 256 + bytesToConvert[1];
}

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
uint8_t mountPayloadPackage_16_t(uint8_t*payload, uint16_t*dataPackage, const uint16_t lenDataPackage){
	uint8_t result = EXIT_SUCCESS;
	uint16_t idx=0;
	uint8_t bytes[2] = "";
	for (idx=0; idx<lenDataPackage; idx++){
		convertIntToBytes(dataPackage[idx], bytes);	
		payload[idx*2] = bytes[0];
		payload[(idx*2)+1] = bytes[1];
	}
	return result;
}

/*
 * Method:  desmonta o pacote de dados do payload
 * 			converte os dados para int16
 *
 * Param: payload: 
 * Param: dataToSend: vetor de dados a serem recebidos...
 * Param: qttyData: tamanho do vetor de dados...
 *
 * return: ok or error
*/
uint8_t unmountPayloadPackage_16_t(uint8_t*payload, uint16_t*dataPackage, const uint16_t lenDataPackage){
	uint8_t result = EXIT_SUCCESS;
	uint16_t idx=0;
	uint8_t bytes[2] = "";
	for (idx=0; idx<lenDataPackage; idx++){
		bytes[0] = payload[idx*2];
		bytes[1] = payload[(idx*2)+1];
		convertBytesToInt(&dataPackage[idx], bytes);
	}
	return result;
}

/**
 * Converte cores rgb para escala de cinza
 * @param r
 * @param g
 * @param b
 * @return 
 */
/*
uint32_t bioImage_rgbToGray(uint8_t r, uint8_t g, uint8_t b){
    uint32_t gray;
    uint8_t aux;
    uint8_t bioColor = menu_getSystemStatus()->biometricConfig.bioColor;
        
    switch (bioColor) {
        case BIOMETRIC_LED_COLOR_GREEN:
            if (g < 0x7f) {
                aux = g * 2;
            } else {
                aux = 0xfe;
            } 
        break;
        case BIOMETRIC_LED_COLOR_BLUE:
            if (g < 0x7f) {
                aux = g * 2;
            } else {
                aux = 0xfe;
            } 
        break;
        case BIOMETRIC_LED_COLOR_RED:
            aux = g;
        break;
    
    }
        
    gray += aux << 16;
    gray += aux << 8;
    gray += aux << 0; 
    
    return gray;
}
*/
