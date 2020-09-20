#include <iostream>

#define DUR 6

using namespace std;
int main()
{
   int i, j, k;

   for (i = 0; i < DUR; i++)
   {
      for (j = 0; j < DUR; j++)
      {
         for (k = 0; k < DUR; k++)
         {  
            if (k == 0)
            {
               continue;
               cout << "k : " << k << endl;
            }
			cout << "j : " << j << endl;
         }
      }
      if (j == 0)
      { 
         break;
         
      }
 
      cout << "i : " << i << endl;
   }

   return 0;
}
