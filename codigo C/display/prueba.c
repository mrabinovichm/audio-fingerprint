#include "lcd16x2.h"

#define LARGO 	32

	 _Y unsigned char dsp_afp[]    = "DSP 2009        AUDIOFINGERPRINT";
	 _Y unsigned char sw_2[]       = "Presione SW2    para  comenzar  ";
	 _Y unsigned char busq[]       = "Buscando        huella...       ";
     _Y unsigned char h_enc[]      = "Huella          encontrada      ";
	 _Y unsigned char h_no_enc[]   = "Huella          no encontrada   ";
 	 _Y unsigned char error[]      = "Error                           ";
 	 
 	 _Y unsigned char enya[]       = "Enya:           Only Time       ";
	 _Y unsigned char oasis[]      = "Oasis:          Headshrinker    ";
	 _Y unsigned char van_halen[]  = "Van Halen:      Eruption        ";
	 _Y unsigned char losolima[]   = "Los Olima       Los dos Gallos  ";
	 _Y unsigned char zitarrosa[]  = "Zitarrosa:      A Jose Artigas  ";
	 _Y unsigned char curtidores[] = "Curtidores:     Cuple IMM       ";
	 _Y unsigned char mozart[]     = "Mozart:         Marcha Turca    ";
	 _Y unsigned char sodastereo[] = "Soda Stereo:    De Musica Ligera";

int main()
{
   	//short len;

	init_gpio();	
	init_lcd();

  	//len = strlen((char *)dsp_afp);
	dato_lcd(dsp_afp, LARGO);
	delay(1000);
	write_lcd(CLEAR, CTRL_WR);	    	/*comando Clear Dply*/
	delay(100);  				    	/*esperar 10ms*/
  	//len = strlen((char *)enya);
	dato_lcd(enya, LARGO);
	delay(1000);
	write_lcd(CLEAR, CTRL_WR);	    	/*comando Clear Dply*/
	delay(100);  				    	/*esperar 10ms*/
  	//len = strlen((char *)h_no_enc); 		                   
	dato_lcd(h_no_enc, LARGO);
	delay(1000);
	write_lcd(CLEAR, CTRL_WR);	    	/*comando Clear Dply*/
	delay(100);  				    	/*esperar 10ms*/
  	//len = strlen((char *)busq); 		                   
	dato_lcd(busq, LARGO);
	delay(3000);
	write_lcd(CLEAR, CTRL_WR);	    	/*comando Clear Dply*/
	delay(100);  				    	/*esperar 10ms*/
	write_lcd(DPLY_OFF, CTRL_WR);
	delay(1);  				    		/*esperar 100us*/
	HDR = 0x0000;

}/*Fin main*/

