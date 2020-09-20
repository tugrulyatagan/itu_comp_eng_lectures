syms x t
h = @(t) 10*exp(-10*t);         % h(t)

y0 = @(t) 0*t;                  % y(t) = 0 for t < 0
y1 = @(t) int(h(x),x,0,t);      % integral of h(t)*x(t) for 0 to t
y2 = @(t) int(h(x),x,t-2,t);    % integral of h(t)*x(t) for t-2 to t

hold on;
ezplot(y0(t),[0,3]);            % t < 0           
ezplot(y1(t),[0,3]);            % 0 < t < 2
ezplot(y2(t),[0,3]);            % 2 < t