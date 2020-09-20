#include <iostream>             // cin,cout,endl
#include <stdlib.h>             // EXIT_SUCCESS
#include <math.h>               // pow

#define MAXFACTOR 50

struct factor_s {
    int base;
    int power;
};
typedef struct factor_s   factor_t;


void factorize(int x, factor_t  factors[], int &n);

void gcd_factors(const factor_t  factors1[], int n1,
                 const factor_t  factors2[], int n2,
                       factor_t  factors[], int &n);

int main(void)
{
    int number1, number2;
    factor_t  factors1[MAXFACTOR], factors2[MAXFACTOR], factors3[MAXFACTOR];
    int n1, n2, n3;
    long int gcd = 1L;
    int i;

    cout << "Iki Sayi yaziniz: ";
    cin >> number1 >> number2;
    factorize(number1, factors1, n1);
    factorize(number2, factors2, n2);

    cout << "\nFactors of number1: ";
    for (i = 0; i < n1; i++)
        cout << factors1[i].base << "^" << factors1[i].power << "   ";

    cout << "\nFactors of number2: ";
    for (i = 0; i < n2; i++)
        cout << factors2[i].base << "^" << factors2[i].power << "   ";

    gcd_factors(factors1, n1, factors2, n2, factors3, n3);

    cout << "\n\nFactors of GCD: ";
    for (i = 0; i < n3; i++)
    {
        cout << factors3[i].base << "^" << factors3[i].power << "   ";
        gcd = gcd * (long int) pow((double) factors3[i].base,(double) factors3[i].power);
    }
    cout << "\n\nEn buyuk ortak bolen: " << gcd << endl;

    cout << endl << endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}

bool is_prime(int cand)
{
    int count;

    if (cand == 2)
        return true;
    if (cand % 2 == 0)
        return false;
    for (count = 3; count * count <= cand; count += 2) {
        if (cand % count == 0)
            return false;
    }
    return true;
}

int next_prime(int prime)
{
    int cand = (prime % 2 == 0) ? prime + 1 : prime + 2;

    while (!is_prime(cand))
        cand += 2;
    return cand;
}

void factorize(int x, factor_t factors[], int &n)
{
    int factor = 2;

    n = 0;
    while (x > 1) {
        if (x % factor == 0) {
            factors[n].base = factor;
            factors[n].power = 0;
            while (x % factor == 0) {
                factors[n].power++;
                x = x / factor;
            }
            n++;
        }
        factor = next_prime(factor);
    }
}

void gcd_factors(const factor_t factors1[], int n1,
                 const factor_t factors2[], int n2,
                 factor_t factors[], int &n)
{
    int i1 = 0, i2 = 0;

    n = 0;
    while ((i1 < n1) && (i2 < n2)) {    // iki dizi de bitmedi
        if (factors1[i1].base < factors2[i2].base)
            i1++;
        else if (factors1[i1].base > factors2[i2].base)
            i2++;
        else {
            factors[n].base = factors1[i1].base;
            if (factors1[i1].power < factors2[i2].power)
                factors[n].power = factors1[i1].power;
            else
                factors[n].power = factors2[i2].power;
            i1++;
            i2++;
            n++;
        }
    }
}
