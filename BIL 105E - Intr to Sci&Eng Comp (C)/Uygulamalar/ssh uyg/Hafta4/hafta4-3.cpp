#include <iostream>

#define SINIR 10

using namespace std;

int main()

{
   int sayi;

   cout  << "Bir sayi giriniz: ";
   cin >> sayi;


   if ((sayi % 2) ==  0)
      cout << "Sayi cifttir.\n";
   else
      cout << "Sayi tektir.\n";

   cout << (!(sayi % 2) ? "Sayi cifttir.\n" : "Sayi tektir.\n");

   return 0;
}
