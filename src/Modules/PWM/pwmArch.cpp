#include <Arduino.h>
#include "Modules/PWM/pwmArch.h"

#define PWM_ARCH_DEBUG 1
#ifndef PWM_ARCH_DEBUG
    #define PWM_ARCH_DEBUG 0
#endif /* PWM_ARCH_DEBUG */

// char pwmArch_setFrequencyUno(const int pin, const int divisor) {

//     char result = EXIT_FAILURE;
//     byte mode;

//     #if PWM_ARCH_DEBUG
//         Serial.println("Entrou aqui");
//     #endif /* DEBUG */

//     if(pin == 5 || pin == 6 || pin == 9 || pin == 10)
//     {
//         #if PWM_ARCH_DEBUG
//             Serial.println("pin 5 ou 10");
//         #endif /* DEBUG */

//         switch(divisor) {
//             case 1:     mode = 0x01; break;
//             case 8:     mode = 0x02; break;
//             case 64:    mode = 0x03; break;
//             case 256:   mode = 0x04; break;
//             case 1024:  mode = 0x05; break;
//             default:    return result; break;
//         }
//         if(pin == 5 || pin == 6) {
//             TCCR0B = (TCCR0B & 0b11111000) | mode;
//             result = EXIT_SUCCESS;
//         } else {
//             TCCR1B = (TCCR1B & 0b11111000) | mode;
//             result = EXIT_SUCCESS;
//         }
//     } else if(pin == 3 || pin == 11) {
//         #if PWM_ARCH_DEBUG
//             Serial.println("pin 3 ou 11");
//         #endif /* DEBUG */

//         switch(divisor) {
//             case 1:     mode = 0x01; break;
//             case 8:     mode = 0x02; break;
//             case 32:    mode = 0x03; break;
//             case 64:    mode = 0x04; break;
//             case 128:   mode = 0x05; break;
//             case 256:   mode = 0x06; break;
//             case 1024:  mode = 0x07; break;
//             default: return result;    break;
//         }
//         TCCR2B = (TCCR2B & 0b11111000) | mode;
//         result = EXIT_SUCCESS;
//     }
//     #if PWM_ARCH_DEBUG
//         Serial.println("Terminou");
//     #endif /* DEBUG */
//     return result;
// }
