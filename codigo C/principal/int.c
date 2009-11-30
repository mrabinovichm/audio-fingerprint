#include "int.h"

void init_sw(void)
{
	//configuracion de prioridades de interrupcion
	IPRC.B.IAL =1;
	IPRC.B.IDL =1;

	//configuracion de timer como GPIO
	TCSR0.B.TEN   =0; 	//deshabilita el timer
	TCSR0.B.TCTRL =0; 	//modo 0 GPIO
	TCSR0.B.TINV  =0; 	//apaga el inversor a la salida
	TCSR0.B.TDIR  =1; 	//configura DO como salida
	TCSR0.B.TDO   =0;	//salida a cero (led D12 apagado)

	//el resto quiero que valga cero (no me importan)
	TCSR0.B.TOIE =0;
	TCSR0.B.TCIE =0;
	TCSR0.B.TRM	 =0;
	TCSR0.B.TDI	 =0;
	TCSR0.B.TPCE =0;
	TCSR0.B.TOF	 =0;
	TCSR0.B.TCF	 =0;
}


void _long_interrupt(IRQ_A) switch2(void)
{
	//se apreto el SW2
	TCSR0.B.TDO =ON;		//led D12 ON
	sw2 = 1;
}

/* void _fast_interrupt(IRQ_D) switch3(void)
{
	//se apreto el SW3
	TCSR0.B.TDO =OFF;		//led D12 OFF	
}  */