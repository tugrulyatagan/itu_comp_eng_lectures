#include <iostream>

using namespace std;

int main()

{

   int sayi;

   cout  << "Bir sayi giriniz: ";
   cin >> sayi;

   if (( !(sayi % 7) && !(sayi % 5)))
      cout << "Sayi 5'e ve 7'ye tam bolunur.\n";
   else if ( !(sayi % 5))
      cout << "Sayi 5'e tam bolunur.\n";
   else if ( !(sayi % 7))
      cout << "Sayi 7'ye tam bolunur.\n";
   else
      cout << "Sayi 5'e de 7'ye de bolunemez.\n";

   return 0;

}
