%********* Funcion que haya los cruces por cero de una señal que es pasada como parametro **********


function[z] = ZCR(s);
    
    z=0;
    for(i=2:length(s)),
        
        if(sign(s(i) * s(i-1)) == -1)
            z = z + 1;
        end
    end    