#include <iostream>
#include <cstdlib>
#include <ctime>

#define SINIR 10

using namespace std;

void rastgele(void)

{
  
   cout << "Rastgele sayi: " << rand() % SINIR << endl; /* % sinir 
belirler*/

}

int main()

{
   srand(time(NULL));

   cout << "Rastgele sayi ureten program..." << endl;

   rastgele();
   rastgele();
   rastgele();
   rastgele();
   rastgele();
  

   return 0;

}
