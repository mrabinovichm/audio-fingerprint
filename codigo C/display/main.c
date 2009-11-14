#include "lcd16x2.h"

unsigned char dsp_afp[]   = "DSP 2009        AUDIOFINGERPRINT";

unsigned char busq[]      = "Buscando...";
unsigned char h_enc[]     = "Huella          encontrada";
unsigned char h_no_enc[]  = "Huella          no encontrada";

unsigned char enya[]      = "Enya: Only Time";
unsigned char oasis[]     = "Oasis:          Headshrinker";
unsigned char van_halen[] = "Van Halen:      Erupsion";

void dato_lcd(unsigned char *dato, short len_dato);

int main()
{
	short len;

	init_gpio();	
	init_lcd();

  	len = strlen((char *)dsp_afp);
	dato_lcd(dsp_afp, len);
	delay(10000);
	write_lcd(CLEAR, CTRL_WR);	    	/*comando Clear Dply*/
	delay(100);  				    	/*esperar 10ms*/
  	len = strlen((char *)enya);
	dato_lcd(enya, len);
	delay(10000);
	write_lcd(CLEAR, CTRL_WR);	    	/*comando Clear Dply*/
	delay(100);  				    	/*esperar 10ms*/
  	len = strlen((char *)h_no_enc); 		                   
	dato_lcd(h_no_enc, len);
	delay(10000);
	write_lcd(CLEAR, CTRL_WR);	    	/*comando Clear Dply*/
	delay(100);  				    	/*esperar 10ms*/
  	len = strlen((char *)busq); 		                   
	dato_lcd(busq, len);

}/*Fin main*/

