clear all;          %limpia variables
close all;          %cierra ventanas
clc;                %limpia pantalla

Fs = 48000;         %frecuencia de muestreo en Hz. 
Ts = 1/Fs;          %Periodo de muestreo en segundos.
N = 6;              %Segundos del tramo del vector tiempo.
tcorte = 1;         %tiempo de corte para la funcion dividet (segundos)

f = 8000;           %frecuencia de la señal sinusoidal (Hz).
fi = 0;             %argumento de la señal sinusoidal (rad).

%------------------------------------------------------------------------------------------------
%Generacion de señales para prueba

%se generan vectores de tiempo a partir de la frecuencia de muestreo de longitud Fs.
t1=[0:2*Fs] * Ts;
t2=[2*Fs+1:4*Fs] * Ts;
t3=[4*Fs+1:6*Fs] * Ts;


t = [t1,t2,t3];

f1 = 100;
f2 = 1000;
f3 = 10000;

y1 = seno(f1, t1, fi);
y2 = seno(f2, t2, fi);
y3 = seno(f3, t3, fi);

y = [y1,y2,y3];

% plot(t, y, '*-');
% title('Seno de frecuencia f Hz');
% xlabel('Tiempo (segundos)');
% ylabel('Amplitud');
% grid;

z = zcr(y);         %z es el total de cruces por cero de la señal que se le pasa como argumento.
disp(sprintf('Cruces por cero (toda la senal) = %.0f', z))
%------------------------------------------------------------------------------------------------


z1 = zhuella(2,tcorte,Fs,t,f1,fi);
z2 = zhuella(2,tcorte,Fs,t,f2,fi);
z3 = zhuella(2,tcorte,Fs,t,f3,fi);

z = [z1,z2,z3]

%------------------------------------------------------------------------------------------------
tprueba = [2*Fs+1:3*Fs]*Ts;
yprueba = seno(f2,tprueba,fi);
zprueba = zcr(yprueba);

error = 0.1;
[esta,ind] = buscarZ (zprueba,z,error);

