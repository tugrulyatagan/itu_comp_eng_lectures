#include <stdio.h>
#include <conio.h>
main()
{
      int total=0,a,sayi,bolen;
      
      printf("enter sayi:");
      scanf("%d", &sayi);
      printf("sayinin bolenleri asagidadir");
      for(a=1; a<=sayi; a++){
               if(sayi%a == 0){
               printf("\n%d",a);
               total=total+a;
               }
               }
     printf("\nbolenler toplami %d dir", total);
     
      
  
      
     getch();
return 0;

}
