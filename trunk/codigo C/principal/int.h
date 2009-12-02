#ifndef INT_H
#define INT_H

#include <reg56303.h>
#define ON 1
#define OFF 0

void init_sw(void);

void _long_interrupt(IRQ_A) switch2(void);

/* void _fast_interrupt(IRQ_D) switch3(void); */

#endif /*INT_H*/