#include <iostream>

using namespace std;

int main()

{

   int sayi;

   cout  << "Bir sayi giriniz: ";
   cin >> sayi;

   if ((sayi % 3) ==  0)
      cout << "Sayi 3'un katidir.\n";
   else if ((sayi % 3) == 2)
      cout << "3'e bolumunden kalan 2'dir.\n";
   else
      cout << "3'e bolumunden kalan 1'dir.\n";

   return 0;

}
