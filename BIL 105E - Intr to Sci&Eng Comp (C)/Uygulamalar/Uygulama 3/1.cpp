/********************************************************
* ornek   : 3-1                                         *
* aciklama: rastgele sayi ureten program			    *
* derleme : g++ -o program_ismi 1.cpp                   *
********************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>

#define SINIR 1000

using namespace std;

void rastgele(void)
{
	cout << "Rastgele sayi: " << rand() % SINIR << endl;
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
