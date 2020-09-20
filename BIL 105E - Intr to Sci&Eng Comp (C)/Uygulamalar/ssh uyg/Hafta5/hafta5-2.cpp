#include <iostream>

using namespace std;
int main()
{
   int i, j;

   cout << "Farkli iki sayi giriniz: ";
   cin >> i >> j;

   (i>j) ? cout << i << " > " << j << endl : cout << i << " < " << j << endl;

   return 0;
}
