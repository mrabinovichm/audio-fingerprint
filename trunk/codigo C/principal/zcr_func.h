#ifndef ZCR_FUNC_H
#define ZCR_FUNC_H

/* ******************************************************************************************************* */
/* *********************** Parametros para la generacion y busqueda de huellas *************************** */
/* ******************************************************************************************************* */
 
#define 	UMBRAL	0.70			   							   /*umbral de decision al comparar huellas*/
#define 	S		160						   /* a fs=16Khz, un intervalo de 10ms, equivale a 160 muestras*/
#define  	q		597										   /* largo de las huellas de la base de datos */
#define  	LHG		199								 /* Largo de la Huella Generada de la señal de entrada */
#define 	T 		3														   /*cantidad de tramos de 10ms*/

/* ******************************************************************************************************* */


/* ******************************************************************************************************* */
/* **************** Funciones usadas en el algoritmo ZCR y en la busqueda de huellas ********************* */
/* ******************************************************************************************************* */

int zcr(_fract *s, int largo);
short fundamentales(int *ceros);
short busqueda(_fract *h, _Y _fract **base_de_datos, short tam_bd);

/* ******************************************************************************************************* */

#endif 