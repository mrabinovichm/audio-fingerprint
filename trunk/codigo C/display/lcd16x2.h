#ifndef LCD16x2_H
#define LCD16x2_H

#include <reg56303.h>

#ifndef CPUCLK
#define CPUCLK      67000000L   /* Hz */
#endif

#define CTRL 0x42
#define DATO 0x62

typedef union 
{
	struct{
			int bit0  : 1;
			int bit1  : 1;
			int bit2  : 1;
			int bit3  : 1;
			int bit4  : 1;
			int bit5  : 1;
			int bit6  : 1;
			int bit7  : 1;
			int bit8  : 1;
			int bit9  : 1;
			int bit10 : 1;
			int bit11 : 1;
			int bit12 : 1;
			int bit13 : 1;
			int bit14 : 1;
			int bit15 : 1;
	} bits;

	struct{
			int byte0  : 8;
			int byte1  : 8;
	} bytes;

	int I;

} REGISTRO_HDR;

#define CLEAR	      0x01 /*00000001 Borra Dply y vuelve cursor al inicio*/
#define RET_HOME      0x02 /*00000010 Contador de direcciones a cero*/
#define ETY_MOD_SET	  0x06 /*00000110 I/D=1 inc DDRAM, S=0 sin salto de Dply*/
#define DPLY_ON		  0x0C /*00001100 D=1 Dply on, C=0 sin cursor, B=0 sin blink*/
#define DPLY_OFF	  0x08 /*00001000 D=0 Dply off, C=0 sin cursor, B=0 sin blink*/
#define CSOR_SHFT  	  0x18 /*00011000 */
#define FUN_SET		  0x38 /*00111000 DL=1 8 bits, N=1 2_lineas, F=don't care*/


/*Genera retardos multiplos de 100us*/
void delay(int factor);

/*Inicializa el puerto B en modo GPIO*/
void init_gpio(void);

/*Funcion que maneja la escritura en la memoria del lcd*/
void write_lcd(char simbolo, char ctrl_dat);

/*Inicializa el display LCD16x2*/
void init_lcd(void);

/*Envia un comando de configuracion al display*/
void cmd_lcd(char comando);

/*Envia los datos que se escribiran en el display*/
void dato_lcd(char *datos);

#endif /*LCD16x2_H*/