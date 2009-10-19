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
getf ('E:\facultad\dsp\Proyecto\audio-fingerprint\algoritmos\zcr\zcr_func.sci')

//Oculta mensaje de funcion definida dos veces
funcprot(0);                          

//**********************************************************************************************************

//Definicion de parametros  

  ti5  =  5*10^(-3);                          //intervalo de 5ms 
  ti15 = 15*10^(-3);                          //intervalo de 15ms
  L = 3;                                      //3 segundos de señal para generar su huella
  
//**********************************************************************************************************

//Cargamos el archivo wav con la señal de audio
  [archivo] = input('Nombre del archivo .wav (enya/oasis/van halen): ', 'string');
  [x, t, fs] = wav(archivo);

//Nos quedamos con tres segundos de señal que corresponden con el estribillo 
  inicio = 518175;                               //muestra donde inicia el estribillo
  x = x(inicio : inicio + L*fs);
  t = t(inicio : inicio + L*fs);
  
// Filtrado pasabanda entre 60 y 22000 Hz 
  finf = 60;
  fsup = 22000;
  hz = iir(4,'bp','butt',[finf fsup]/fs,[0 0]); 
  bp = syslin ('d', hz);                         //'d' indica el dominio discreto
  xf = flts (x, bp);                             //xf es la señal filtrada

//Cantidad de tramos de 15ms solapados, que es equivalente a la cantidad de muestras de f0
  long = length(xf);
  q = floor(long/(ti5 * fs));

//Tomamos tramos de 15ms y en cada iteración nos desplazamos 5ms
//en cada iteracion se halla los cruces por cero y la frecuencia fundamental f0
//por cada periodo hay dos cruces por esto es que f0 = z/2
  for(j=1:q-3),
    
      ini_tramo = (j*ti5)*fs;
      fin_tramo = (j*ti5+ti15)*fs;
      xi = xf(ini_tramo : fin_tramo);         //muestras de la señal en un tramo de 15ms
//    ti = t(ini_tramo : fin_tramo);
   
      z(j) = zcr(xi);                         //cruces por cero en un tramo de 15ms 
      f0(j) = z(j)/2 * (1/ti15);              //frecuencia fundamental f0 para dicho tramo  
                                              //se multiplica por 1/ti15 para que f0 esté en Hz
  end

//  subplot(2,2,1)
//  plot2d(ti, xi(1,:))
//  xtitle('Señal de audio','t(s)','amplitud');
  
//  subplot(2,2,2)
  plot2d((1:length(f0)), f0, rect=[0,0,600,6000])
  xtitle('Huella de la Señal de audio','muestras','Frecuencia fundamental (Hz)');
  
  
