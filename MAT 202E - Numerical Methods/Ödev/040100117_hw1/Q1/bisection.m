syms x;
f = inline( x^3 - 3*x + 2 );
xl = -4;
xu = -1;
max_err = 0.01; % percantage
max_iter = 100;

errors = [];
xm=0;
for n=1:max_iter
    x = xm;
    xm = (xl+xu)/2;
    xn = xm;
    errors = [errors abs((xn-x)/xn)*100]; % append
    if f(xl)*f(xm) < 0
        xu = xm;
    elseif f(xl)*f(xm) > 0
        xl = xm;
    end 
    if errors(end) < max_err; break; end % finish
end
display(['Root x for Bisection Method = ' num2str(x) ' with relative error = ' num2str(errors(end))]);
plot(errors);