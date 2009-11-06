#include "lcd16x2.h"

/*Inicializa el puerto B en modo GPIO*/
void init_gpio(void)
{
	HPCR.B.HGEN  = 1; /*  0: Host GPIO Port Enable                    */

	HPCR.B.HA8EN = 0; /*  1: Host Address Line 8 Enable               */
	HPCR.B.HA9EN = 0; /*  2: Host Address Line 9 Enable               */
	HPCR.B.HCSEN = 0; /*  3: Host Chip Select Enable                  */
	HPCR.B.HREN  = 0; /*  4: Host Request Enable                      */
	HPCR.B.HAEN  = 0; /*  5: Host Acknowledge Enable                  */
	HPCR.B.HEN   = 0; /*  6: Host Enable                              */

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


void delay(int factor)
{
	int i, j;
	
	for(i = 0;  i < factor;  i++)     /* factor*100 us total delay:*/
    {
        for(j = 0;  j < (int)(100*CPUCLK/(2*1E6));  j++)   /*100 us*/
        {
            _nop();
        }
    }
}

/*Inicializa el display LCD16x2, pag.45 HD44780U.pdf*/
void init_lcd(void)
{
	delay(150);  						/*esperar 15ms*/
	write_lcd(FUN_SET, CTRL);			/*comando Function set*/
	delay(50);  						/*esperar 5ms*/
	write_lcd(FUN_SET, CTRL);			/*comando Function set*/
	delay(1);  				    		/*esperar 100us*/
	write_lcd(FUN_SET, CTRL);			/*comando Function set*/
	delay(1);  				    		/*esperar 100us*/
	write_lcd(FUN_SET, CTRL);			/*comando Function set*/
	delay(1);  				    		/*esperar 100us*/
	write_lcd(DPLY_OFF, CTRL);	    	/*comando Dply off*/
	delay(1);  				    		/*esperar 100us*/
	write_lcd(CLEAR, CTRL);	    		/*comando Clear Dply*/
	delay(1);  				    		/*esperar 100us*/
	write_lcd(ETY_MOD_SET, CTRL);	    /*comando Entry mode set*/
}

/*Envia un comando de configuracion al display*/
void cmd_lcd(char comando)
{

}

/*Envia los datos que se escribiran en el display*/
void dato_lcd(char *datos)
{

}
