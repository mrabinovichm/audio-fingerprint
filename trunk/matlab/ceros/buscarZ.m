%a partir de las huellas predeterminadas y la huella de la entrada
%se busca si esta ultima existe en las predeterminadas y en ese caso
%se devuelve un 1 en la variable esta y el numero del indice en ind
%en caso que no la encuentre en ind se devuelve siempre un 1 y en esta un 0


function [esta,ind] = buscarZ (zprueba,z,error);

ind=1;
esta=0;

while (abs(zprueba-z(ind))>error) & (ind<=length(z)-1),
    ind = ind + 1;
end

if (zprueba-z(ind)<=error)
    esta=1;
end

if esta
    disp(sprintf('Se encontro el tramo en la señal!!!...el valor buscado era %.0f y el valor encontrado es %.0f en el lugar %.0f',zprueba,z(ind),ind))
else
    disp(sprintf('No se encontro nada a menos de %f, todo esto es culpa de edgardo!!!...Se buscaba %f',error,zprueba))
end