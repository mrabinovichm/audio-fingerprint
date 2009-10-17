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

function[d_norm] = dif_norm(xi, S, W, Tau_max);
   
   d_norm(1) = 1;                                      //1er elemento vale 1, cuando Tau = 0, por definici�n
   suma = 0;
   for tau=2:floor(Tau_max/3)                                           
      if tau <> 2 then 
            daux = d3
            d3 = sum( (xi(2*S+1 : W) - xi(tau+2*S+1 : W + tau)).^2 );    //diferencia en un intervalo de 5ms
            d  = d - d1 + d3;
            d1 = d2;
            d2 = daux;            
      else                              //la primera iteracion calcula la diferencia en un intervalo de 15ms
            d1 = sum( (xi(1 : S) - xi(tau : S + tau - 1)).^2 ); 
            d2 = sum( (xi(S+1 : 2*S) - xi(tau+S+1 : 2*S + tau)).^2 );
            d3 = sum( (xi(2*S+1 : W) - xi(tau+2*S+1 : W + tau)).^2 );
            d = d1 + d2 + d3;
      end
      suma = suma + d;                                    
      d_norm(tau) = d/(suma/(tau-1));
   end
   
endfunction  

//**********************************************************************************************************


//**********************************************************************************************************
//**************** Funcion que halla la frecuencia fundamental f0 en un tramo de se�al *********************
//**********************************************************************************************************

function[f0] = yin(d_n, fs);
    
   [min_a, ind] = min(d_n); 
   umbral = min_a + min_a * 0.7 ;       //el umbral est� un 10% por encima del minimo absoluto
 
   minimos = [];
   lugar = [];
   for i=2:length(d_n)-1
      if(d_n(i-1)>d_n(i)) & (d_n(i+1)>d_n(i)) & (umbral>d_n(i)) then
            minimos = [minimos d_n(i)];
            lugar   = [lugar i];        
      end
   end

   [m ind] = min(minimos);              //me quedo con el menor de los minimos
   f0 = fs/lugar(ind);
 
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
