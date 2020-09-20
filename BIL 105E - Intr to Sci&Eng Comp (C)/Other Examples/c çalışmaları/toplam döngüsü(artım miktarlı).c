#include <stdio.h>
#include <conio.h>
main()
{
      int total=0,a,sayi,bolen;
      
      printf("enter sayi:");
      scanf("%d", &sayi);
      printf("\nenter bolen:");
      scanf("%d", &bolen);
      
      if(sayi%bolen==0)
      printf("sayi kalansiz bolunur");
      
      else
      printf("sayi kalansiz bolunmez, kalan %d dir", sayi%bolen);
      
     getch();
return 0;

}
