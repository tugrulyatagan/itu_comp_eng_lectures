#include<iostream>

using namespace std;

int main()

{

  int x, y, z;

   z = 1;
   x = y = z;
   cout << "x = " << x  << "\t y = " << y << " \t z = " << z << endl;

   x = ++y + ++z; //once deger artirilir sonra atama
   cout << "x = " << x << " \t y = " << y << " \t z = " << z << endl;

   x = y++ + z++; //once atama yapilir sonra deger artirma
   cout << "x = " << x << " \t y = " << y << " \t z = " << z << endl;

   x = y == z; // y ile z kiyaslanir sonuc 0 yada 1
   cout << "x = " << x << " \t y = " << y << " \t z = " << z << endl;

   x = y == --z; //once deger azaltilir sonra kiyaslama
   cout << "x = " << x << " \t y = " << y << " \t z = " << z << endl;


   return 0;

}

