#include <stdio.h>

int main(void)
    {
    int x, y, z;

    printf("Enter numbers: ");
    scanf("%d %d", &x, &y);

    asm ("movl  %1,%%ecx\n\t"
         "movl  %2,%%edx\n\t"
         "xorl  %%eax,%%eax\n"
         "next:\n\t"
         "shrl  $1,%%ecx\n\t"
         "jnc   even\n\t"
         "addl  %%edx,%%eax\n"
         "even:\n\t"
         "shll  $1,%%edx\n\t"
         "cmpl  $0,%%ecx\n\t"
         "jne   next\n\t"
         : "=a" (z)
         : "g" (x), "g" (y)
         : "%ecx", "%edx" );

    printf("The product is: %d\n", z);
    return 0;
    }
