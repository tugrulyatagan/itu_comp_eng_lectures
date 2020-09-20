#include <iostream>


using namespace std;
int main()
{
   int sayi;

   cout << "sayiyi giriniz: ";
   cin >> sayi;

   int i = sayi, j;

   while (i > 0)
   {
      j = i % 10;
      cout << j;
         i /= 10;
   }

   cout << endl;  

   return 0;
}
