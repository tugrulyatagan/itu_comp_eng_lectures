#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
int main()

{
   int a, b;

   for (;;)
   {
      cout << "iki kenari gir: ";
      cin >> a >> b;

      if (a >0 && b >0)
      {
         cout << "sonuc: " << fixed << setprecision(2) << pow(a * a + b * b, 0.5) << endl;
         break;
      }
      else
        cout << "farkli degerler giriiz..." << endl;
   }
   return 0;
}
