
#include "Arduino.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Utils/strNum.h"

////////////////////////////////////////////////////////////
////
////	transforma numeros em char array
////
////	Retorna a quantidade de caracteres do num
////
////////////////////////////////////////////////////////////////
unsigned char numToStr(unsigned int number, char *getNumStr){
    int n = (log10(number) + 1);
	int i;
	unsigned char j=(n-1); // qtde de caracteres...
    for ( i = 0; i < n; ++i, number /= 10 ){
		getNumStr[j--] = (number % 10)+48;
    }
    return n;
}

////////////////////////////////////////////////////////////
////
////	transforma numeros em char array e se a quantidade
////	de caracteres for menor que elementQtty, completa 
////	com zeros (retorna se conseguiu ou nao completar)
////	com zeros.
////
////	Retorna a quantidade de caracteres do num
////
////////////////////////////////////////////////////////////////
char numToStrCompleteWithZero(unsigned int number, char *getNumStr, const int elementQtty){
    
 	char result=EXIT_FAILURE;   
    char strAux[elementQtty];
    int idx=0;
    unsigned char getQtdeChar=0;
    memset(strAux, 0, elementQtty);
	getQtdeChar = numToStr(number, getNumStr);
	if(elementQtty<=getQtdeChar){
		result=EXIT_FAILURE;
		#if DEBUG_STR_NUM 
			printf("Retornou erro de tamanho...\r\n");
		#endif
	}else{
		#if DEBUG_STR_NUM 
			printf("A string num: %s\r\n", getNumStr);
		#endif
		for (idx=0; idx<(elementQtty-getQtdeChar); idx++){
			strAux[idx]='0';
		}
		#if DEBUG_STR_NUM 
			printf("A string aux: %s\r\n", strAux);
		#endif
		strcat(strAux, getNumStr);
		#if DEBUG_STR_NUM 
			printf("2 - A string aux: %s\r\n", strAux);
		#endif
		memcpy(getNumStr, strAux, elementQtty);
		#if DEBUG_STR_NUM 
			printf("A string: %s\r\n", getNumStr);
		#endif
		result=EXIT_SUCCESS;
	}
	return result;
}