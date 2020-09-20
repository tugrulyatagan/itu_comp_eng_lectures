#include <stdio.h>
#include <conio.h>
main()
{
      int array[10],tek[10],cift[10];
      int i,j=0, k=0;
      printf("enter 10 array values\n");
      for(i=0;i<10;i++)
      scanf("%d",&array[i]);
      
      
      for(i=0;i<10;i++)
      {
      if(array[i]%2==0)
      {
      cift[j]=array[i];
      j++;
      }
      else
      {
      tek[k]=array[i];
      k++;
      }
      }
      printf("\ntek sayilar\n");
      for(i=0;i<k;i++)
      printf("%d, ",tek[i]);
      printf("\ncift sayilar\n");
      for(i=0;i<j;i++)
      printf("%d, ",cift[i]);
      
     getch();
return 0;

}
