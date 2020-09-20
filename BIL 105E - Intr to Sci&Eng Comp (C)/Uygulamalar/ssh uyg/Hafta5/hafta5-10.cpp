#include <iostream>

using namespace std;
int main()
{
   char sekil;
   int yukseklik, i, j;

   cout << "Sekili olusturulacak karakteri ve yuksekligi giriniz: ";

   cin >> sekil >> yukseklik;

   for (i = 1; i <= yukseklik; i++)
   {
      for (j = 0; j < yukseklik - i; j++) cout << " ";
      for (j = 0; j < (2 * i) - 1; j++) cout << sekil;
      cout << endl;
   }
   
   return 0;
}
