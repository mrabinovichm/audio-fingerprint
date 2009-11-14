#ifndef LCD16x2_H
#define LCD16x2_H

#include <reg56303.h>
#include <string.h>

#ifndef CPUCLK
#define CPUCLK      67000000L   /* Hz */
#endif

#define LCD_16 16	   /*Long de una linea del Dply*/

/*Lineas de control RS, R/W, E y Backlight*/
#define CTRL_WR 0x4200 /*x10xx01x BL=1(backlight on), RS=0, R/W=0, E=1*/
#define CTRL_RD 0x4600 /*x10xx11x BL=1(backlight on), RS=0, R/W=1, E=1*/
#define DATO_WR	0x6200 /*x11xx01x BL=1(backlight on), RS=1, R/W=0, E=1*/
#define DATO_RD	0x6600 /*x11xx11x BL=1(backlight on), RS=1, R/W=1, E=1*/

/*Palabras de control del LCD16x2*/
#define CLEAR	      0x01 /*00000001 Borra Dply y vuelve cursor al inicio*/
#define RET_HOME      0x02 /*00000010 Contador de direcciones a cero*/
#define ETY_MOD_SET	  0x06 /*00000110 I/D=1 inc DDRAM, S=0 sin salto de Dply*/
#define DPLY_ON		  0x0C /*00001100 D=1 Dply on, C=0 sin cursor, B=0 sin blink*/
#define DPLY_OFF	  0x08 /*00001000 D=0 Dply off, C=0 sin cursor, B=0 sin blink*/
#define CSOR_SHFT  	  0x18 /*00011000 */
#define FUN_SET		  0x38 /*00111000 DL=1 8 bits, N=1 2_lineas, F=don't care*/
#define SDA_LIN		  0xC0 /*11000000 Posiciona el cursor en la 2da linea*/


/* typedef union            */
/* {                        */
/* 	struct{                 */
/* 			int bit0  : 1;  */
/* 			int bit1  : 1;  */
/* 			int bit2  : 1;  */
/* 			int bit3  : 1;  */
/* 			int bit4  : 1;  */
/* 			int bit5  : 1;  */
/* 			int bit6  : 1;  */
/* 			int bit7  : 1;  */
/* 			int bit8  : 1;  */
/* 			int bit9  : 1;  */
/* 			int bit10 : 1;  */
/* 			int bit11 : 1;  */
/* 			int bit12 : 1;  */
/* 			int bit13 : 1;  */
/* 			int bit14 : 1;  */
/* 			int bit15 : 1;  */
/* 	} bits;                 */
/*                          */
/* 	struct{                 */
/* 			int byte0  : 8; */
/* 			int byte1  : 8; */
/* 	} bytes;                */
/*                          */
/* 	int I;                  */
/*                          */
/* } REGISTRO_HDR;          */


/*Inicializa el puerto B en modo GPIO*/
void init_gpio(void);

/*Funcion que maneja la escritura en la memoria del lcd*/
void write_lcd(unsigned char simbolo, short ctrl_dat);

/*Lee un dato o el estado del Dply*/
//char read_lcd(char ctrl_dat);

/*Genera retardos multiplos de 100us*/
void delay(int factor);

/*Inicializa el display LCD16x2*/
void init_lcd(void);

/*Se fija si el Dply esta ocupado*/
//int busy(void);

/*Envia los datos que se escribiran en el display*/
void dato_lcd(unsigned char *dato, short len);

#endif /*LCD16x2_H*/