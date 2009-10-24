//**********************************************************************************************************
//*************** Algoritmo para calcular la frecuencia fundamental de una señal de audio ******************
//**********************************************************************************************************

#include <reg56303.h>
#include "cs4215.h"
#include "zcr_func.h"

//**********************************************************************************************************
//Definicion de parametros  

	fs = 48000;								//frecuencia de muestreo del codec	
	tr_c = 5*10^(-3);                       //intervalo de 5ms 
	tr_g = 15*10^(-3);                      //intervalo de 15ms
	L = 3;                                  //3 segundos de señal para generar su huella
  
//**********************************************************************************************************

//llamar a funciones del codec

//falta hacer el  main