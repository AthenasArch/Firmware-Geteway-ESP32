#ifndef PWM_ARCH_H_
#define PWM_ARCH_H_

// * A frequência resultante é igual à frequência base dividida pelo divisor
// *
// * - Frequências base:
// * o A frequência base para os pinos (3, 9, 10 e 11)  = 31250 Hz.
// * o A frequência base para os pinos (5 e 6)          = 62500 Hz.
// *
// * - Divisores:
// * o Os divisores disponíveis nos pinos 5, 6, 9 e 10 são:
// * 1, 8, 64, 256 e 1024.
// *
// * o Os divisores disponíveis nos pinos 3 e 11 são:
// * 1, 8, 32, 64, 128, 256 e 1024.
// *
// * As frequências PWM estão ligadas em pares de pinos. Se um pino em um par
// * for alterado, o outro também será alterado para corresponder:
// * - Os pinos (5 e 6 ) são pareados no     - timer0
// * - Os pinos (9 e 10) são emparelhados no - timer1
// * - Os pinos (3 e 11) são emparelhados no - timer2
//
//
//
// * Observe que essa função terá efeitos colaterais em qualquer outra coisa
// * que use timers:
// * ******* delay () e millis ().
// * - As alterações nos pinos ( 3, 5, 6 ou 11) podem fazer com que as
// * funções [ delay () e millis () ] parem de funcionar.
// * Outras funções relacionadas ao tempo também podem ser afetadas.
//
// * ******* Servo
// * - Alterações nos pinos ( 9 ou 10 ) farão com que a biblioteca Servo funcione
// * incorretamente.
// *
// * Graças ao macegr dos fóruns do Arduino para sua documentação dos
// divisores de freqüência * PWM. Sua postagem pode ser visualizada em:
// * Https://forum.arduino.cc/index.php?topic=16612#msg121031
// * /
// *
//
// * Pinos recomendados para utilizar: 9 ou 10, pois noa utilizam contadores
// * de tempo...

// * o A frequência base para os pinos (3, 9, 10 e 11)  = 31250 Hz.
// * o A frequência base para os pinos (5 e 6)          = 62500 Hz.
// *
// * FREQUENCIA_PWM = (FREQ_BASE / DIV)
// * EX: FREQUENCIA_PWM = (31250 / PWM_DIV_1024) = 30,6 Hz
// *
#define PWM_DIV_1       0x01
#define PWM_DIV_8       0x08
#define PWM_DIV_32      0x20
#define PWM_DIV_64      0x40
#define PWM_DIV_128     0x80
#define PWM_DIV_256     0x100
#define PWM_DIV_1024    0x400


/*
 *  @Method: Seta a frequencia do modulo pwm.
 *
 *  @Param: pin - pino pwm utilizado.
 *  @Param: divisor - PWM_DIV_X.
 *
 *  @Return:  EXIT_FAILURE or EXIT_SUCCESS.
 */

char pwmArch_setFrequencyUno(const int pin, const int divisor);

#endif /* */
