#include <stdio.h>

int sum(int x, int y){
	int result;
	result = x+y;
	return result;
};

int main(void)
{
    int x, y, z;

    printf("Enter numbers: ");
    scanf("%d %d", &x, &y);
    z = sum(x, y);
    printf("The sum is: %d\n", z);
    return 0;
}
