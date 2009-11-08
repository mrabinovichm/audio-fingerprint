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

//Cargamos el archivo wav con la señal de audio
  [archivo] = input('Nombre del archivo .wav (enya/oasis/van halen/seno/ruido): ', 'string');
  [x, t, fs] = wav(archivo);


//Definicion de parametros  

  tr_c    = 5*10^(-3);                        //intervalo de 5ms 
  tr_g    = 15*10^(-3);                       //intervalo de 15ms
  L       = 3;                                //3 segundos de señal para generar su huella
  W       = floor(tr_g * fs);                 //cantidad de muestras de un tramo de 15ms
  S       = floor(tr_c * fs);                 //cantidad de muestras de un tramo de 5ms
    
//**********************************************************************************************************


//Nos quedamos con tres segundos de señal que corresponden con el estribillo 
  
  inicio = 518175;                            //muestra donde inicia el estribillo
  x = x(inicio : inicio + L*fs);
  t = t(inicio : inicio + L*fs);
  

// Filtrado pasabanda entre 60 y 22000 Hz 
  finf = 60;
  fsup = 22000;
  hz = iir(4,'bp','butt',[finf fsup]/fs,[0 0]); 
  bp = syslin ('d', hz);                          //'d' indica el dominio discreto
  xf = flts (x, bp);                              //xf es la señal filtrada


//Cantidad de tramos de 15ms solapados, que es equivalente a la cantidad de muestras de f0
  q = floor((L - tr_g)/tr_c);


//Tomamos tramos de 15ms y en cada iteración nos desplazamos 5ms
//en cada iteracion se halla los cruces por cero y la frecuencia fundamental f0
//por cada periodo hay dos cruces por esto es que f0 = z/2
//La primera vez se calcula sobre los tr_g ms, luego se recuerdan los datos ya procesados 
  
  f_cero = [];
  
  for(i=1:3),
      ini_tramo = (i-1)*S + 1;
      fin_tramo = ini_tramo + S;
      xi = xf(ini_tramo : fin_tramo);         //muestras de la señal en un tramo de tr_c ms
      z(i) = zcr(xi);
      f_cero = [f_cero z(i)/2*(1/tr_c)];
  end

  f1 = f_cero(1);
  f2 = f_cero(2);
  f3 = f_cero(3);
  
  f0(1) = (f1+f2+f3)/3;
      
  for(j=2:q),
    
      f1 = f2;
      f2 = f3;
      
      ini_tramo = (j+1)*S;
      fin_tramo = ini_tramo + S;
      xi = xf(ini_tramo : fin_tramo);         //muestras de la señal en un tramo de 15ms
//    ti = t(ini_tramo : fin_tramo);
   
      z(j) = zcr(xi);                         //cruces por cero en un tramo de 15ms 
           
      f3 = z(j)/2 * (1/tr_c);              //frecuencia fundamental f0 para dicho tramo  
      
      f0(j) = (f1+f2+f3)/3;                                        //se multiplica por 1/ti15 para que f0 esté en Hz
  end

//  subplot(2,2,1)
//  plot2d(ti, xi(1,:))
//  xtitle('Señal de audio','t(s)','amplitud');
  
//  subplot(2,2,2)
  plot2d((1:length(f0)), f0, rect=[0,0,600,6000])
  xtitle('Huella de la Señal de audio','muestras','Frecuencia fundamental (Hz)');
  
  //disp(f0);
