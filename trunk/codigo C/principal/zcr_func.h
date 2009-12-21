#ifndef ZCR_FUNC_H
#define ZCR_FUNC_H

#define 	tr_g 	0.015                   	/*intervalo de ventana de calculo*/
#define 	tr_c 	0.005                    	/*intervalo de desplazamiento de la ventana*/
#define 	L 		3                         	/*3 segundos de señal para generar su huella*/
#define 	UMBRAL	0.70			   			/*umbral de decision al comparar huellas*/
#define 	UMB	    0.25
#define 	W		720							/*cantidad de muestras equivalentes a tr_g segundos*/
#define 	S		160							/*a frecuencia fs=48Khz, intervalo de 5ms, son 240 muestras*/
#define  	q		597
#define  	LHG		199
#define 	T 		3							/*cantidad de tramos de 5ms*/


int zcr(_fract *s, int largo);
short fundamentales(int *ceros);
short busqueda(_fract *h, _Y _fract **base_de_datos, short tam_bd);


#endif 