#include "lcd16x2.h"

const char busq[]     = "Buscando...";
const char h_enc[]    = "Huella          encontrada:";
const char h_no_enc[] = "Huella          no encontrada:";

const char enya[]      = "Enya: Only Time";
const char oasis[]     = "Oasis:          Headshrinker";
const char van_halen[] = "Van Halen:      Erupsion";

int main()
{
	int i, len;
	
	init_gpio();	
	init_lcd();


 	len = strlen(busq);                  
 	if(len <= LCD_16)                    
 	{                                    
 		for(i=0; i<len; i++)             
 		{                                
 			write_lcd(busq[i], DATO_WR); 
 		}                                
 	}                                    
 	else                                 
 	{                                    
 		for(i=0; i<LCD_16; i++)          
 		{                                
 			write_lcd(busq[i], DATO_WR); 
 		}                                
 		write_lcd(SDA_LIN, CTRL_WR);     
 		for(i=LCD_16; i<len; i++)        
 		{                                
 			write_lcd(busq[i], DATO_WR); 
 		}                                
}	                                 
	 
	delay(50000);
	HDR = 0x0200;

}