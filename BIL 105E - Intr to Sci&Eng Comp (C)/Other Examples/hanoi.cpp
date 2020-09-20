#include <iostream>             // cin,cout,endl
#include <stdlib.h>             // EXIT_SUCCESS

using namespace std;

void move(int n, int a, int b, int c);

int main(void)
{
   int N;
    cout << "Enter count of disks: ";
    cin >> N;

    move(N, 1, 3, 2);
    return EXIT_SUCCESS;
}

void move(int n, int a, int b, int c)
{
    if (n > 0) {
        move(n - 1, a, c, b);
        cout << "Bir diski " << a << " direginden "
             << b << " diregine tasi." << endl;
        move(n - 1, c, b, a);
    }
}
