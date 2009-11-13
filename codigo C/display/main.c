#include "lcd16x2.h"

const unsigned char dsp_afp[]   = "DSP 2009        AUDIOFINGERPRINT";

const unsigned char busq[]      = "Buscando...";
const unsigned char h_enc[]     = "Huella          encontrada:";
const unsigned char h_no_enc[]  = "Huella          no encontrada:";

const unsigned char enya[]      = "Enya: Only Time";
const unsigned char oasis[]     = "Oasis:          Headshrinker";
const unsigned char van_halen[] = "Van Halen:      Erupsion";


int main()
{
	int i, len;
	
	init_gpio();	
	init_lcd();

  	len = strlen(dsp_afp);                                                
 	if(len <= LCD_16)                                                  
  	{                                                                  
  		for(i=0; i<len; i++)                                           
  		{                                                              
  			write_lcd(dsp_afp[i], DATO_WR);                               
  			delay(1);  				    		/*esperar 100us*/      
  		}                                                              
  	}                                                                  
  	else                                                               
  	{                                                                  
  		for(i=0; i<LCD_16; i++)                                        
  		{                                                              
 			write_lcd(dsp_afp[i], DATO_WR);                               
  			delay(1);  				    		/*esperar 100us*/      
  		}                                                              
  		write_lcd(SDA_LIN, CTRL_WR);                                   
  		delay(1);  				    			/*esperar 100us*/      
 		for(i=LCD_16; i<len; i++)                                      
  		{                                                              
 			write_lcd(dsp_afp[i], DATO_WR);                               
 			delay(1);  				    		/*esperar 100us*/      
  		}                                                              
	}	                                                                   
}