#include <iostream>             // cin,cout,endl
#include <stdlib.h>             // EXIT_SUCCESS

using namespace std;

int main(void)
{
    int num1, num2, result; 
    char op;

    cout << "Islemi yaziniz: ";
    cin >> num1 >> op >> num2;
    switch (op) {
        case '+': result = num1 + num2;
                  break;
        case '-': result = num1 - num2; 
                  break;
        case '*': result = num1 * num2; 
                  break;
        case '/': result = num1 / num2; 
                  break;
        case '%': result = num1 % num2; 
                  break;
        default:  cout << "Boyle bir islem yok." << endl; 
                  return EXIT_FAILURE;
    }
    cout << num1 << op << num2 << " isleminin sonucu: " << result << endl;
    return EXIT_SUCCESS;
}
