syms x;
f = x^3 - 3*x + 2;
a = -4;
max_err = 0.01; % percantage
max_iter = 100;

errors = [];
df = inline(diff(f));
f = inline(f); 
for n=1:max_iter
   x = a;
   a = a - f(a)/df(a);
   errors = [errors abs((a-x)/a)*100]; % append
   if errors(end) < max_err; break; end % finish
end
display(['Root x for Newton-Raphson Method = ' num2str(x) ' with relative error = ' num2str(errors(end))]);
plot(errors);