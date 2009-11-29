#include "cs4215.h"
#include "loopback.h"
#include "lcd16x2.h"
#include "int.h"

#define T 3	/*cantidad de tramos de 5ms*/

/* ************ Mensajes a desplegar en display ******************** */
	unsigned char dsp_afp[]   = "    DSP 2009    AUDIOFINGERPRINT";
	unsigned char sw_2[]      = "  Presione SW2   para  comenzar ";
    unsigned char busq[]      = "Buscando...";
    unsigned char h_enc[]     = "Huella          encontrada";
	unsigned char h_no_enc[]  = "Huella          no encontrada";

	unsigned char enya[]      = "Enya: Only Time";
	unsigned char oasis[]     = "Oasis:          Headshrinker";
	unsigned char van_halen[] = "Van Halen:      Eruption";
/* ***************************************************************** */

/* ** Buffers y punteros para los datos de entrada desde el codec ** */
	_fract buffer_in0[S];
	_fract buffer_in1[S];
	_fract buffer_in2[S];

	extern _fract *ptr_buffer;
	_fract *ptr_fin;
	_fract *ptr_ini;
/* ***************************************************************** */

/* ******** Buffers y punteros para el manejo de huellas *********** */
	float huella[q];		/*muestras de frecuencias fundamentales*/
	float ceros_tramo[T];	/*cantidad de ceros en c/tramo de 5ms*/
	short tramo_listo;		/*flag que indica tramo lleno*/
	unsigned char *ptr_resp; /*nombre de cancion a enviar al display*/
/* ***************************************************************** */

	
int main(void)
{
   	short sw2 = 0;											/*sw=1 arranca la busqueda*/
	short resultado;							   /*0 = no encontrada, 1 = encontrada*/
	short len;										  /*largo de datos mandados al lcd*/
	short uso_buff;									  /*indica numero de buffer en uso*/
	short h_lista ; 						/*indica que la huella generada está lista*/		
	
/* ********* Inicializa puerto, display, switch2 y switch3 ********* */
	init_gpio();	
	init_lcd();
	init_sw ();
	ssi_init(); 				  									/*inicializa codec*/
	disable_interrupts();

    
  	len = strlen((char *)dsp_afp);							   /*mensaje de bienvenida*/
	dato_lcd(dsp_afp, len);
	delay(50000);														  /*esperar 5s*/
	write_lcd(CLEAR, CTRL_WR);	    							  /*comando Clear Dply*/
	delay(100);  				    									/*esperar 10ms*/
	
	for(;;) 
	{
		resultado = 0;
		uso_buff = 0;
		h_lista = 0;
		
		len = strlen((char *)sw_2);
		dato_lcd(sw_2, len);
		delay(100);
		while(!sw2);											  /*espero por switch2*/
		sw2 = 0;
		write_lcd(CLEAR, CTRL_WR);	    						  /*comando Clear Dply*/
		delay(100);  				    								/*esperar 10ms*/
		len = strlen((char *)busq); 		                   
		dato_lcd(busq, len);

/* *************************************************************************************
Calculo los ceros en 2 tramos de 5ms y luego el tercero dentro del loop
la funcion fundamentales() calcula la frecuencia fundamental de 3 tramos de
5ms c/u y la guarda en el arreglo huellas[]
************************************************************************************* */

		ptr_buffer = buffer_in0;						  /*inicializo puntero buffer0*/
		ptr_fin = ptr_buffer + S;
		ptr_ini = buffer_in0;
		enable_interrupts();
		while(ptr_buffer < ptr_fin);				   /*espero hasta llenar el buffer*/
		ptr_buffer = buffer_in1;						  /*inicializo puntero buffer1*/
		ptr_fin = ptr_buffer + S;
		ceros_tramo[1] = zcr(ptr_ini, S);						 /*ceros en un tramo 0*/
		ptr_ini = buffer_in1;
		while(ptr_buffer < ptr_fin);				   /*espero hasta llenar el buffer*/
		ptr_buffer = buffer_in2;						  /*inicializo puntero buffer1*/
		ptr_fin = ptr_buffer + S;
		ceros_tramo[2] = zcr(ptr_ini, S);						 /*ceros en un tramo 1*/
				
		while(!h_lista)
		{
			while(ptr_buffer < ptr_fin);			   /*espero hasta llenar el buffer*/
			switch(uso_buff)
			{
				case 0: ptr_buffer = buffer_in0;		  /*inicializo puntero buffer0*/
						ptr_ini = buffer_in2;
						break;
				case 1: ptr_buffer = buffer_in1;		  /*inicializo puntero buffer1*/
						ptr_ini = buffer_in0;
						break;
				case 2: ptr_buffer = buffer_in2;		  /*inicializo puntero buffer2*/
						ptr_ini = buffer_in1;
						break;
				default: break;
			}
			ptr_fin = ptr_buffer + S;
			ceros_tramo[uso_buff] = zcr(ptr_ini, S);	    	   /*ceros en un tramo*/
			h_lista = fundamentales();				  /*indica si la huella esta lista*/
			uso_buff++;
			uso_buff = uso_buff % 3;			
			
			
		}
		disable_interrupts();
		resultado = busqueda(huella);					  /*busca la huella en la base*/
	
		switch(resultado)
		{
			case 0 : len = strlen((char *)h_no_enc); 		                   
					 dato_lcd(h_no_enc, len);
					 break;
			case 1 : len = strlen((char *)h_enc); 		                   
					 dato_lcd(h_enc, len);
					 delay(20000);
					 write_lcd(CLEAR, CTRL_WR);	    			  /*comando Clear Dply*/
					 delay(100);  				    					/*esperar 10ms*/
					 len = 32; //strlen((char *) ----); 		                   
					 dato_lcd(ptr_resp, len);
					 break;
			default: len = strlen((char *)error); 		                   
					 dato_lcd(error, len);
					 break;
		}												   	
		delay(50000);
		write_lcd(CLEAR, CTRL_WR);	    						  /*comando Clear Dply*/
		delay(100);  				    								/*esperar 10ms*/	
	} /*Fin loop ppal*/ 
} /*Fin main*/