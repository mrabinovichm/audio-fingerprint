//**********************************************************************************************************
//**********************************************************************************************************
//********************* Funciones implementadas para el algoritmo de cruces por cero ZCR *******************
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
        case 'seno'      then [x,Fs]=seno(1000,44100),
      else disp('No se ha encontrado el archivo de audio'),
  end 

  N=size(x,'*');           //cantidad de muestras
  t = (0:N-1)/Fs;          //vector tiempo asociado a cada muestra
  
endfunction 

//**********************************************************************************************************


//**********************************************************************************************************
//********** Funcion que haya los cruces por cero de una se�al que es pasada como parametro ****************
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
