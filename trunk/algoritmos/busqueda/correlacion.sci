function [r] = correlacion(x,y);
  
x = x - mean(x);
y = y - mean(y);

nx = length(x);
ny = length(y);
r = [];

for l=1:ny-2*nx
  for m=0:nx-1
    sumax   = 0;
    sumay   = 0;
    sigmax  = 0;
    sigmay  = 0;
    suma    = 0;
    for k=1:nx
      yk = y(l:l+2*nx-1);
      suma = suma + (x(k)*yk(m+k));
      //*********************
      sumax = sumax + (x(k)*x(k));
      sumay = sumay + (yk(k)*yk(k));
    end
    //*********************
    sigmax = sqrt(sumax/nx);
    sigmay = sqrt(sumay/nx);
    //*********************
    div = sigmax*sigmay*nx;
    r(l+m) = suma/div;
  end
end
