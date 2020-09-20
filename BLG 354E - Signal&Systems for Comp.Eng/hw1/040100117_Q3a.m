syms x t
h = @(t) 10*exp(-10*t);         % h(t)

y = @(t) int(h(x),x,0,t);       % integral of h(t)*x(t) for 0 to t

ezplot(y(t),[0,1])