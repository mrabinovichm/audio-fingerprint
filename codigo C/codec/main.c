#include "cs4215.h"
#include "loopback.h"
#include "int.h"

_circ _fract buffer_in0[S];
_circ _fract buffer_in1[S];
_circ _fract buffer_in2[S];
extern _circ _fract *ptr_buffer;
_fract *ptr_fin;


int main(void)
{
   	short bandera = 0;			  //valores de bandera 0, 1, o 2
	
	inicializacion();			  //inicializa el TIO0
	ssi_init(); 				  //inicializa codec
    enable_interrupts();
    		
	for(;;) 
	{
		switch(bandera)
		{
			case 0 : ptr_buffer = &buffer_in0;
					 break;
			case 1 : ptr_buffer = &buffer_in1;
					 break;
			case 2 : ptr_buffer = &buffer_in2;
					 break;
			default: break;
		}
		ptr_fin = ptr_buffer + S-1;
		while(ptr_buffer <= ptr_fin);
		bandera++;
		bandera = bandera % 3;
	}

}