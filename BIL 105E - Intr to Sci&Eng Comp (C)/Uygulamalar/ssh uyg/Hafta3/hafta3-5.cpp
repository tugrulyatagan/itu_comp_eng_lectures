#include <iostream>
#include <cmath>

using namespace std;

int main()

{

 float kenar1, kenar2, hipotenus;

 cout << "Ucgenin kenarlarini giriniz: ";
 cin >> kenar1 >> kenar2;

 hipotenus = sqrt((kenar1 * kenar1) + (kenar2 * kenar2));
 cout << "Ucgenin hipotenusu = " << hipotenus << " cm" << endl; 

 return 0;

}

