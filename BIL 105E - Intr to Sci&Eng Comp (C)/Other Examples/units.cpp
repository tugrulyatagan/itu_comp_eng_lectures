#include <iostream>             // cout,cin,endl
#include <stdlib.h>             // EXIT_SUCCESS,EXIT_FAILURE

using namespace std;

int main(void)
{
    int choice;
    float inch, cm, f, c;

    cout << "1. inch-cm" << endl;
    cout << "2. f-c" << endl;
    cout << "3. Cikis" << endl;
    cout << "Seciminiz: ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "inch cinsinden uzunluk: ";
            cin >> inch;
            cm = 2.54 * inch;
            cout << cm << " cm" << endl;
            break;
        case 2:
            cout << "f cinsinden sicaklik: ";
            cin >> f;
            c = (f - 32) * 5.0 / 9.0;
            cout << c << " C" << endl;
            break;
        case 3:
            return EXIT_SUCCESS;
        default:
            cout << "Boyle bir islem yok." << endl;
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
