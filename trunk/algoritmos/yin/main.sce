//**********************************************************************************************************
//*************** Algoritmo para calcular la frecuencia fundamental de una señal de audio ******************
//******************************* Las señales de audio de prueba son: **************************************
//******************** "OnlyTime-Enya", "Headshrinker-Oasis" y  Eruption-Van Halen *************************
//**********************************************************************************************************

//**********************************************************************************************************
clear all;                  //limpia variables de memoria
clc;                        //limpia la pantalla
clf(0)                      //cierra las gráficas abiertas

//Obtiene las funciones definidas en el archivo de funciones .sci
getf ('E:\facultad\dsp\Proyecto\audio-fingerprint\algoritmos\yin\yin_func.sci')

//Oculta mensaje de funcion definida dos veces
funcprot(0);                          

//**********************************************************************************************************

//Cargamos el archivo wav con la señal de audio

  [archivo] = input('Nombre del archivo .wav (enya/oasis/van halen/seno): ', 'string');
  [x, t, fs] = wav(archivo);

//**********************************************************************************************************

//**********************************************************************************************************

//Definicion de parametros  

  L       = 3;                                 //3 segundos de señal para generar su huella
  ti5     = 15*10^(-3);                        //tramo de 5ms 
  ti15    = 45*10^(-3);                        //tramo de 15ms
  W       = floor(ti15 * fs);                  //cantidad de muestras de un tramo de 15ms
  S       = floor(ti5 * fs);                   //cantidad de muestras de un tramo de 5ms
  f0_min  = 1/ti15;                            //frecuencia fundamental min que puede detectarse en un tramo
  Tau_max = floor((1/f0_min)*fs);              //retardo max tau para aplicar a la señal 
  
//**********************************************************************************************************

//Nos quedamos con tres segundos de señal que corresponden con el estribillo 
  inicio = 518175;                             //muestra donde inicia el estribillo
  x = x(inicio : (inicio + L*fs));
  
  resto = length(x) - S*floor(length(x)/S);    //ultimas muestras de x que no alcanzaron para formar una trama 
  ceros = zeros(1, W + Tau_max - S - resto);   //ceros de relleno para poder retardar Tau a Xj
  x = [x, ceros];
  
//Cantidad de tramos de 15ms solapados, que es equivalente a la cantidad de muestras de f0
  q = floor((L - ti15)/ti5);

//Tomamos tramos de 15ms y en cada iteración nos desplazamos 5ms
//en cada iteracion se halla los cruces por cero y la frecuencia fundamental f0
//por cada periodo hay dos cruces por esto es que f0 = z/2
  
// Filtrado pasabanda entre 60 y 22000 Hz 
  finf = 60;
  fsup = 22000;
  hz = iir(4,'bp','butt',[finf fsup]/fs,[0 0]); 
  bp = syslin ('d', hz);                       //'d' indica el dominio discreto
  x = flts (x, bp);                            //la señal x es filtrada
  
  d_norm = [];
    
  for j = 1:q
    
      ini_tramo = (j-1)*S + 1;
      fin_tramo = ini_tramo + 2*W - 1;
      xt = x(ini_tramo : fin_tramo);
      
      d = dif_2(xt, W);
      
      d_norm = dif_norm(d);
      
      [f0(j),umbral(j)] = yin(d_norm, fs);  
      
  end

  figure(1);
  plot2d((1:length(d_norm)), d_norm)  

  figure(2);
  plot2d((1:length(f0)), f0)
  xtitle('Huella de la Señal de audio','muestras','Frecuencia fundamental (Hz)');
  
//figure(3);
//y = graf_fft(xt, fs);
u = umbral(q)
f = f0(q)
  
  
