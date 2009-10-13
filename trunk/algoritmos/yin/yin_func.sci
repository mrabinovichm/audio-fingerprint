//**********************************************************************************************************
//**********************************************************************************************************
//****************** Funciones implementadas para el algoritmo de funci�n diferencia YIN *******************
//**********************************************************************************************************
//**********************************************************************************************************


//**********************************************************************************************************
//********************* Obtenci�n de la se�al a partir de un archivo .WAV *************************
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
//****** Funcion que haya la funcion diferencia normalizada de una se�al que es pasada como parametro ******
//**********************************************************************************************************

function[d_norm] = dif_norm(xi, W, Tau_max);
   
   d_norm(1) = 1;                                      //1er elemento vale 1, cuando Tau = 0, por definici�n
   suma = 0;
    
   for tau=2:Tau_max                                           //    W
      d(tau) = sum( (xi(1 : W) - xi(tau : W + tau - 1)).^2 );  // sumatoria (Xj - Xj+tau)^2  
      suma = suma + d(tau);                                    //  j = 1
      d_norm(tau) = d(tau)/(suma/(tau-1));
   end
   
endfunction  

//**********************************************************************************************************


//**********************************************************************************************************
//********** Funcion que haya la **************
//**********************************************************************************************************

function[y] = yin(s);
    
   
endfunction  

//**********************************************************************************************************


//**********************************************************************************************************
//**************** Funcion que grafica una se�al que es pasada como par�metro y su FFT**********************
//**********************************************************************************************************

function[y] = graf_fft(x, fs);

  N=size(x,'*');
  
//Calculo de la transformada r�pida de Fourier FFT.
  y=fft(x);                
  //the fft response is symetric we retain only the first N/2 points
  f=fs*(0:(N/2))/N;        //associated frequency vector
  n=size(f,'*');

//Graficas de la se�al normalizada vs tiempo y de la FFT

  subplot(2,2,1)
  plot2d(t,x(1,:))
  xtitle('Se�al de audio','t(s)','amplitud');

  subplot(2,2,2)
  plot2d(f,abs(y(1:n)))
  xtitle('Transformada r�pida de Fourier (FFT)','f(Hz)');

endfunction  

//**********************************************************************************************************
