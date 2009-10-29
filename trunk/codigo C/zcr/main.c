//**********************************************************************************************************
//*************** Algoritmo para calcular la frecuencia fundamental de una señal de audio ******************
//**********************************************************************************************************

#include <reg56303.h>
#include <cs4215.h>
#include "zcr_func.h"

//**********************************************************************************************************
	
//Definicion de parametros  

#define		fs 		48000						//frecuencia de muestreo del codec	
#define 	tr_g 	15/1000                   	//intervalo de ventana de calculo
#define 	tr_c 	5/1000                    	//intervalo de desplazamiento de la ventana 
#define 	L 		3                         	//3 segundos de señal para generar su huella
#define 	umbral	0.2					   		//umbral de decision al comparar huellas
#define 	W		720							//cantidad de muestras equivalentes a tr_g segundos
#define 	S		240							//cantidad de muestras equivalentes a tr_c segundos
#define  	q		597							//cantidad de muestras de fo

//Buffers y punteros

_fract 	_circ 	buffer_in[W];				   	//buffer de entrada de la señal
float 	_circ 	huella[q];					  	//arreglo de frecuencias fundamentales
											    

//**********************************************************************************************************


int main (void)
{
	int largo;
 
//Huellas guardadas calculadas con la herramienta SCILAB

	float enya[q];//			= {};
	float oasis[q];//			= {};
	float vanHalen[q];//		= {};


//Buffers y punteros

	_fract 	_circ 	*ptr_buffer = buffer_in;				   	//puntero al buffer de entrada circular
	float 	_circ	*ptr_huella = huella;						//puntero al array de huellas


//inicio_codec();

	ssi_init();




//acá arrancaría un for grande -loop-, de modo de poder interrumpir cada vez que llega una muestra,
//guardarla y si hay suficientes (2 para ZCR) hallar la huella

	//ver manera de interrumpir, fast_interrupt?, SSISR0.B.TFS para interrumpir...

//leer dato de entrada y guardar la muestra en el "buffer_in"

	//guardo en donde apunta el puntero lo q hay en la entrada de audio
	*ptr_buffer =  // ¿rxdata.d.i.audio_left o rxdata.d.i.audio_right? hay q ver por cual canal transmitimos
	
//calculo de ZCR y guardado del resultado en "huella"
	
	zcr(ptr_buffer, largo); //no sé bien cual es el largo... a priori se sabe pq se conocen las huellas

//llamar a funciones del codec


	//incremento el puntero para la siguiente pasada del for grande que terminaría con esto...
	*ptr_buffer++;

}	