%Esta funcion recibe en: 
%N -------> tiempo en segundos del vector de tiempo,
%tcorte --> tiempo que dura el tramo, 
%Fs ------> la frecuencia de muestreo,
%t -------> vector de tiempo,
%f -------> frecuencia de la señal sinusoidal,
%fi ------> argumento de la señal sinusoidal.

%devuelve en:
%z -------> un arreglo de huellas, de los tramos que correspondan segun el N/tcorte.


function[z] = zhuella(N,tcorte,Fs,t,f,fi);

for(i=1:N/tcorte),
    tiempo = dividet(tcorte,i,t,Fs);
    y = seno(f, tiempo, fi);
    z(i) = zcr(y);
end