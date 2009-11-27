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
	_fract *ptr;
/* ***************************************************************** */

/* ******** Buffers y punteros para el manejo de huellas *********** */
	float huella[q];	/*muestras de frecuencias fundamentales*/
	float tramos[T];	/*cantidad de ceros en c/tramo de 5ms*/
	short fg_tramo;		/*flag que indica tramos llenos*/
/* ***************************************************************** */

	
int main(void)
{
   	short bandera = 0;			/*indica que buffer llenar*/
	short sw2 = 0;				/*sw=1 arranca la busqueda*/
	short len;					/*largo de datos mandados al lcd*/
	
/* ********* Inicializa puerto, display, switch2 y switch3 ********* */
	init_gpio();	
	init_lcd();
	init_sw ();	
	ssi_init(); 				  		/*inicializa codec*/
	disable_interrupts();

    
  	len = strlen((char *)dsp_afp);
	dato_lcd(dsp_afp, len);
	delay(50000);						/*esperar 5s*/
	write_lcd(CLEAR, CTRL_WR);	    	/*comando Clear Dply*/
	delay(100);  				    	/*esperar 10ms*/
	
	for(;;) 
	{
		
	len = strlen((char *)sw_2);
	dato_lcd(sw_2, len);
	delay(100);
	while(!sw2);						/*espero por switch2*/
	sw2 = 0;
	write_lcd(CLEAR, CTRL_WR);	    	/*comando Clear Dply*/
	delay(100);  				    	/*esperar 10ms*/
	len = strlen((char *)busq); 		                   
	dato_lcd(busq, len);
	ptr_buffer = buffer_in0;			/*inicializo puntero*/
	enable_interrupts();
	
/*desde acá en adelante hay que modificar y agragar lo que falta*/

	switch(bandera)
	{
		case 0 : ptr_buffer = buffer_in0;
				 ptr = buffer_in0;
				 break;
		case 1 : ptr_buffer = buffer_in1;
				 ptr = buffer_in1;
				 break;
		case 2 : ptr_buffer = buffer_in2;
				 ptr = buffer_in2;
				 break;
		default: break;
	}												   
		
	ptr_fin = ptr_buffer + S;
		
	while(ptr_buffer < ptr_fin);

	bandera++;					/*para que ya empiece a llenar el siguiente buffer*/
	bandera = bandera % 3;		/*no estaría mal definir un #buffer = 3 en este caso*/
		
generador(ptr, S);	/*genera la huella de la señal de entrada*/
			

		
		
	
/*buscar la huella en la base de datos*/
		
/*desplegar mensaje en el display dependiendo de una bandera (si encontro o no)*/
	
	}  
}