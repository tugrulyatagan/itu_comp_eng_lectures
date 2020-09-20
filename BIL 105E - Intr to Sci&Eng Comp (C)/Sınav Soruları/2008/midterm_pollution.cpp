// BIL105E MIDTERM EXAM
// SOLUTION OF POLLUTION QUESTION

#include <iostream.h>
#include <stdlib.h>

int main()
{
      int P; // Pollution variable
      int TL=0, TM=0, TH=0; // Totals for Low, Medium, and High
      int CL=0, CM=0, CH=0; // Counters for Low, Medium, and High

      cout.setf(ios::showpoint); // Allow decimal points to display

      // Get air pollution values from user:
      while (1) // Infinite loop
      {
        cout << "Enter P (-1 to stop) : ";
        cin >> P;

        if (P == -1) // Terminate infinite loop
            break;

        if (P >= 0 && P < 5)  { TL += P; CL++;}
        if (P >= 5 && P < 20) { TM += P; CM++;}
        if (P >= 20)          { TH += P; CH++;}
      }

      // Calculate averages and display messages:
      cout << "\n\n";
      cout << "Avg. of Low Levels= ";
      if (CL > 0) cout << (float) TL / CL;
      else cout << "No data";
      cout << endl;

      cout << "Avg. of Medium Levels= ";
      if (CM > 0) cout << (float) TM / CM;
      else cout << "No data";
      cout << endl;

      cout << "Avg. of High Levels= ";
      if (CH > 0) cout << (float) TH / CH;
      else cout << "No data";
      cout << endl;

      cout << "\n";
      system("PAUSE");
      return 0;
}
