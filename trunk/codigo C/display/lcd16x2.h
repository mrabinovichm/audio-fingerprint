#ifndef LCD16x2_H
#define LCD16x2_H

#include <reg56303.h>

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


/*Inicializa el puerto B en modo GPIO*/
void init_gpio(void);

/*Funcion que maneja la escritura en la memoria del lcd*/
void write_lcd(char simbolo);

/*Inicializa el display LCD16x2*/
void init_lcd(void);

/*Envia un comando de configuracion al display*/
void cmd_lcd(char *comando);

/*Envia los datos pertinentes a cmd_lcd*/
char dato_lcd(char *datos);

#endif /*LCD16x2_H*/