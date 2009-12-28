//**********************************************************************************************************
//*************** Algoritmo para calcular la frecuencia fundamental de una señal de audio ******************
//**************************** se prueban la correlacion y demas funciones utiles **************************
//**********************************************************************************************************

//**********************************************************************************************************
clear all;                  //limpia variables de memoria
clc;                        //limpia la pantalla
clf(0)                      //cierra las gráficas abiertas

//Obtiene las funciones definidas en el archivo de funciones .sci (equivalente a un include de C)
getf ('zcr_func.sci')

//Oculta mensaje de funcion definida dos veces
funcprot(0);                          

//**********************************************************************************************************

//Cargamos el archivo wav con la señal de audio
  [archivo] = input('Nombre del archivo .wav (enya/oasis/van halen/olima/zitarrosa/curtidores/mozart/soda/seno): ', 'string');
  [x, t, fs] = wav(archivo);

  
//Definicion de parametros  

  tr_c    = 5*10^(-3);                        //intervalo de 5ms 
  tr_g    = 15*10^(-3);                       //intervalo de 15ms
  L       = 6;                                //6 segundos de señal para generar su huella
  W       = floor(tr_g * fs);                 //cantidad de muestras de un tramo de tr_g segundos
  S       = floor(tr_c * fs);                 //cantidad de muestras de un tramo de tr_c segundos
    
//**********************************************************************************************************

  
  inicio = 44100;  //muestra donde inicia el estribillo (las señales que construimos tienen 
                   //el estribillo mas o menos a partir del segundo)
  
  x = x(inicio : inicio + L*fs);
  t = t(inicio : inicio + L*fs);
  

// Filtrado pasabanda
  finf  = 60;
  fsup  = 22000;
  hz    = iir(4,'bp','butt',[finf fsup]/fs,[0 0]);   //filtro de orden 4 
  bp    = syslin ('d', hz);                          //'d' indica el dominio discreto
  xf    = flts (x, bp);                              //xf es la señal filtrada


//Cantidad de tramos de 15ms solapados, que es equivalente a la cantidad de muestras de f0
  q = floor((L - tr_g)/tr_c);


//Tomamos tramos de tr_g(15 ms) y en cada iteración nos desplazamos tr_c(5ms)
//En cada iteracion se hallan los cruces por cero y la frecuencia fundamental f0
//Por cada periodo hay dos cruces por cero
//La primera vez se calcula sobre los tr_g seg, luego se recuerdan los datos ya procesados
//por lo que basta con procesar tr_c seg cada vez
  
  f_cero = [];  //arreglo de ceros por tramo
  
  for(i=1:3),
      ini_tramo = (i-1)*S + 1;
      fin_tramo = ini_tramo + S;
      xi = xf(ini_tramo : fin_tramo);         //muestras de la señal en un tramo de tr_c s
      z(i) = zcr(xi);                         //cruces por cero en un tramo de tr_c s
      f_cero = [f_cero z(i)];
  end

  f1 = f_cero(1);
  f2 = f_cero(2);
  f3 = f_cero(3);
  
  f0(1) = (f1+f2+f3)/(2*tr_g);                //primer frecuencia fundamental calculada      
  
  for(j=2:q),
    
      //se recuerdan tramos anteriores
      f1 = f2;
      f2 = f3;
      
      ini_tramo = (j+1)*S;
      fin_tramo = ini_tramo + S;
      xi = xf(ini_tramo : fin_tramo);         //muestras de la señal en un tramo de tr_c s
   
      z(j) = zcr(xi);                         //cruces por cero en un tramo de tr_c s 
           
      f3 = z(j);                               
      
      f0(j) = (f1+f2+f3)/(2*tr_g);            //f0 calculada en tramo de tr_g s
  end

 
//se genera un archivo de texto (arreglo.txt) con los valoras de f0
  imp_array(f0);          //genera un array con los valores de f0 obtenidos
  //length(f0)            //muestra el largo del array generado
  
  
  
  //se imprime la huella generada
  figure;
  plot2d((1:length(f0)), f0, rect=[0,0,1200,6000])
  xtitle('Huella de la Señal de audio','muestras','Frecuencia fundamental (Hz)');
  
  //************************************************************************
  //simulacion!!!
  //************************************************************************
  //la huella hallada anteriormente es la que está en memoria 
  //"huella_calc" es la huella obtenida para comparar con la de la memoria 
  
  huella_calc = f0(150:350); //se toman 200 muestras (obtenido tras simular)
  
  
  //calculo de correlacion
  r = correlacion(huella_calc,f0);
  
  //se imprime la correlacion
  figure;
  plot2d(abs(r))
  xtitle('Correlacion entre señal entrada y guardada en memoria','muestras','correlacion normalizada');
