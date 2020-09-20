#include <stdio.h>
#include <conio.h>
main()
{
      int i,j,array[5];
      printf("enter array values\n");
      for(i=0;i<5;i++)
      scanf("%d",&array[i]);
      
      printf("%s \t%s \t%s","eleman","deger","yildiz");
      
      for(i=0;i<5;i++){
      printf("\n%d \t%d\t",i+1,array[i]);
      for(j=0;j<array[i];j++)
      printf("*");
      }
   
      
     getch();
return 0;

}
