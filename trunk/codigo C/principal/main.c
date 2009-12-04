#include "cs4215.h"
#include "loopback.h"
#include "lcd16x2.h"
#include "zcr_func.h"
#include "int.h"

#define LARGO 		32
#define NRO_HUELLAS 3


/* ***************** Mensajes a desplegar y sus largos en display ********************** */
	 _Y unsigned char dsp_afp[]   = "DSP 2009        AUDIOFINGERPRINT";
	 _Y unsigned char sw_2[]      = "Presione SW2    para  comenzar  ";
	 _Y unsigned char busq[]      = "Buscando        huella...       ";
     _Y unsigned char h_enc[]     = "Huella          encontrada      ";
	 _Y unsigned char h_no_enc[]  = "Huella          no encontrada   ";
 	 _Y unsigned char error[]     = "Error                           ";
 
 	 _Y unsigned char enya[]      = "Enya:           Only Time       ";
	 _Y unsigned char oasis[]     = "Oasis:          Headshrinker    ";
	 _Y unsigned char van_halen[] = "Van Halen:      Eruption        ";

	 _Y unsigned char *dply[NRO_HUELLAS] = {enya, oasis, van_halen};
/* ********************************************************************************** */

/* ********************** Base de datos de huellas conocidas ************************ */
  	 _Y float h_enya[q];
	 _Y float h_oasis[q];
	 _Y float h_van_halen[q];

	 _Y float *h_conocidas[NRO_HUELLAS] = {h_enya, h_oasis, h_van_halen};
/* ********************************************************************************** */

/* ********** Buffers y punteros para los datos de entrada desde el codec *********** */
	_fract _circ buffer_in0[S];
	_fract _circ buffer_in1[S];
	_fract _circ buffer_in2[S];

	_fract _circ buffer_aux[2*S];	   /*buffer auxiliar para no sobreescribir memoria*/
																 
	extern _fract _circ *ptr_buffer;
	_fract *ptr_fin;
	_fract *ptr_ini;
	
/* ********************************************************************************** */

/* ***************** Buffers y punteros para el manejo de huellas ******************* */
	float huella[q];		   				   /*muestras de frecuencias fundamentales*/
	int ceros_tramo[T];		   					 /*cantidad de ceros en c/tramo de 5ms*/
	_Y unsigned char *ptr_resp;   			   /*nombre de cancion a enviar al display*/
	extern float *ptr_huella;
	extern float *ptr_h_fin;
/* ********************************************************************************** */

extern short sw2;
	
int main(void)
{
	short resultado;							   /*0 = no encontrada, 1 = encontrada*/
	short uso_buff;									  /*indica numero de buffer en uso*/
	short h_lista ; 						/*indica que la huella generada está lista*/
			
/* ************** Inicializa puerto, display, switch2, interrupciones  ************** */
	init_gpio();						   /*inicializa puerto donde se conecta el lcd*/	
	init_lcd();								  /*inicializa el display, ver HD44780.pdf*/
	init_sw();										   /*inicializa switch 2 y led D12*/
  	ssi_init(); 				  									/*inicializa codec*/

    
	/*mensaje de bienvenida*/
disable_interrupts();
	dato_lcd(dsp_afp, LARGO);
	delay(5000);														  /*esperar 0.5s*/
	write_lcd(CLEAR, CTRL_WR);	    							  /*comando Clear Dply*/
	delay(100);  				    									/*esperar 10ms*/
	
	for(;;) 
	{
		sw2 = 0;
		resultado = -1;
		uso_buff = 0;
		h_lista = 0;
		ptr_huella = huella;				 /*inicio el puntero al arreglo de frec f0*/
		ptr_h_fin = ptr_huella + q;
		ptr_buffer = buffer_aux;			           

		dato_lcd(sw_2, LARGO);
		delay(1000);
		enable_interrupts();
		while(!sw2);									   /*sw2=1 arranca la busqueda*/
	 
disable_interrupts();
		write_lcd(CLEAR, CTRL_WR);	    						  /*comando Clear Dply*/
		delay(100);  				    								/*esperar 10ms*/
		dato_lcd(busq, LARGO);
enable_interrupts();

/* *************************************************************************************
Calculo los ceros en 2 tramos de 5ms y luego el tercero dentro del loop
la funcion fundamentales() calcula la frecuencia fundamental de 3 tramos de
5ms c/u y la guarda en el arreglo huellas[]
************************************************************************************* */

		ptr_buffer = buffer_in0;						  /*inicializo puntero buffer0*/
		ptr_fin = ptr_buffer + S;
		ptr_ini = buffer_in0;
		
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
			h_lista = fundamentales(ceros_tramo);	  /*indica si la huella esta lista*/
			uso_buff++;
			uso_buff = uso_buff % 3;			
		}
		disable_interrupts();
		resultado = busqueda(huella, (float **)h_conocidas, NRO_HUELLAS);
	
		write_lcd(CLEAR, CTRL_WR);	    						  /*comando Clear Dply*/
		delay(100);
		if(resultado != -1)
		{
			dato_lcd(h_enc, LARGO);                                                   
 			delay(20000);                                                              
 			write_lcd(CLEAR, CTRL_WR);	    			  		  /*comando Clear Dply*/        
 			delay(100);  				    					        /*esperar 10ms*/        
 			dato_lcd(dply[resultado], LARGO);
		}
		else
			dato_lcd(h_no_enc, LARGO);

/* 		switch(resultado)                                                                       */
/* 		{                                                                                       */
/* 			case 0 : dato_lcd(h_no_enc, LARGO);                                                 */
/* 					 break;                                                                     */
/* 			case 1 : dato_lcd(h_enc, LARGO);                                                    */
/* 					 delay(20000);                                                              */
/* 					 write_lcd(CLEAR, CTRL_WR);	    			  /*comando Clear Dply*/        
/* 					 delay(100);  				    					/*esperar 10ms*/        
/* 					 dato_lcd(ptr_resp, LARGO);                                                 */
/* 					 break;                                                                     */
/* 			default: dato_lcd(error, LARGO);                                                    */
/* 					 break;                                                                     */
/* 		}	                                                                                    */											   	
		delay(5000);
		write_lcd(CLEAR, CTRL_WR);	    						  /*comando Clear Dply*/
		delay(100);  				    								/*esperar 10ms*/
		TCSR0.B.TDO = OFF;							/*led D12 OFF, termina la busqueda*/
	} /*Fin loop ppal*/ 
} /*Fin main*/