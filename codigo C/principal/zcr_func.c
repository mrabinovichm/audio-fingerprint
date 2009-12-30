#include "zcr_func.h"
#include "math.h"


_fract *ptr_huella;
_fract *ptr_h_fin;
/* _fract correl[q-LHG+1];	*/													  /* vector de correlacion */

/* ******************************************************************************************************* */
/* **************** Funcion que halla el signo del valor que es pasado como parametro ******************** */
/* ******************************************************************************************************* */

int signo(_fract x)
{
	_fract cero = 0;

	if(x > cero)  {return 1;}
	if(x < cero)  {return -1;}
	if(x == cero) {return 0;}

	return 2; 													/*caso no valido, evita warning al compilar*/
}
/* ******************************************************************************************************* */


/* ******************************************************************************************************* */
/* ************ Funcion que halla los cruces por cero de una señal que es pasada como parametro ********** */
/* ******************************************************************************************************* */

int zcr(_fract *s, int largo)
{
	int i, sg, z;
	_fract p;

	z=0;
	
	for (i=1; i<largo; i++) 
	{
		p  = (*(s+i)) * (*(s+i-1));
		sg = signo(p);
		if ((sg == -1) || (*(s+i) == 0))
			z++;
	}
	return z;
}
/* ******************************************************************************************************* */


/* ******************************************************************************************************* */
/* ******************* Funcion que halla la frecuencia fundamental de un tramo de señal ****************** */
/* ******************************************************************************************************* */

short fundamentales(int *ceros)
{
	float zero;

	zero = ceros[0] + ceros[1] + ceros[2];							/* cruces por cero en un tramo de 30ms */
	*ptr_huella++ = (_fract)(zero/480);					/* normalizacion para no saturar por uso de _fract */
												  /* 480 = cruces por cero equiv a 8kHz(max f0 detectable) */

	if(ptr_huella < ptr_h_fin)
		return 0;
	return 1;															  /* la huella generada esta lista */
}
/* ******************************************************************************************************* */


/* ******************************************************************************************************* */
/* ************************************ Funcion que halla el promedio ************************************ */
/* ******************************************************************************************************* */

_fract promedio(_fract *p, int largo)
{
	int i;
	float suma;
	_fract prom;
		
	
	suma = 0;

	for (i=0;i<largo;i++) suma += (float) *(p+i)/largo;
	
	prom = (_fract)suma;	

	return prom;
}
/* ******************************************************************************************************* */


/* ******************************************************************************************************* */
/* ************************ Funcion que halla la correlacion entre dos señales *************************** */
/* ******************************************************************************************************* */

short correlacion(_fract *px, _Y _fract *py, _fract media)
{                                                                   
 	float r,suma,sigmax,sigmay,d;                                                       
 	int k,m,largo;                                                           
 	_Y _fract *py0;	
	double mult;

	                                                          
 	py0 = py;
 	   
 	sigmax = 0;
    for (k=0; k<LHG; k++) 
    	sigmax += (*(px+k)) * (*(px+k));  


	largo = q-LHG+1;
 	for (m=0; m<largo; m++)                                      
    {                                                              
		sigmay   = 0;                                               
     	suma    = 0;
		py0 = py+m;
     	for (k=0; k<LHG; k++)                                             
       	{   
			suma += (*(px+k)) * (*(py+k+m)-media);                   
       		/* ******************** */
       	   	sigmay += (*(py+k+m)-media) * (*(py+k+m)-media);                            
		}                                                      		    
                                                                  
		mult = (double)(sigmax*sigmay);
    	d = (float)sqrt(mult);
    	
    	r = suma/d;

		/* correl[m] = (_fract) r; */		 /* genera el vector de correlacion para ver su grafica en EVM */

	  	if (r>=UMBRAL) return 1;
	}
	
	return 0;
}
/* ******************************************************************************************************* */


/* ******************************************************************************************************* */
/* *************** Funcion que busca la huella pasada como parametro en la base de datos ***************** */
/* ******************************************************************************************************* */

short busqueda(_fract *h, _Y _fract **base_de_datos, short tam_bd)
{
	short i;
	_fract media;
	
	/* calcula la media de la señal */
   	media = promedio(h, LHG);

	/* calculo de señal sin valor medio */
 	for (i=0; i<LHG; i++)
	{
		*(h+i) -= media;
	}

	for (i=0; i<tam_bd; i++)
    {
        if (correlacion(h, base_de_datos[i], media) == 1)
        	return i; 										    /* índice donde está la huella coincidente */
    }
	
    return -1; 										                 		 /* si no la encontró va un -1 */
}
/* ******************************************************************************************************* */


