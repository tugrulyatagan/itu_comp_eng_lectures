syms x;
f = inline( x^3 - 3*x + 2 );
a = -4;
b = -4.1;
max_err = 0.01; % percentage
max_iter = 100;

errors = [];
for n=1:max_iter
   x = b;
   b = b - f(b)*(b-a)/(f(b)-f(a));
   a = x;
   errors = [errors abs((b-a)/b)*100]; % appending
   if errors(end) < max_err; break; end 
end
display(['Root x for Secant Method = ' num2str(x) ' with relative error = ' num2str(errors(end))]);
plot(errors);