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

  [archivo] = input('Nombre del archivo .wav (enya/oasis/van halen): ', 'string');
  [x, t, fs] = wav(archivo);

//**********************************************************************************************************

//**********************************************************************************************************

//Definicion de parametros  

  L       = 3;                                 //3 segundos de señal para generar su huella
  ti5     = 5*10^(-3);                         //tramo de 5ms 
  ti15    = 15*10^(-3);                        //tramo de 15ms
  W       = floor(ti15 * fs);                  //cantidad de muestras de un tramo de 15ms
  S       = floor(ti5 * fs);                   //cantidad de muestras de un tramo de 5ms
  f0_min  = 1/ti15;                            //frecuencia fundamental min que puede detectarse en un tramo
  Tau_max = floor((1/f0_min)*fs);              //retardo max tau para aplicar a la señal 
  
//**********************************************************************************************************

//Nos quedamos con tres segundos de señal que corresponden con el estribillo 
  inicio = 518175;                             //muestra donde inicia el estribillo
  x = x(inicio : inicio + L*fs);
  
  resto = length(x) - S*floor(length(x)/S);    //ultimas muestras de x que no alcanzaron para formar una trama 
  ceros = zeros(1, W + Tau_max - S - resto);   //ceros de relleno para poder retardar Tau a Xj
  x = [x, ceros];
  
//Cantidad de tramos de 15ms solapados, que es equivalente a la cantidad de muestras de f0
  long = length(x);
  q = floor(long/(ti5 * fs));

//Tomamos tramos de 15ms y en cada iteración nos desplazamos 5ms
//en cada iteracion se halla los cruces por cero y la frecuencia fundamental f0
//por cada periodo hay dos cruces por esto es que f0 = z/2
  d_norm = [];
  d_viejo = [];
  
  for j = 1:2
    
      ini_tramo = (j-1)*S + 1;
      fin_tramo = ini_tramo + 2*S - 1;
      xt = x(ini_tramo : fin_tramo);
      
      d = dif_2(xt, S);
      
      d_masviejo = d_viejo;
      d_viejo = d;
  end
  
  for j = 3:q-3
    
      ini_tramo = (j-1)*S + 1;
      fin_tramo = ini_tramo + 2*S - 1;
      xt = x(ini_tramo : fin_tramo);
      
      d = dif_2(xt, S);
      d_norm = dif_norm(d,d_viejo,d_masviejo);
      
      f0(j) = yin(d_norm, fs);
      
      d_masviejo = d_viejo;
      d_viejo = d;
  end


//length(d_norm(1,:))
plot2d((1:length(d_norm)), d_norm)  
figure;

//  subplot(2,2,2)
  plot2d((1:length(f0)), f0)
  xtitle('Huella de la Señal de audio','muestras','Frecuencia fundamental (Hz)');
  
  //figure;
  //y = graf_fft(x, fs);
  
  
