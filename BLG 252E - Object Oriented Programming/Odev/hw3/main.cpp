#include <iostream>
#include <cstdlib>
#include <ctime>
#include "ArithmeticVector.h"
using namespace std;
int main() {
    srand(time(NULL));
    ArithmeticVector<int> v1(3); // creating some objects
    ArithmeticVector<int> v2(3); // vector elements are assigned randomly from 0 to 10
    ArithmeticVector<double> v3(5);
    ArithmeticVector<double> v4(5);
    try {
        // trying to get the element at(4)
        // should give an error
        cout << v1[4] << endl;
    } catch (const string & err_msg) {
        cout << err_msg << endl;
    }
    cout << "Printing v4" << endl;
    v4.print();
    try {
        // trying to divide two vectors
        ArithmeticVector<double> v6 = v4 / v3;
        cout << "Printing v6" << endl;
        v6.print();
    } catch (const string & err_msg) {
        cout << err_msg << endl;
    }

    if (v1.contains(4))
        // checking if the Vector has an element with value 4
        cout << "Vector contains the element" << endl;
    else
        cout << "Vector does not contain the element" << endl;
    ArithmeticVector<int> v5 = v2;
    cout << "Printing v5" << endl;
    v5.print();
    try {
        v1 = v2 + v5; // sum v2 and v5 vectors and assign result to v1
        --v1; // decrement v1's vector elements by 1
        v5 = v2 / v1; // divide v2 and v1 vectors and assign result to v5
        ++v5; // increment v5's vector elements by 1
        if (v5 == v1) // comparing two vectors
            cout << "Objects are equal" << endl;
        else
            cout << "Objects are not equal" << endl;
    } catch (const string & err_msg) {
        cout << err_msg << endl;
    }
    cout << "Printing v1" << endl;
    v1.print();
    cout << "Printing v5" << endl;
    v5.print();

}

