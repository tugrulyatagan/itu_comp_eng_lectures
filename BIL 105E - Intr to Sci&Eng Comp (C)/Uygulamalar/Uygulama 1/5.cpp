/*********************************************
* ornek   : 1-5                              *
* aciklama: kullanicidan giris almak         *
* derleme : g++ -o program_ismi 5.cpp        *
*********************************************/

#include <iostream>

using namespace std;
int main()
{
  int a, b;

  cout << "Toplanacak sayilari giriniz: ";
  cin >> a >> b;
  cout << "Toplam = " << a + b << "\n";

  return 0;
}
