#include <stdio.h>
int add_without_plus(int a, int b);
int main() {
	int a, b, c;
	printf("Please input a,b:\n");
	scanf("%d,%d",&a, &b);
	c = add_without_plus(a, b);
	printf("a + b(without plus): %d, a+b(real plus) = %d\n", c, a+b);

	return 0;
}

int add_without_plus(int a, int b) {
	int c, i, d;
	int count = 0;

	c = a & b;
	d = a ^ b;
	while(c != 0 && count < 32) {
		a = c << 1;
		b = d;
		d = a ^ b;
	 	c = a & b;
		count++;
	}
	if (count == 32)
		printf("overflow happens!\n");

	printf("sizeof(int):%lu\n", sizeof(int));

	return d; 
}
