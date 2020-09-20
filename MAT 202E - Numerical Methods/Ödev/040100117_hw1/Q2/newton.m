x0 = linspace(0,2*pi,1000);
y0 = sin(x0);
SamplePoints = linspace(0,2*pi,20)
N = [3, 5, 9, 20];
z=1;
P = zeros(1,4);
ip = input('Enter X coordinate for interpolation: ');

for n=N
    if n == N(1)
        x3 = SamplePoints([2,9,17]);
        y3 = sin(x3);
        X = x3;
        Y = y3;
    elseif n == N(2)
        x5 = SamplePoints([2,5,9,14,17]);
        y5 = sin(x5);
        X = x5;
        Y = y5;
    elseif n == N(3)
        x9 = SamplePoints([1,2,5,7,9,11,14,17,19]);
        y9 = sin(x9);
        X = x9;
        Y = y9;
    elseif n == N(4)
        x20 = SamplePoints;
        y20 = sin(x20);
        X = x20;
        Y = y20;
    end
    
    A(n,n) = 0;
    for k=1:n
        A(k,1) = Y(k);
    end
    for k=2:n
        for l=1:n-k+1
            A(l,k) = (A(l+1,k-1)-A(l,k-1))/(X(k+l-1)-X(l));
        end
    end
    for k=1:n
        multp = A(1,k);
        for l=1:k-1
            multp = multp*(ip-X(l));
        end
        P(z) = multp + P(z);
    end
    z = z + 1;
end

display(['p(x) points are = ' num2str(P)]);
plot(x0,y0,x3,y3,x5,y5,x9,y9,x20,y20);