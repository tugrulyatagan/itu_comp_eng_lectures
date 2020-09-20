n = input('Enter n iteration number(ex:1000): ');
distances(n) = 0;
meandistances(n) = 0;

for k = 1:n
    distances(k) = randdistance();
end
for k = 1:n
    for l = 1:k
        meandistances(k) = meandistances(k) + distances(l);
    end
    meandistances(k) =  meandistances(k) / k;
end
plot(meandistances)