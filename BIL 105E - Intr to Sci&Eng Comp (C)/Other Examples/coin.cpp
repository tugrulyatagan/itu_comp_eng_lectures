#include <iostream>             // cin,cout,endl
#include <stdlib.h>             // EXIT_SUCCESS,srand,rand,RAND_MAX
#include <time.h>               // time

using namespace std;

int main(void)
{
    int count, i;
    float number;
    int heads = 0, tails = 0;

    cout << "Kac kere atilacak? ";
    cin >> count;
    srand(time(NULL));
    for (i = 1; i <= count; i++) {
        number = (float) rand() / RAND_MAX;
        if (number < 0.5) {
            cout << "Tura" << endl;
            heads++;
        } else {
            cout << "Yazi" << endl;
            tails++;
        }
    }
    cout << "  Tura sayisi: " << heads
         << ", Yuzdesi: %" << 100.0 * heads / count << endl;
    cout << "  Yazi sayisi: " << tails
         << ", Yuzdesi: %" << 100.0 * tails / count << endl;
    return EXIT_SUCCESS;
}
