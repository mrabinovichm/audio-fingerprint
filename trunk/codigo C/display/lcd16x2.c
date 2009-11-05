#include "lcd16x2.h"

/*Inicializa el puerto B en modo GPIO*/
void init_gpio(void)
{
	HPCR.I.B.HGEN  = 1; /*  0: Host GPIO Port Enable                    */

	HPCR.I.B.HA8EN = 0; /*  1: Host Address Line 8 Enable               */
	HPCR.I.B.HA9EN = 0; /*  2: Host Address Line 9 Enable               */
	HPCR.I.B.HCSEN = 0; /*  3: Host Chip Select Enable                  */
	HPCR.I.B.HREN  = 0; /*  4: Host Request Enable                      */
	HPCR.I.B.HAEN  = 0; /*  5: Host Acknowledge Enable                  */
	HPCR.I.B.HEN   = 0; /*  6: Host Enable                              */

//Configuro bits de I/O como salidas
	HDDR = 0xFFFF;
}

void write_lcd(char simbolo, char ctrl_dat)
{
	REGISTRO_HDR dato;

	dato.bytes.byte0 = simbolo;  /*Caracter a escribir en lcd*/
	dato.bytes.byte1 = ctrl_dat; /*R/!W=0; E=1; RS= 0(ctrl), 1(dato); BL encendido*/
	HDR = dato.I;
	dato.bits.bit1 = 0;		     /*flanco de bajada(E=0)*/
	HDR = dato.I;				 /*graba char en lcd*/ 
}

/*Inicializa el display LCD16x2*/
void init_lcd(void)
{
	 
}

/*Envia un comando de configuracion al display*/
void cmd_lcd(char *comando)
{

}

/*Envia los datos pertinentes a cmd_lcd*/
char dato_lcd(char *datos)
{

}
