#include <stdio.h>
#include <conio.h>

int fibonacci(int);
int main()
{
      int a;
      printf("enter value to find fibonacci term of value:");
      scanf("%d",&a);
      printf("%d nin fibonaccisi: %d",a,fibonacci(a));
      getch();
return 0;

}

int fibonacci(int k)
{
    if(k==0 || k==1)
    return k;
    else
    return (fibonacci(k-1)+fibonacci(k-2));
}
