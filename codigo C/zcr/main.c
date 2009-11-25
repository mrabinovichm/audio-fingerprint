//**********************************************************************************************************
//*************** Algoritmo para calcular la frecuencia fundamental de una se�al de audio ******************
//****************************************por medio de ZCR**************************************************

#include <reg56303.h>
#include "cs4215.h"
#include "zcr_func.h"

//**********************************************************************************************************
	
//definicion de parametros  

#define		fs 		48000						//frecuencia de muestreo del codec	
#define 	tr_g 	0.015                   	//intervalo de ventana de calculo
#define 	tr_c 	0.005                    	//intervalo de desplazamiento de la ventana 
#define 	L 		3                         	//3 segundos de se�al para generar su huella
#define 	umbral	0.2					   		//umbral de decision al comparar huellas
#define 	W		720							//cantidad de muestras equivalentes a tr_g segundos
#define 	S		240							//cantidad de muestras equivalentes a tr_c segundos
#define  	q		597							//cantidad de muestras de fo = (L-tr_g)/tr_c

//buffers y punteros

_fract 	buffer_in[721] = {0.000000,0.081460,0.162379,0.242218,0.320448,0.396547,0.470011,0.540350,0.607098,0.669811,0.728072,0.781493,0.829720,0.872432,0.909345,0.940214,0.964833,0.983040,0.994712,0.999772,0.998188,0.989968,0.975169,0.953887,0.926266,0.892487,0.852777,0.807398,0.756653,0.700878,0.640445,0.575755,0.507238,0.435349,0.360567,0.283388,0.204325,0.123905,0.042660,-0.038867,-0.120137,-0.200608,-0.279745,-0.357023,-0.431928,-0.503962,-0.572647,-0.637525,-0.698165,-0.754165,-0.805153,-0.850788,-0.890769,-0.924828,-0.952741,-0.974321,-0.989425,-0.997952,-0.999846,-0.995094,-0.983729,-0.965824,-0.941500,-0.910918,-0.874281,-0.831833,-0.783856,-0.730669,-0.672625,-0.610111,-0.543541,-0.473358,-0.400029,-0.324041,-0.245900,-0.166123,-0.085243,-0.003796,0.077676,0.158632,0.238533,0.316849,0.393059,0.466657,0.537152,0.604078,0.666988,0.725464,0.779119,0.827595,0.870570,0.907759,0.938914,0.963828,0.982336,0.994315,0.999684,0.998409,0.990497,0.976002,0.955020,0.927690,0.894193,0.854753,0.809632,0.759129,0.703581,0.643356,0.578854,0.510505,0.438763,0.364105,0.287026,0.208040,0.127670,0.046453,-0.035074,-0.116367,-0.196887,-0.276099,-0.353475,-0.428502,-0.500680,-0.569531,-0.634596,-0.695443,-0.751667,-0.802896,-0.848787,-0.889037,-0.923378,-0.951581,-0.973459,-0.988867,-0.997702,-0.999906,-0.995463,-0.984404,-0.966801,-0.942773,-0.912477,-0.876117,-0.833934,-0.786208,-0.733255,-0.675429,-0.613114,-0.546723,-0.476699,-0.403505,-0.327630,-0.249577,-0.169866,-0.089025,-0.007592,0.073891,0.154883,0.234845,0.313247,0.389566,0.463296,0.533947,0.601048,0.664155,0.722847,0.776734,0.825458,0.868696,0.906160,0.937601,0.962810,0.981619,0.993903,0.999582,0.998616,0.991012,0.976822,0.956139,0.929100,0.895886,0.856718,0.811854,0.761595,0.706273,0.646257,0.581946,0.513766,0.442171,0.367638,0.290660,0.211751,0.131435,0.050244,-0.031280,-0.112596,-0.193164,-0.272448,-0.349921,-0.425069,-0.497390,-0.566406,-0.631657,-0.692710,-0.749158,-0.800627,-0.846774,-0.887293,-0.921914,-0.950407,-0.972583,-0.988295,-0.997438,-0.999951,-0.995817,-0.985064,-0.967764,-0.944031,-0.914024,-0.877941,-0.836023,-0.788548,-0.735831,-0.678224,-0.616108,-0.549898,-0.480032,-0.406976,-0.331214,-0.253251,-0.173605,-0.092805,-0.011388,0.070105,0.151131,0.231154,0.309639,0.386067,0.459929,0.530733,0.598010,0.661312,0.720218,0.774337,0.823310,0.866810,0.904548,0.936274,0.961777,0.980887,0.993478,0.999465,0.998808,0.991513,0.977627,0.957244,0.930498,0.897566,0.858669,0.814065,0.764049,0.708956,0.649149,0.585028,0.517019,0.445573,0.371165,0.294291,0.215460,0.135197,0.054035,-0.027485,-0.108824,-0.189438,-0.268794,-0.346363,-0.421629,-0.494094,-0.563274,-0.628710,-0.689967,-0.746638,-0.798347,-0.844749,-0.885536,-0.920437,-0.949220,-0.971694,-0.987709,-0.997159,-0.999981,-0.996157,-0.985711,-0.968713,-0.945277,-0.915557,-0.879752,-0.838100,-0.790877,-0.738396,-0.681008,-0.619094,-0.553064,-0.483359,-0.410440,-0.334794,-0.256922,-0.177342,-0.096584,-0.015184,0.066317,0.147378,0.227459,0.306028,0.382562,0.456555,0.527512,0.594963,0.658460,0.717580,0.771930,0.821149,0.864911,0.902923,0.934934,0.960731,0.980142,0.993038,0.999333,0.998986,0.991999,0.978419,0.958335,0.931881,0.899234,0.860609,0.816264,0.766493,0.711628,0.652032,0.588103,0.520265,0.448968,0.374688,0.297916,0.219165,0.138957,0.057825,-0.023691,-0.105049,-0.185709,-0.265135,-0.342799,-0.418184,-0.490790,-0.560133,-0.625753,-0.687214,-0.744108,-0.796055,-0.842711,-0.883766,-0.918946,-0.948019,-0.970790,-0.987108,-0.996866,-0.999997,-0.996482,-0.986343,-0.969648,-0.946509,-0.917077,-0.881551,-0.840165,-0.793194,-0.740951,-0.683783,-0.622071,-0.556223,-0.486678,-0.413899,-0.338368,-0.260589,-0.181077,-0.100362,-0.018979,0.062529,0.143622,0.223760,0.302411,0.379052,0.453174,0.524283,0.591908,0.655598,0.714930,0.769511,0.818977,0.862999,0.901285,0.933580,0.959670,0.979382,0.992583,0.999187,0.999150,0.992472,0.979196,0.959412,0.933252,0.900888,0.862536,0.818451,0.768926,0.714289,0.654906,0.591169,0.523503,0.452357,0.378204,0.301538,0.222867,0.142715,0.061615,-0.019895,-0.101273,-0.181978,-0.261473,-0.339231,-0.414733,-0.487479,-0.556984,-0.622788,-0.684452,-0.741566,-0.793752,-0.840661,-0.881983,-0.917442,-0.946804,-0.969872,-0.986494,-0.996558,-0.999999,-0.996793,-0.986961,-0.970570,-0.947727,-0.918584,-0.883336,-0.842217,-0.795500,-0.743495,-0.686548,-0.625038,-0.559374,-0.489991,-0.417352,-0.341938,-0.264252,-0.184809,-0.104138,-0.022775,0.058740,0.139864,0.220059,0.298791,0.375537,0.449787,0.521047,0.588844,0.652727,0.712271,0.767081,0.816793,0.861075,0.899634,0.932213,0.958596,0.978608,0.992115,0.999027,0.999299,0.992929,0.979959,0.960476,0.934609,0.902529,0.864450,0.820626,0.771347,0.716941,0.657770,0.594226,0.526733,0.455739,0.381716,0.305155,0.226566,0.146472,0.065403,-0.016100,-0.097496,-0.178244,-0.257807,-0.335657,-0.411276,-0.484161,-0.553828,-0.619813,-0.681679,-0.739014,-0.791437,-0.838599,-0.880188,-0.915925,-0.945575,-0.968940,-0.985865,-0.996236,-0.999986,-0.997089,-0.987565,-0.971477,-0.948931,-0.920078,-0.885110,-0.844258,-0.797794,-0.746028,-0.689303,-0.627997,-0.562516,-0.493297,-0.420798,-0.345503,-0.267911,-0.188538,-0.107913,-0.026570,0.054950,0.136105,0.216354,0.295166,0.372016,0.446393,0.517803,0.585771,0.649846,0.709601,0.764640,0.814597,0.859139,0.897970,0.930833,0.957508,0.977820,0.991632,0.998853,0.999434,0.993373,0.980709,0.961526,0.935952,0.904157,0.866352,0.822789,0.773757,0.719582,0.660624,0.597275,0.529956,0.459115,0.385222,0.308768,0.230262,0.150226,0.069191,-0.012304,-0.093717,-0.174508,-0.254138,-0.332079,-0.407813,-0.480836,-0.550663,-0.616830,-0.678897,-0.736451,-0.789111,-0.836525,-0.878380,-0.914395,-0.944333,-0.967995,-0.985222,-0.995900,-0.999959,-0.997372,-0.988155,-0.972370,-0.950122,-0.921559,-0.886870,-0.846286,-0.800077,-0.748551,-0.692049,-0.630947,-0.565651,-0.496595,-0.424239,-0.349063,-0.271566,-0.192265,-0.111686,-0.030364,0.051159,0.132343,0.212647,0.291537,0.368490,0.442993,0.514552,0.582690,0.646956,0.706922,0.762188,0.812389,0.857190,0.896293,0.929439,0.956407,0.977018,0.991135,0.998664,0.999555,0.993802,0.981444,0.962562,0.937282,0.905772,0.868242,0.824941,0.776156,0.722213,0.663469,0.600316,0.533172,0.462484,0.388722,0.312376,0.233954,0.153978,0.072977,-0.008508,-0.089937,-0.170768,-0.250464,-0.328496,-0.404344,-0.477504,-0.547490,-0.613838,-0.676105,-0.733878,-0.786773,-0.834439,-0.876559,-0.912852,-0.943078,-0.967035,-0.984564,-0.995550,-0.999918,-0.997640,-0.988730,-0.973249,-0.951299,-0.923026,-0.888617,-0.848302,-0.802349,-0.751063,-0.694784,-0.633887,-0.568777,-0.499887,-0.427673,-0.352618,-0.275218,-0.195989,-0.115457,-0.034158,0.047368,0.128579,0.208936,0.287904,0.364958,0.439586,0.511293,0.579601,0.644057,0.704232,0.759725,0.810170,0.855229,0.894603,0.928031,0.955291,0.976201,0.990623,0.998460,0.999661,0.994217,0.982164,0.963584,0.938598,0.907374,0.870119,0.827081};				   	//buffer de entrada de la se�al
float 	huella[597];					  			//arreglo de frecuencias fundamentales
float   huellita[3];							//arreglo de frecuencias parciales calculadas cada tr_c ms
											    
