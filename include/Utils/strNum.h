#ifndef STR_NUM_H_
#define STR_NUM_H_

// #include "strNum.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// #define DEBUG_STR_NUM 1
#ifndef DEBUG_STR_NUM
	#define DEBUG_STR_NUM 0
#endif

unsigned char numToStr(unsigned int number, char *getNumStr);
char numToStrCompleteWithZero(unsigned int number, char *getNumStr, const int elementQtty);

#endif /* STR_NUM_H_ */ 
