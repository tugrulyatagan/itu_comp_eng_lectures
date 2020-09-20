#include <stdio.h>

int main(void)
{
    int x, y;

    printf("x: ");
    scanf("%d", &x);

    asm("movl  %1,%%ecx\n\t"
        "movl  $1,%%edi\n"
        "back:\n\t"
        "movl  %%edi,%%eax\n\t"
        "mull  %%ecx\n\t"
        "movl  %%eax,%%edi\n\t"
        "decl  %%ecx\n\t"
        "cmpl  $1,%%ecx\n\t"
        "jne   back\n\t"
        : "=D" (y)
        : "g" (x)
        : "%eax", "%ecx", "%edx");

    printf("%d\n", y);
    return 0;
}