int ceros;
//**********************************************************************************************************


int main (void)
{
	//int ceros;
	int tramo_listo;
	int i,j;

//huellas guardadas calculadas con la herramienta SCILAB

  /*float enya[q]		= {};
	float oasis[q]		= {};
	float vanHalen[q]	= {};*/


//buffers y punteros

	_fract 	*ptr_buffer = buffer_in;			//puntero al buffer de entrada circular
	float 	*ptr_huella = huella;				//puntero al array de huellas
	//float   *ptr_huellita = huellita;			//puntero a huellita


//inicializacion

	//codec
	/*inicio_codec();
	ssi_init();*/



	tramo_listo = 1;

//procesamiento de a tramos de S muestras equivalentes a tr_c ms 
	while(tramo_listo==0);

	for(j=0;j<=2;j++)
	{
		//calculo de ZCR y guardado del resultado en "huellita"
		ceros = zcr(ptr_buffer, S);
		huellita[j] = ceros*100;//(2*tr_c);
		ptr_buffer += S; //me corro tr_c ms donde se encuentra el nuevo intervalito
	}

	*ptr_huella = (huellita[0]+huellita[1]+huellita[2])/3; //muestra de huella guardada
		
	//intercambio huellitas para recordar lo ya calculado
	huellita[0] = huellita[1];
	huellita[1] = huellita[2];

	ptr_huella += 1; //me preparo para calcular la nueva muestra de huella

	for(i=2;i<=q;i++)
	{
		//calculo de ZCR y guardado del resultado en "huellita"
		ceros = zcr(ptr_buffer, S);
		huellita[2] = ceros*100;//(2*tr_c);	
			
		ptr_buffer += S; //me corro tr_c ms donde se encuentra el nuevo intervalito
			
		*ptr_huella = (huellita[0]+huellita[1]+huellita[2])/3; //muestra de huella guardada
			
		//intercambio huellitas para recordar lo ya calculado
		huellita[0] = huellita[1];
		huellita[1] = huellita[2];

		ptr_huella += 1; //me preparo para calcular la nueva muestra de huella
	}
}	