#ifndef ZCR_FUNC_H
#define ZCR_FUNC_H

#define 	tr_g 	0.015                   	/*intervalo de ventana de calculo*/
#define 	tr_c 	0.005                    	/*intervalo de desplazamiento de la ventana*/
#define 	L 		3                         	/*3 segundos de señal para generar su huella*/
#define 	UMBRAL	0.75				   		/*umbral de decision al comparar huellas*/
#define 	W		720							/*cantidad de muestras equivalentes a tr_g segundos*/
#define 	S		240							/*cantidad de muestras equivalentes a tr_c segundos*/
#define  	q		597
#define 	T 		3							/*cantidad de tramos de 5ms*/


int signo(_fract x);
int zcr(_fract *s, int largo);
short fundamentales(int *ceros);
short busqueda(float *h, float **base_de_datos, short tam_bd);

#endif 