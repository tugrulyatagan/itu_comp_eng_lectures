// example illustrating output of integers in decimal, octal, and hex
// also illustrates the showbase and uppercase flags

#include <iostream>
#include <iomanip>
using namespace std;

void PrintValues(int x, int y, int z);

int main()
{
   int x = 123456,
       y = 987564,
       z = 12345678;

   PrintValues(x, y, z);

   cout << "Setting ios::showbase\n";
   cout.setf(ios::showbase);
   PrintValues(x, y, z);

   cout << "Setting ios::uppercase\n";
   cout.setf(ios::uppercase);
   PrintValues(x, y, z);
 
   return 0;
}

void PrintValues(int x, int y, int z)
{
   const int WID = 20;

   cout << "           " << setw(WID) << "x" 
		<< setw(WID) << "y" << setw(WID) << "z" << '\n';

   cout << dec << "Decimal    " << setw(WID) << x 
		<< setw(WID) << y << setw(WID) << z << '\n';

   cout << oct << "Octal      " << setw(WID) << x 
		<< setw(WID) << y << setw(WID) << z << '\n';

   cout << hex << "Hexadecimal" << setw(WID) << x 
		<< setw(WID) << y << setw(WID) << z << "\n\n";
}
