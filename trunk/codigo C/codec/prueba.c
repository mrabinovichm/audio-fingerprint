#include "cs4215.h"
#include "loopback.h"

_fract buffer_in0[S];
_fract buffer_in1[S];
_fract buffer_in2[S];
extern _fract *ptr_buffer;
_fract *ptr_fin;


int main(void)
{
   	short bandera = 0;			  //valores de bandera 0, 1, o 2
	
	ssi_init(); 				  //inicializa codec
    		
	for(;;) 
	{

		switch(bandera)
		{
			case 0 : ptr_buffer = buffer_in0;
					 break;
			case 1 : ptr_buffer = buffer_in1;
					 break;
			case 2 : ptr_buffer = buffer_in2;
					 break;
			default: break;
		}												   
		
		ptr_fin = ptr_buffer + S;
		
		while(ptr_buffer < ptr_fin);

		bandera++;
		bandera = bandera % 3;
	}  
}