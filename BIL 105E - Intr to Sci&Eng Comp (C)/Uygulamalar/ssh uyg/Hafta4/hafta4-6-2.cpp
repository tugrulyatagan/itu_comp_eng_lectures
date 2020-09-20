#include <iostream>

using namespace std;

int main()
{

   int a, b, c;

while(true){


   cout  << "Dizilecek 3 sayiyi giriniz: ";
   cin >> a >> b >> c;


   if ((a == b) && (b == c)){
      cout << "Hepsi esittir." << endl;
   }

   else if (a == b){
      cout << a << " ile " << b << " esittir" << endl;
      if (a > c){
         cout << c << " kucuktur" << endl;
      }
      else if (c > a){
         cout << c << " buyuktur" << endl;
      }
   }


   else if (a == c){
      cout << a << " ile " << c << " esittir" << endl;
      if (a > b){
         cout << b << " kucuktur" << endl;
      }
      else if (b > a){
         cout << b << " buyuktur" << endl;
      }
   }

   else if (c == b){
      cout << c << " ile " << b << " esittir" << endl;
      if (c > a){
         cout << a << " kucuktur " << endl;
      }
      else if (a > c){
         cout << a << " buyuktur " << endl;
      }
   }


   else if ((a > b) && (a > c)){
      cout << "En buyuk sayi: " << a << endl;
      if (b > c){
         cout << "Ikinci buyuk sayi: " << b << endl;
         cout << "En kucuk sayi: " << c << endl;
      }
      else if (c > b){
         cout << "Ikinci buyuk sayi: " << c << endl;   
         cout << "En kucuk sayi: " << b << endl;
      }
   }

   else if ((b > a) && (b > c)){
      cout << "En buyuk sayi: " << b << endl;
      if (a > c){
         cout << "Ikinci buyuk sayi: " << a << endl;   
         cout << "En kucuk sayi: " << c << endl;
      }
      else if (c > a){
         cout << "Ikinci buyuk sayi: " << c << endl;             
         cout << "En kucuk sayi: " << a << endl;
      }
   }

   else if ((c > a) && (c > b)){
      cout << "En buyuk sayi: " << c << endl;    
      if (a > b){
         cout << "Ikinci buyuk sayi: " << a << endl;
         cout << "En kucuk sayi: " << b << endl;
      }
      else if (b > a){
         cout << "Ikinci buyuk sayi: " << b << endl;
         cout << "En kucuk sayi: " << a << endl;
      }
   }

}

   return 0;
}
