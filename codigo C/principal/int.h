#ifndef INT_H
#define INT_H

#include <reg56303.h>
#define ON 1
#define OFF 0

/* ************* Configura el Timer 0 como GPIO para usar los switch SW2, SW3 y el led D12 *************** */
void init_sw(void);

/* ****************** ISR para manejar las interrupciones del switch SW2 de la placa EVM ***************** */
void _long_interrupt(IRQ_A) switch2(void);

/* ****************** ISR para manejar las interrupciones del switch SW3 de la placa EVM ***************** */
/* void _fast_interrupt(IRQ_D) switch3(void); */

#endif /*INT_H*/