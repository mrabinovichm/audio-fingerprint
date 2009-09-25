%********* Funcion que genera sañales sinusoidales ************
%********* se pasan como parametro, frecuencia en Hz, tiempo en segundos y el argumento en radianes**********

function[y] = seno(f, t, fi);

    x = 2*pi*f*t + fi;
    y = sin(x);

