// BIL105E MIDTERM EXAM
// SOLUTION OF POLYGON QUESTION

/* TEST DATA FOR POLYGON PROBLEM:
   Inputs:              N = 5 ,  Point coordinates = (3 7) (6 4) (3 -2) (-6 1) (-6 7)
   Expected outputs:    A = 81 , Cx = 0  , Cy = 3
*/

#include <iostream.h>
#include <stdlib.h>

int main()
{
      int X[100],Y[100]; // Arrays to keep points coordinates in the polygon
      int Cx, Cy;        // Centroid coordinates to be computed.
      double A;          // Area of polygon to be computed.
      double TotX, TotY, term;
      int i, j, N;

      cout << "Enter number of edges : "; 
      cin >> N;

      A = 0; TotX = 0; TotY = 0;

      // Get all point coordinates of polygon:
      for (i=0; i <= N-1; i++)
      {
          cout << "Enter X and Y for " << i << ". point : ";
          cin >> X[i] >> Y[i];
      }

      // Calculate area:
      for (i=0; i <= N-1; i++)
      {
          if (i == N-1)
             j = 0;
          else
             j = i+1;

          term = (X[i]*Y[j]) - (X[j]*Y[i]);
          A = A + term;
          TotX += (X[i]+X[j]) * term;
          TotY += (Y[i]+Y[j]) * term;
      }

      A = A / 2;

      // Calculate centroid coordinates:
      Cx = TotX /(6*A);
      Cy = TotY /(6*A);

      cout << "AREA= " << fabs(A) << "  Cx= " << Cx << "  Cy= " << Cy << "\n\n";

      system("PAUSE");
      return 0;
}
