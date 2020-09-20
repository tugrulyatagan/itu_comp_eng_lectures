#include <stdio.h>

int fact(int k);

int main(void)
{
    int x, y;

    printf("x: ");
    scanf("%d", &x);
    y = fact(x);
    printf("%d\n", y);
    return 0;
}
