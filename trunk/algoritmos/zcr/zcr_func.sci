//**********************************************************************************************************
//**********************************************************************************************************
//********************* Funciones implementadas para el algoritmo de cruces por cero ZCR *******************
//**********************************************************************************************************
//**********************************************************************************************************


//**********************************************************************************************************
//********************* Obtención de la señal a partir de un archivo .WAV *************************
//**********************************************************************************************************

function[x, t, Fs] = wav(audio);
  
  stacksize('max');

  select audio,    
        case 'enya'  then [x,Fs]=wavread("E:\facultad\dsp\Proyecto\audio-fingerprint\audio\enya.wav"),
        case 'oasis' then [x,Fs]=wavread("E:\facultad\dsp\Proyecto\audio-fingerprint\audio\oasis.wav"),
      else disp('No se ha encontrado el archivo de audio'),
  end 

  N=size(x,'*');           //cantidad de muestras
  t = (0:N-1)/Fs;          //vector tiempo asociado a cada muestra

  //Calculo de la transformada rápida de Fourier FFT.
  y=fft(x);                
  //the fft response is symetric we retain only the first N/2 points
  f=Fs*(0:(N/2))/N;        //associated frequency vector
  n=size(f,'*');

  //Graficas de la señal normalizada vs tiempo y de la FFT

//  subplot(2,2,1)
//  plot2d(t,x(1,:))
//  xtitle('Señal de audio','t(s)','amplitud');

//  subplot(2,2,2)
//  plot2d(f,abs(y(1:n)))
//  xtitle('Transformada rápida de Fourier (FFT)','f(Hz)');
  
endfunction 

//**********************************************************************************************************


//**********************************************************************************************************
//********** Funcion que haya los cruces por cero de una señal que es pasada como parametro ****************
//**********************************************************************************************************

function[z] = zcr(s);
    
    z=0;
    for(i=2:length(s)),
        
        if(sign(s(i) * s(i-1)) == -1)
            z = z + 1;
        end
    end 
endfunction  

//**********************************************************************************************************
