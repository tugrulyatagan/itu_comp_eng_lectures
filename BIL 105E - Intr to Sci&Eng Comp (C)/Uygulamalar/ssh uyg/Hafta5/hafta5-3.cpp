#include <iostream>

using namespace std;
int main()
{
   int i = 0, j;

   cout << "Pozitif bir tamsayi giriniz: ";
   cin >> j;

   while (i < j)
   { 
      cout << "i nin degeri: " << ++i << endl;
   }

   return 0;
}
