#include <stdio.h>
#include <stdlib.h>

unsigned int recgcd(unsigned int a, unsigned int b)
{
	if (b == 0)
		return a;
	else
		return recgcd(b, a%b);
}

unsigned int gcd(unsigned int a, unsigned int b)
{
	if ((a == 0) || (b == 0)) {
		fprintf(stderr, "Numbers can not be zero.\n");
		exit(1);
	}
	if (a >= b)
		return recgcd(a, b);
	else
		return recgcd(b, a);
}

int main(void)
{
	int x, y, z;

	printf("Numbers: ");
	scanf("%d %d", &x, &y);
	z = gcd(x, y);
	printf("GCD: %d\n", z);
	return 0;
}
