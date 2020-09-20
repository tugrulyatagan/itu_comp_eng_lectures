#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
      int k, N;
      long int X;
      int which_number, length, max_length = -1;

      cout << "Enter upper limit: ";
      cin >> N;

      for (k=1; k <= N; k++)
      {
        cout << "Number= " << k << " , Ackermann Sequence= " << k << "  ";

        X = k;
        length = 1; // Count of Ackermann numbers

        // Generate all Ackermann numbers for X
        do
        {
           if (X % 2 == 0)
              X = X / 2;
           else
              X = 3 * X + 1;

           cout << X << "  ";

           length++;

        } while (X != 1);

        cout << "\n";

        // Compare with the longest length so far:
        if (length > max_length)
        {
           which_number = k;    // New number having longest sequence
           max_length = length; // New maximum sequence length
        }

      }
      cout << "\n\n";
      cout << "NUMBER HAVING THE LONGEST SEQENCE= " << which_number << "  ";
      cout << "WITH LENGTH= " << max_length << "\n\n";

      system("PAUSE");
      return 0;
}
