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


	HDDR = 0xFFFF;	  /*Configuro bits de I/O como salidas*/	
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

/*Lee un dato o el estado del Dply*/
char read_lcd(char ctrl_dat)                                                      
{                                                                                 
 	REGISTRO_HDR dato;                                                               
 	                                                                                 
 	HDDR = 0xFF00; 				 /*Configuro 8 bits de datos de I/O como entradas*/  
 	dato.bytes.byte1 = ctrl_dat; /*R/!W=1; E=1; RS= 0(ctrl), 1(dato); BL encendido*/ 
 	HDR = dato.I;                                                                    
 	dato.bits.bit1 = 0;		     /*flanco de bajada(E=0)*/                           
 	HDR = dato.I;                                                                    
 	dato.I = HDR;				 /*lee dato desde lcd*/                              
 	                                                                                 
 	HDDR = 0xFFFF;				 /*Configuro bits de I/O como salidas*/              
                                                                                   
 	return dato.bytes.byte0;                                                         
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
	write_lcd(FUN_SET, CTRL_WR);			/*comando Function set*/
	delay(50);  						/*esperar 5ms*/
	write_lcd(FUN_SET, CTRL_WR);			/*comando Function set*/
	delay(1);  				    		/*esperar 100us*/
	write_lcd(FUN_SET, CTRL_WR);			/*comando Function set*/
	delay(1);  				    		/*esperar 100us*/
	write_lcd(FUN_SET, CTRL_WR);			/*comando Function set*/
	delay(1);  				    		/*esperar 100us*/
	write_lcd(DPLY_OFF, CTRL_WR);	    	/*comando Dply off*/
	delay(1);  				    		/*esperar 100us*/
	write_lcd(CLEAR, CTRL_WR);	    		/*comando Clear Dply*/
	delay(1);  				    		/*esperar 100us*/
	write_lcd(ETY_MOD_SET, CTRL_WR);	    /*comando Entry mode set*/
}


/*Se fija si el Dply esta ocupado*/
int busy(void)                                                                                                      
{                                                                                                                   
  	int bf = 1;                                                                                                     
 	int i = 0;                                                                                                      
 	char status;                                                                                                    
  	status = read_lcd(CTRL_RD);                                                                                     
 	status = status & 0x80; 							/*me deja todo a 0 salvo el DB7 = BF*/                          
	if (status == 0x00)                                                                                             
  		return bf = 0;                                                                                              
  	else                                                                                                            
  		{                                                                                                           
  			while ((status != 0x00) || (i == 50000)) 	/*me quedo mientras este ocupado el lcd evitando el loop*/  
 				{                                                                                                      
  					status = read_lcd(CTRL_RD);                                                                     
  					status = status & 0x80; 			/*me deja todo a 0 salvo el DB7 = BF*/                      
  					i++;                                                                                            
  				}                                                                                                   
  			if (status == 0x00)                                                                                     
  				return bf = 0;                                                                                      
  			return bf;                                                                                              
  		}	                                                                                                        
}                                                                                                                    
                                                                                                                      
                                                                                                                      
/*Escribe una linea del Dply*/                                                                                       
void wr_linea(char *data, int len_lin)                                                                               
{                                                                                                                    
 	int i;                                                                                                              
 	for(i=0; i<len_lin; i++)                                                                                            
 	{                                                                                                                   
 		/*falta verificar ocupado*/                                                                                     
 		write_lcd(*(data+i), DATO_WR);                                                                                  
 	}                                                                                                                   
}                                                                                                                    
                                                                                                                      
/*Envia los datos que se escribiran en el display*/                                                                  
void dato_lcd(char *dato, int len_dato)                                                                              
{                                                                                                                    
	if(len_dato <= LCD_16)                                                                                              
		{                                                                                                               
 			wr_linea(dato, len_dato);   /*escribe solo una linea*/                                                      
 		}                                                                                                               
 	else                                                                                                                
 		{								/*escribe las dos lineas*/                                                      
 			wr_linea(dato, LCD_16);                                                                                     
			/*busy*/                                                                                                    
 			write_lcd(SDA_LIN, CTRL_WR);                                                                                
 			wr_linea(dato, (len_dato - LCD_16));                                                                        
 		}                                                                                                            
}                                                                                                                    
