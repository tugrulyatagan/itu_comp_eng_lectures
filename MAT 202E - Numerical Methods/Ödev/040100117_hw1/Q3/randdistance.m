function[distance] = randdistance()
a = [1,1];
b = [1,1];

while a(1).^2+a(2).^2 >= 1
    a = 2*rand(1,2) - 1;
end
while b(1).^2+b(2).^2 >= 1
    b = 2*rand(1,2) - 1;
end

distance = sqrt((a(1)-b(1))^2 + (a(2)-b(2))^2);
end