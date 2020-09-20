/* Ilk C programim.                                             *
 *                                                              *
 * Yaricapi verilen bir dairenin cevresini ve alanini hesaplar. */

#include <iostream>             // cout,cin,endl icin
#include <stdlib.h>             // EXIT_SUCCESS icin

using namespace std;

#define PI 3.14

int main(void)
{
    float radius; 
    float circum, area;

    cout << "Yaricapi yaziniz: ";
    cin >> radius;
    circum = 2 * PI * radius;
    area = PI * radius * radius;
    cout << "Cevresi: " << circum << endl;
    cout << "Alani: " << area << endl;
    return EXIT_SUCCESS;
}
