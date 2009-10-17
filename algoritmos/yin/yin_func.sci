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
      else disp('No se ha encontrado el archivo de audio'),
  end 

  N=size(x,'*');           //cantidad de muestras
  t = (0:N-1)/Fs;          //vector tiempo asociado a cada muestra
 
endfunction 

//**********************************************************************************************************


//**********************************************************************************************************
//****** Funcion que halla la funcion diferencia de una señal que es pasada como parametro *****************
//**********************************************************************************************************

function[d] = dif_2(xi5, S);
   
   inicio = 1;
   final = S;
   
   //d(1) = 0;
   
   for tau = 1:S
      d(tau) = sum((xi5(inicio:final)-xi5(inicio+tau:final+tau)).^2);
   end
      
endfunction  

//**********************************************************************************************************


//**********************************************************************************************************
//****** Funcion que halla la diferencia normalizada de la funcion diferencia ******************************
//**********************************************************************************************************

function [d_norm] = dif_norm(d,d_viejo,d_masviejo)
  
  d = [d_masviejo d_viejo d];
  d_norm(1) = 1;
  for tau = 2:length(d)
      d_norm(tau) = d(tau)/(sum(d(2:tau))*(1/(tau-1)));
  end
      
endfunction  

//**********************************************************************************************************

//**********************************************************************************************************
//**************** Funcion que halla la frecuencia fundamental f0 en un tramo de señal *********************
//**********************************************************************************************************

function[f0] = yin(d_n, fs);
    
   [min_a, ind] = min(d_n);
    
   umbral = min_a +0.4;       
 
   minimos = [];
   lugar = [];
   for i=2:length(d_n)-1
      if(d_n(i-1)>d_n(i)) & (d_n(i+1)>d_n(i)) & (umbral>d_n(i)) then
            minimos = [minimos d_n(i)];
            lugar   = [lugar i];        
      end
   end

   delta_l(1) = lugar(1);
   
   if length(lugar)>1 then
      for i = 2:length(lugar)
          delta_l(i) = lugar(i)-lugar(i-1);
      end
   end
   
   suma_delta = sum(delta_l(1:length(delta_l)));
   promedio_delta = suma_delta/length(delta_l);
   
   //f0 = fs/promedio_delta;
  
  f0 = fs/delta_l(1);
   //disp('f0',f0);
   //disp('f01',f01);   
 
endfunction  

//**********************************************************************************************************


//**********************************************************************************************************
//**************** Funcion que grafica una señal que es pasada como parámetro y su FFT**********************
//**********************************************************************************************************

function[y] = graf_fft(x, fs)

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
