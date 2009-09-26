clear all;          %limpia variables
close all;          %cierra ventanas
clc;                %limpia pantalla

Fs = 48000;         %frecuencia de muestreo en Hz. 
Ts = 1/Fs;          %Periodo de muestreo en segundos.
N = 6;              %Segundos del tramo del vector tiempo.
tcorte = 1;         %tiempo de corte para la funcion dividet (segundos)

f = 8000;           %frecuencia de la se�al sinusoidal (Hz).
fi = 0;             %argumento de la se�al sinusoidal (rad).

%------------------------------------------------------------------------------------------------
%Generacion de se�ales para prueba

%se genera vector de tiempo a partir de la frecuencia de muestreo de longitud Fs.
t=[0:N*Fs] * Ts;
t1=[0:Fs] * Ts



% plot(t, y, '*-');
% title('Seno de frecuencia f Hz');
% xlabel('Tiempo (segundos)');
% ylabel('Amplitud');
% grid;

z = zcr(y);         %z es el total de cruces por cero de la se�al que se le pasa como argumento.
disp(sprintf('Cruces por cero (toda la senal) = %.0f', z))
%------------------------------------------------------------------------------------------------