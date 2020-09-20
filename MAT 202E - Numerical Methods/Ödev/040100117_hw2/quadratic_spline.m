function [ yy ] = quadratic_spline(X, Y, xx)
n=numel(X); % X'in eleman sayisi
A=zeros(3*(n-1),3*(n-1)); % katsayilar matrisi olustur

XY= sortrows(transpose([X;Y]),1); % vektorleri birlestir ve X'e gore sirala
X=XY(:,1); % siralanmis ilk sutun X
Y=XY(:,2); % siralanmis ikinci sutun Y

for k=0:n-2 % X^2'ler icin katsayilari bul matrise ekle
    A(2*k+1,3*k+1)=(X(k+1))*(X(k+1)); % X^2'nin katsayisi a
    A(2*k+1,3*k+2)=X(k+1); % X'in katsayisi b
    A(2*k+1,3*k+3)=1; % sabit katsayi c
    % bir sonraki noktanin katsayilari
    A(2*k+2,3*k+1)=(X(k+2))*(X(k+2)); % X^2'nin katsayisi a
    A(2*k+2,3*k+2)=X(k+2); % X'in katsayisi b
    A(2*k+2,3*k+3)=1; % sabit katsayi c
end

for k=0:n-3 % 2*X'ler icin katsayilari bul matrise ekle
    A(2*n-1+k,3*k+1)=2*X(k+2);
    A(2*n-1+k,3*k+2)=1;
    % bir sonraki noktanin katsayilari
    A(2*n-1+k,3*k+4)=-2*X(k+2);
    A(2*n-1+k,3*k+5)=-1;
end
A(3*(n-1),1)=1;

B=zeros(1,3*(n-1)); % noktalarin sonuclarini iceren matrisi olustur
B(1)=Y(1); % ilk nokta degeri ve
B(2+2*(n-2))=Y(end); % son nokta degeri bir kere yazilir

for k=0:n-3
    B(2*k+2)=Y(k+2); % geri kalan nokta sonuclari 2 kere yazilir
    B(2*k+3)=B(2*k+2);
end

S=transpose(A\transpose(B)); %cozum matrisini bul

for t=1:numel(xx); % tum istenen noktalar icin
    for k=0:n-2 % belli deger araliklari icerisinde
        if X(k+1) <= xx(t) && xx(t) <= X(k+2) % araligi kontrol et
            yy(t) = S(3*k+1)*xx(t)*xx(t) + S(3*k+2)*xx(t) + S(3*k+3); % degiskenleri denklem icine yaz
        end
    end
end
