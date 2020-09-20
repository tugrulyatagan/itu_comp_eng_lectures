#include <iostream>

using namespace std;
int main()

{
   char c;

   do
   {
      cin >> c;
      if (c != '\n')
      {
         if (!((c >= '0') && (c <= '9')))
         {
            c = c - 'a';
            c = c + 'A';
            cout <<  c;
         }
      }
   } 
   while (c != '0');

   return 0;
}
