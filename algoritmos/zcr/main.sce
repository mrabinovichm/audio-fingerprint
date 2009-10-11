//**********************************************************************************************************
//***************** Algoritmo para calcular los cruces por cero de una señal de audio **********************
//************* Las señales de audio de prueba son "OnlyTime-Enya" y "Headshrinker-Oasis" ******************
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
  q = 600;                                    //cantidad de muestras de f0
  
//**********************************************************************************************************

//Cargamos el archivo wav con la señal de audio
  archivo = 'enya';
  [x, t, fs] = wav(archivo);

//Nos quedamos con tres segundos de señal que corresponden con el estribillo 
  INI_enya = 518175;                          //muestra donde inicia el estribillo
  x = x(INI_enya : INI_enya + 3*fs);
  t = t(INI_enya : INI_enya + 3*fs);

//Tomamos intervalos de 15ms y en cada iteración nos desplazamos 5ms
//en cada iteracion se halla los cruces por cero y la frecuencia fundamental f0
//por cada periodo hay dos cruces por esto es que f0 = z/2
  for(j=1:q-3),
    
      xi = x((j*ti5)*fs : (j*ti5+ti15)*fs);   //muestras de la señal en un intervalo de 15ms
//    ti = t((j*ti5)*fs : (j*ti5+ti15)*fs);
   
      z(j) = zcr(xi);                         //cruces por cero en un intervalo de 15ms 
      f0(j) = z(j)/2 * (1/ti15);              //frecuencia fundamental f0 para dicho intervalo  
                                              //se multiplica por 1/ti15 para que f0 esté en Hz
  end

//  subplot(2,2,1)
//  plot2d(ti, xi(1,:))
//  xtitle('Señal de audio','t(s)','amplitud');
  
//  subplot(2,2,2)
  plot2d((1:q), f0)
  xtitle('Huella de la Señal de audio','muestras','Frecuencia fundamental (Hz)');
  
  
