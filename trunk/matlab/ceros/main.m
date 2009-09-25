clear all;  %limpia variables
close all;  %cierra ventanas
clc;        %limpia pantalla

Fs = 100;         %frecuencia de muestreo en Hz. 
Ts = 1/Fs;          %Periodo de muestreo en segundos.

f = 7;            %frecuencia de la señal sinusoidal.
fi = 0;             %argumento de la señal sinusoidal.

%se genera un vector de tiempos a partir de la frecuencia de muestreo de longitud Fs.
t=[0:Fs] * Ts;

y = seno(f, t, fi);
plot(t, y, '*-');
title('Seno de frecuencia f Hz');
xlabel('Tiempo (segundos)');
ylabel('Amplitud');
grid;

z = zcr(y);         %z es el total de cruces por cero de la señal que se le pasa como argumento.
disp(sprintf('Cruces por cero = %.0f', z))