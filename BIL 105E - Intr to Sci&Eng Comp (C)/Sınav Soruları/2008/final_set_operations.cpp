#include <iostream.h>
#include <stdlib.h>

void Display_Array(int X[], int NX)
{
   int i;

   for (i=0; i < NX; i++)
       cout << X[i] << "  ";
   cout << "\n\n";
}

// In the exam, only set functions were required.
//--------------------------------------------------------------------------------
void Unification(int A[], int B[], int C[], int NA, int NB, int & NC)
{
   int i;
   int k = 0; // Counter index of C array

   for (i=0; i < NA; i++)
   {
       C[k] = A[i];
       k++;
   }

   for (i=0; i < NB; i++)
   {
       C[k] = B[i];
       k++;
   }

   NC = k; // Number of elements in C
}

//--------------------------------------------------------------------------------
void Intersection(int A[], int B[], int C[], int NA, int NB, int & NC)
{
   int i, j;
   int k = 0; // Counter index of C array

   for (i=0; i < NA; i++)
   {
       for (j=0; j < NB; j++)
       {
           if (A[i] == B[j])
           {
              C[k] = A[i];
              k++;
           }
       }
   }

   NC = k; // Number of elements in C

}

//--------------------------------------------------------------------------------
void Difference(int A[], int B[], int C[], int NA, int NB, int & NC)
{
   int i, j;
   int k = 0; // Counter index of C array
   bool found;

   for (i=0; i < NA; i++)
   {
       found = false;
       for (j=0; j < NB; j++)
       {
           if (A[i] == B[j])
           {
              found = true;
              break; // Skip the rest of j loop
           }
       }

       if (!found)
       {
          C[k] = A[i];
          k++;
       }
   }

   NC = k; // Number of elements in C
}

//--------------------------------------------------------------------------------


int main()
{
   int NA, NB, NC;

   int A[] = {1,4,5,6,2};
   int B[] = {6,3,4,7};
   int C[NC];
   int i;

   NA = sizeof(A)/sizeof(int);
   NB = sizeof(B)/sizeof(int);
   NC = NA + NB;

   cout << "A = "; Display_Array(A, NA);
   cout << "B = "; Display_Array(B, NB);

   Unification(A, B, C, NA, NB, NC);
   cout << "Unification = "; Display_Array(C, NC);

   Intersection(A, B, C, NA, NB, NC);
   cout << "Intersection = "; Display_Array(C, NC);

   Difference(A, B, C, NA, NB, NC);
   cout << "Difference = "; Display_Array(C, NC);

   cout << "\n";
   system("PAUSE");
   return 0;
}


