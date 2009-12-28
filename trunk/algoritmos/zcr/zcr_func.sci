//**********************************************************************************************************
//**********************************************************************************************************
//***************************** Funciones implementadas ****************************************************
//**********************************************************************************************************
//**********************************************************************************************************


//**********************************************************************************************************
//********************* Obtención de la señal a partir de un archivo .WAV **********************************
//**********************************************************************************************************
//**********************************************************************************************************

function[x, t, Fs] = wav(audio);
  
  stacksize('max'); //tamaño del stack de memoria. si se tienen problemas de stack, es necesario cargar señales de menor longitud

  select audio,    
        case 'enya'       then [x,Fs] = wavread("enya.wav"),
        case 'oasis'      then [x,Fs] = wavread("oasis.wav"),
        case 'van halen'  then [x,Fs] = wavread("van halen.wav"),
        case 'olima'      then [x,Fs] = wavread("olimareños.wav"),
        case 'zitarrosa'  then [x,Fs] = wavread("zitarrosa.wav"),
        case 'curtidores' then [x,Fs] = wavread("curtidores.wav"),
        case 'mozart'     then [x,Fs] = wavread("mozart.wav"),
        case 'soda'       then [x,Fs] = wavread("sodaStereo.wav"),
        case 'seno'       then [x,Fs] = seno(1000,44100),
     else disp('No se ha encontrado el archivo de audio'),
  end 

  N=size(x,'*');           //cantidad de muestras
  t = (0:N-1)/Fs;          //vector tiempo asociado a cada muestra
  
endfunction 

//**********************************************************************************************************


//**********************************************************************************************************
//********** Funcion que haya los cruces por cero de una señal que es pasada como parametro ****************
//**********************************************************************************************************
//**********************************************************************************************************

function[z] = zcr(s);
    
    z=0;
    for(i=2:length(s)),
        
        if(sign(s(i) * s(i-1)) == -1) //cada vez que hay un cambio de signo es que hubo un cruce por cero
            z = z + 1;
        end
    end 

endfunction  

//**********************************************************************************************************


//**********************************************************************************************************
//**************** Funcion que realiza la correlacion entre dos vectores de muestras************************
//**************************************(ver condiciones de borde)******************************************
//**********************************************************************************************************
//**********************************************************************************************************

function [r] = correlacion(x,y);
  
x = x - mean(x);
y = y - mean(y);

nx = length(x);
ny = length(y);
r = [];

for m=1:ny-nx
  sumax   = 0;
  sumay   = 0;
  sigmax  = 0;
  sigmay  = 0;
  suma    = 0;
  for k=1:nx
    yk = y(m:m+nx-1);               //tramo de y del tamaño de x
    suma = suma + (x(k)*yk(k));
    //*********************
    sumax = sumax + (x(k)*x(k));
    sumay = sumay + (yk(k)*yk(k));
  end
  //*********************
  sigmax = sqrt(sumax/nx);
  sigmay = sqrt(sumay/nx);
  //*********************
  div = sigmax*sigmay*nx;
  r(m+1) = suma/div;
end


endfunction

//**********************************************************************************************************


//**********************************************************************************************************
//**Funcion que genera un archivo de texto con los datos del array entre corchetes y separados por comas****
//**********************************************************************************************************
//**********************************************************************************************************

function [] = imp_array(arreglo);
  

fd = mopen("arreglo.txt", "w");

mfprintf(fd,'{');

mfprintf(fd,'%f', arreglo(1));

for i=2:length(arreglo)
  mfprintf(fd,',%f',arreglo(i));
end

mfprintf(fd,'};');
   							   
mclose(fd);

endfunction

//**********************************************************************************************************


//**********************************************************************************************************
//**************** Funcion que hace un seno de frecuencia f de tantos segundos como se quiera***************
//**********************************************************************************************************

function[x,fs] = seno(f,fs);
  
  pi = %pi;
  
  inicio = 0;
  fin = 30;
  
  t = [inicio:1/fs:fin];
  
  x = sin(2*pi*f*t);

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

  //Graficas de la señal normalizada vs tiempo y de la FFT

  subplot(2,2,1)
  plot2d(t,x(1,:))
  xtitle('Señal de audio','t(s)','amplitud');

  subplot(2,2,2)
  plot2d(f,abs(y(1:n)))
  xtitle('Transformada rápida de Fourier (FFT)','f(Hz)');

endfunction

//**********************************************************************************************************
