#include "zcr_func.h"
#include "math.h"


//**********************************************************************************************************
//***************** Funcion que halla el signo del valor que es pasado como parametro **********************
//**********************************************************************************************************

int signo(_fract x)
{
	if (x == 0)
		return 0;

	return (x/fabs(x));
}
//**********************************************************************************************************


//**********************************************************************************************************
//********** Funcion que halla los cruces por cero de una se�al que es pasada como parametro ***************
//**********************************************************************************************************

int zcr(_fract *s, int largo)
{
	int i, sg, z;
	_fract p;

	z=0;
	
	for (i=1; i<largo; i++) 
	{
		p  = *(s+i) * (*(s+i-1));
		sg = signo(p);
		if (sg == -1 | *(s+i) == 0)
			z++;
	}
	return z;
}
//**********************************************************************************************************


//**********************************************************************************************************
//********************** Funcion que halla la frec fundamental de un tramo de 15ms *************************
//**********************************************************************************************************

short fundamentales(int *ceros)
{
	*ptr_huella++ = (float)(ceros[0] + ceros[1] + ceros[2])/(2*tr_g) ;
	if(ptr_huella < ptr_h_fin)
		return 0;
	return 1;
}
//**********************************************************************************************************


//**********************************************************************************************************
//**************** Funcion que busca la huella pasada como parametro en la base de datos *******************
//**********************************************************************************************************

short busqueda(float *h)
{
	return 0;
}
//**********************************************************************************************************