// ~46 satir
#include <iostream.h>
#include <stdlib.h>

int main()
{
      int nom1, denom1, nom2, denom2, nom3, denom3;
      char tmp, op;
      cout << "Enter first rational number: ";
      cin >> nom1 >> tmp >> denom1;
      cout << "Enter second rational number: ";
      cin >> nom2 >> tmp >> denom2;
      cout << "Enter operator: ";
      cin >> op;

      switch (op)
      {
      case '+':
        nom3 = nom1*denom2 + nom2*denom1;
        denom3 = denom1 * denom2;
        break;

      case '-':
        nom3 = nom1*denom2 - nom2*denom1;
        denom3 = denom1 * denom2;
        break;

      case '*':
        nom3 = nom1 * nom2;
        denom3 = denom1 * denom2;
        break;

      case '/':
        nom3 = nom1 * denom2;
        denom3 = denom1 * nom2;
        break;

      default:
        cout << "Invalid operator!\n";
        return 1;
      }

      cout << "\nResult=" << nom3 << "/" << denom3 << "\n";

      system("PAUSE");
      return 0;
}
