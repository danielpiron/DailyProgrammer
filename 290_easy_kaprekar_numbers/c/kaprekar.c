#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Returns 1 if 'number' is "Kaprekar Number" for the given 'base'
 */
int is_kaprekar(int number, int base)
{
	int a, b, n, squared;

	squared = number * number;
	n = base;

	do {
		a = squared / n;
		b = squared % n;
		if (b > 0 && a + b == number) {
			return 1;
		}
		n *= base;
	} while (a);

	return 0;
}

/**
 * Print all Kaprekar numbers within the given range
 **/
void kaprekar_range(int start, int end, int base)
{
	int i;
	for (i = start; i < end; ++i) {
		if (is_kaprekar(i, base)) {
			printf("%d ", i);
		}
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	int start, end, base;
	char line[LINE_MAX];

	if (argc > 1) {
		base = atoi(argv[1]);
	}
	else {
		base = 10;
	}

	while (fgets(line, LINE_MAX, stdin) != NULL) {
		sscanf(line, "%d %d", &start, &end);
		kaprekar_range(start, end, base);
	}
	return 0;
}
