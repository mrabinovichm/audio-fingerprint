#include "cs4215.h"
#include "loopback.h"

extern _circ _fract buffer_in[LARGO];
extern _circ _fract buffer_in2[LARGO];
extern _circ _fract *ptr_buffer;

char selec_buf = OFF;

int main(void)
{
	ptr_buffer = buffer_in;
	ssi_init(); 				//inicializa codec
    enable_interrupts();		//establece la prioridad del micro

	
	for(;;) 
	{

	}

}