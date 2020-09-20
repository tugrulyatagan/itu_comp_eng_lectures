#include <iostream>

#define SINIR 10

using namespace std;

int main()

{

   int sayi;

   cout  << "Bir sayi giriniz: ";
   cin >> sayi;


/*
   if ((sayi % 2) ==  0)
      cout << "Sayi cifttir.\n";
   else
      cout << "Sayi tektir.\n";
*/


   !(sayi % 2) ? cout << "Sayi cifttir.\n" : cout << "Sayi tektir.\n";


   return 0;

}
