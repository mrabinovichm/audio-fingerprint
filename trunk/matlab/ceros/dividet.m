%Esta funcion recibe en: 
%tcorte --> tiempo que dura el tramo, 
%tramo ---> tramo que quiero del vector t, 
%t -------> vector de tiempo y en 
%Fs ------> la frecuencia de muestreo.
%devuelve en:
%tiempo --> el array que contiene los valores de tiempo en el tramo deseado

function [tiempo] = dividet(tcorte,tramo,t,Fs);

i = (tramo-1)*tcorte*Fs+1:((tramo-1)+1)*tcorte*Fs;
tiempo = t(i);