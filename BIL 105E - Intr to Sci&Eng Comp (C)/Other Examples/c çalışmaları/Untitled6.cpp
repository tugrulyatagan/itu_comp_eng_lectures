#include <stdio.h>
#include <conio.h>
#define n 10

int main(void)
{
   int   a[n] = {100, -250, 400, 125 ,550, 900, 689, 450, 347, 700};
   int   i, j, k, eb;

   /* Dizinin kendisi */
   printf("Once : ");
   for(k=0;k<n;k++)
      printf("%5d ",a[k]);

   /* Sýrala */
   for(k=0; k<n; k++){

      eb = a[k]; 
       i = k;

       for(j=k+1; j<n; j++)
          if( a[j]>eb ){
            eb = a[j];
             i = j; 
          }

       a[i] = a[k];
       a[k] = eb;
   }

   /* Sýralama bitti */
   printf("\nSonra: ");
   for(k=0; k<n; k++)
      printf("%5d ",a[k]);

   printf("\n");
getchar();
 return 0;
}
