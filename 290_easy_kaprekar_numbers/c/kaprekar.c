#include <stdio.h>

/**
 * Returns 1 if the given number is Kaprekar number for the
 * given base.
 */
int is_kaprekar(int number, int base)
{
	int a, b, n, squared;
	int in_range;

	squared = number * number;
	n = base;

	do {
		a = squared / n;
		b = squared % n;
		in_range = b > 0 && b < n;
		if (in_range && a + b == number) {
			return 1;
		}
		n *= base;
	} while (a);

	return 0;
}


int main(int argc, char *argv[]) {
	int i;
	for (i = 0; i < 1000; ++i) {
		if (is_kaprekar(i, 10)) {
			printf("%d\n", i);
		}
	}
	return 0;
}

