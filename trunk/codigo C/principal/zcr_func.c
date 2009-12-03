#include "zcr_func.h"
#include "math.h"

float *ptr_huella;
float *ptr_h_fin;

//**********************************************************************************************************
//***************** Funcion que halla el signo del valor que es pasado como parametro **********************
//**********************************************************************************************************

int signo(_fract x)
{
	_fract cero = 0;

	if(x > cero)  {return 1;}
	if(x < cero)  {return -1;}
	if(x == cero) {return 0;}
}
//**********************************************************************************************************


//**********************************************************************************************************
//********** Funcion que halla los cruces por cero de una señal que es pasada como parametro ***************
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


/* ******************************************************************************************************** */
/* ********* Funcion que halla el promedio ******************************************** */
/* ******************************************************************************************************** */

float promedio(float *p, int largo)
{
	int i;
	float suma, prom;
	
	suma = 0;

	for (i=0;i<largo;i++) suma += *(p+i);
	
	prom = (float)(suma/largo);

	return prom;
}

/* ******************************************************************************************************** */
/* ********* Funcion que halla la correlacion entre dos señales******************************************** */
/* ******************************************************************************************************** */

short correlacion(float *px,float *py)
{                                                                   
 	_fract r;                                                           	
	float mx,my,suma,sumax,sumay,sigmax,sigmay,div;                                                       
 	int k,m;                                                           
 	float *px0,*py0,*finx,*finy;
	
	int largox = q;
	int largoy = 2*q;
  
 	finx = px + largox;                                            
 	finy = py + largoy;                                                
    
 	px0 = px;                                                          
 	py0 = py;                                                          
   
 	/* calculo de la media de las señales */
 	mx = promedio(px0, largox); 	   
 	my = promedio(py0, largoy);                                           
  
 	/* calculo de señales sin valor medio */
 	while(px0 != finx)                                                 
 	{                                                                  
 		*px0 -= mx;                                                    
 		px0++;                                                         
 	}                                                                  
   
 	while(py0 != finy)                                                 
 	{                                                                  
 		*py0 -= my;                                                    
 		py0++;                                                         
 	}                                                                  
    
     for (k=0; k<largox; k++) 
     	sumax += (*(px+k)) * (*(px+k));                                                                    

 	/* cuentas */
 	for (m=0; m<largoy-largox; m++)                                      
    {                                                              
		sumax   = 0;                                               
     	sumay   = 0;                                               
     	sigmax  = 0;                                               
     	sigmay  = 0;                                               
     	suma    = 0;                                               
     	for (k=0; k<largox; k++)                                             
       	{                                                      
       		suma += (*(px+k)) * (*(py+k+m));                   
       		/* ******************** */
       	   	sumay += (*(py+k+m)) * (*(py+k+m));                            
		}                                                          
    }                                                              
	/* ******************** */
    sigmax = sqrt(sumax/largox);                                   
    sigmay = sqrt(sumay/largox);                                   
    /* ******************** */                                     
    div = sigmax*sigmay*largox;                                        
    r = (_fract)(suma/div);
	
	if (fabs(r)>=0.9) return 1;
	
	return 0;
}
/* ******************************************************************************************************** */


//**********************************************************************************************************
//**************** Funcion que busca la huella pasada como parametro en la base de datos *******************
//**********************************************************************************************************

short busqueda(float *h, float **base_de_datos, short tam_bd)
{
	short i;
    for (i=0; i<tam_bd; i++)
    {
        if (correlacion(h, base_de_datos[i]) == 1)
        	return i; 								/* índice en donde está el mensaje para el lcd */
    }
    return -1; 										                 /* si no la encontró va un -1 */
}
/* ******************************************************************************************************* */