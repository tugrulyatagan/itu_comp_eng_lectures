#include <iostream>
#include <stdlib.h>

#define MAXSIZE 30

int main(void)
{
    int left[MAXSIZE][MAXSIZE], right[MAXSIZE][MAXSIZE];
    int product[MAXSIZE][MAXSIZE] = { 0 };
    int rl, cl, cr, rr;
    int i, j, k;

    cout << "Sol matrisin satir sayisini giriniz: "; cin >> rl;
    cout << "Sol matrisin sutun sayisini giriniz: "; cin >> cl;

    rr = cl;
    cout << "\nSag matrisin satir sayisi: " << rr << " (default olarak)\n";
    cout << "Sag matrisin sutun sayisini giriniz: "; cin >> cr;


    cout << "\nSol matris: " << endl;
    for (i = 0; i < rl; i++) {
        for (j = 0; j < cl; j++) {
            cout << "  [" << i + 1 << "," << j + 1<< "]: ";
            cin >> left[i][j];
        }
    }

    cout << "\nSag matris: " << endl;
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

    cout << "\nCarpim sonucu:" << endl;
    for (i = 0; i < rl; i++) {
        for (k = 0; k < cr; k++)
            cout << "\t" << product[i][k];
        cout << endl;
    }

    return EXIT_SUCCESS;
}
