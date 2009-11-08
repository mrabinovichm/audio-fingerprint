//**********************************************************************************************************
//**********************************************************************************************************
//****************** Funciones implementadas para el algoritmo de función diferencia YIN *******************
//**********************************************************************************************************
//**********************************************************************************************************


//**********************************************************************************************************
//********************* Obtención de la señal a partir de un archivo .WAV *************************
//**********************************************************************************************************

function[x, t, Fs] = wav(audio);
  
  stacksize('max');

  select audio,    
        case 'enya'      then [x,Fs]=wavread("E:\facultad\dsp\Proyecto\audio-fingerprint\audio\enya.wav"),
        case 'oasis'     then [x,Fs]=wavread("E:\facultad\dsp\Proyecto\audio-fingerprint\audio\oasis.wav"),
        case 'van halen' then [x,Fs]=wavread("E:\facultad\dsp\Proyecto\audio-fingerprint\audio\van halen.wav"),
        case 'seno'      then [x,Fs]=seno(1000,44100),
      else disp('No se ha encontrado el archivo de audio'),
  end 

  N=size(x,'*');           //cantidad de muestras
  t = (0:N-1)/Fs;          //vector tiempo asociado a cada muestra
 
endfunction 

//**********************************************************************************************************


//**********************************************************************************************************
//****** Funcion que halla la funcion diferencia de una señal que es pasada como parametro *****************
//**********************************************************************************************************

function[d] = dif_2(x, W);
   
   inicio = 1;
   final = W;
   
   d(1) = 0;
   for tau = 2:W
      d(tau) = abs(sum((x(inicio:final)-x(inicio+tau-1:final+tau-1))));
   end
      
endfunction  

//**********************************************************************************************************


//**********************************************************************************************************
//****** Funcion que halla la diferencia normalizada de la funcion diferencia ******************************
//**********************************************************************************************************

function [d_norm] = dif_norm(d);
  
  D = length(d);
  
//  d_norm(1) = 1;
//  for tau = 2:D
//      d_norm(tau) = d(tau)/(sum(d(2:tau))*(1/(tau-1)));
//  end

//Cálculo de la señal diferencia normalizada

  sumd = 0;
  d_norm(1) = 1;
  for i=2:D
    sumd=sumd+d(i);
    d_norm(i)=d(i)/((1/(i-1))*sumd);
  end
       
endfunction  

//**********************************************************************************************************

//**********************************************************************************************************
//**************** Funcion que halla la frecuencia fundamental f0 en un tramo de señal *********************
//**********************************************************************************************************

function[f0,umbral] = yin(d_n, fs);
    
   [min_a, ind] = min(d_n);
    
   umbral = min_a + 0.2;
    
   minimos = [];
   lugar = [];
   
   for i=2:length(d_n)-1
      if (umbral>d_n(i)) & (d_n(i-1)>d_n(i)) & (d_n(i+1)>d_n(i)) then
            minimos = [minimos d_n(i)];
            lugar   = [lugar i];        
      end
   end

   if length(lugar) == 0 then
      f0 = 0;
      return;
   end
      
   delta_l(1) = lugar(1);
   if length(lugar)>1 then
      for i = 2:length(lugar)
          delta_l(i) = lugar(i)-lugar(i-1);
      end
   end
   
   suma_delta = sum(delta_l(1:length(delta_l)));
   promedio_delta = suma_delta/length(delta_l);
   
   f0 = fs/promedio_delta;      //promedio de distancia entre minimos
   //f0 = fs/delta_l(1);        //solo considerando el primer minimo
    
endfunction  

//**********************************************************************************************************


//**********************************************************************************************************
//**************** Funcion que grafica una señal que es pasada como parámetro y su FFT**********************
//**********************************************************************************************************

function[y] = graf_fft(x, fs);

  N=size(x,'*');
  
//Calculo de la transformada rápida de Fourier FFT.
  y=fft(x);                
  //the fft response is symetric we retain only the first N/2 points
  f=fs*(0:(N/2))/N;        //associated frequency vector
  n=size(f,'*');
  
  t = (0:N-1)/fs;          //vector tiempo asociado a cada muestra
  
//Graficas de la señal normalizada vs tiempo y de la FFT

  subplot(2,2,1)
  plot2d(t,x(1,:))
  xtitle('Señal de audio','t(s)','amplitud');

  subplot(2,2,2)
  plot2d(f,abs(y(1:n)))
  xtitle('Transformada rápida de Fourier (FFT)','f(Hz)');

endfunction  

//**********************************************************************************************************

//**********************************************************************************************************
//**************** Funcion que hace un seno de frecuencia f de 3 segundos**********************
//**********************************************************************************************************

function[x,fs] = seno(f,fs);
  
  pi = %pi;
  
  inicio = 0;
  fin = 30;
  
  t = [inicio:1/fs:fin];
  
  x = sin(2*pi*f*t);

endfunction
