#include <iostream>
#include <iomanip>

#define PI 3.1415

using namespace std;

int main()

{

 float yaricap, cevre, alan;

 cout << "Yaricapi giriniz: "; 
 cin >> yaricap;

 cevre = (2 * yaricap) * PI;
 alan = PI * yaricap * yaricap;

 cout << "Cemberin cevresi = " << fixed << setw(7) << setprecision(2) << right << cevre << endl;
 cout << "Dairenin alani   = " << fixed << setw(7) << setprecision(2) << right << alan << endl;
 

 return 0;

}

