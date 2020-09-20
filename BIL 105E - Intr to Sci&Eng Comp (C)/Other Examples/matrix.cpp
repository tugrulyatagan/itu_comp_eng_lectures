#include <iostream>             // cin,cout,endl
#include <stdlib.h>             // EXIT_SUCCESS

using namespace std;

#define MAXSIZE 30

int main(void)
{
    int left[MAXSIZE][MAXSIZE], right[MAXSIZE][MAXSIZE];
    int product[MAXSIZE][MAXSIZE] = { 0 };
    int rl, cl, cr;
    int &rr = cl;
    int i, j, k;

    cout << "Sol matrisin satir sayisi: "; cin >> rl;
    cout << "Sol matrisin sutun sayisi: "; cin >> cl;
    cout << "Sag matrisin sutun sayisi: "; cin >> cr;

    cout << "Sol matris: " << endl;
    for (i = 0; i < rl; i++) {
        for (j = 0; j < cl; j++) {
            cout << "  [" << i + 1 << "," << j + 1<< "]: ";
            cin >> left[i][j];
        }
    }

    cout << "Sag matris: " << endl;
    for (j = 0; j < rr; j++) {
        for (k = 0; k < cr; k++) {
            cout << "  [" << j + 1 << "," << k + 1 << "]: ";
            cin >> right[j][k];
        }
    }

    for (i = 0; i < rl; i++) {
        for (j = 0; j < cr; j++) {
            for (k = 0; k < cl; k++)
                product[i][j] = product[i][j] + left[i][k] * right[k][j];
        }
    }

    cout << "Carpim sonucu:" << endl;
    for (i = 0; i < rl; i++) {
        for (k = 0; k < cr; k++)
            cout << "\t" << product[i][k];
        cout << endl;
    }

    return EXIT_SUCCESS;
}
