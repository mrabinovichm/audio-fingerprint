function[z] = zhuella(N,tcorte,Fs,t,f,fi);

for(i=1:N/tcorte),
    tiempo = dividet(tcorte,i,t,Fs);
    y = seno(f, tiempo, fi);
    z(i) = zcr(y);
end