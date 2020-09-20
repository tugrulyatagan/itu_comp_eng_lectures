#include <iostream>
#include <cmath>

#define PI 3.141593

using namespace std;

int main()

{

 float kenar1, kenar2, aci;
 float adim1, adim2, kenar3;
 int kenar_3;
 
 cout << "2 kenari ve aciyi girin: ";
 cin >> kenar1 >> kenar2 >> aci;

 aci *= PI / 180.0;

 adim1 = 2 * kenar1 * kenar2 * cos(aci);
 adim2 = (kenar1 * kenar1) + (kenar2 * kenar2) - adim1;
 kenar3 = sqrt(adim2);

 cout << "3. kenarin uzunlugu = " << kenar3 << endl;

 kenar_3 = ceil(kenar3);
 cout << "ceil ile 3. kenarin uzunlugu = " << kenar_3 << endl;

 kenar_3 = floor(kenar3);
 cout << "floor ile 3. kenarin uzunlugu = " << kenar_3 << endl;

 
 return 0;

}
