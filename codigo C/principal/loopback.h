/*************************************************************************
 * funciones del CODEC usadas por el programa principal
 *************************************************************************/
#ifndef LOOPBACK_H
#define LOOPBACK_H	

#include <c56.h>
#include <reg56303.h>


#define OUTPOLARITY (-1)     /* invert audio output (56xxxEVM HDPHNE output)  */

#define FSAMPLE     48000    /* sampling frequency, Hz   */

#define ON  1
#define OFF 0
#define S   240				 /*a frecuencia fs=48Khz, intervalo de 5ms, son 240 muestras*/ 

#define disable_interrupts() _asm("ori   #$03,mr")
#define enable_interrupts()  _asm("andi  #$FC,mr")

typedef enum    { IN_LEFT,  IN_RIGHT,  IN_MAX  }        inbuf_t;
typedef enum    { OUT_LEFT, OUT_RIGHT, OUT_MAX }        outbuf_t;

void ssi_init(void);
void ssi_set_gains(void);
void ssi_enable_receive(int flag);
void ssi_toggle_indicator(void);
void ssi_loopback(void);

#endif /*LOOPBACK_H*/


/* END OF FILE */
	   