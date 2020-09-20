#include <stdio.h>
#include <conio.h>

double fibonacci(int);
int main()
{
      int a,n;
      printf("enter value to find fibonacci term of value:");
      scanf("%d",&a);
      printf("%d. fibonacci terimi: %.0f dir",a,fibonacci(a));
      for(n=0;n<=a;n++)
      printf("\n%.0f", fibonacci(n));
      getch();
return 0;

}

double fibonacci(int k)
{
    if(k==0 || k==1)
    return k;
    else
    return (fibonacci(k-1)+fibonacci(k-2));
}
