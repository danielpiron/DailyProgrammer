#include <limits.h>
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

/**
 * Print all kaprekar numbers within the given range
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
	int start, end;
	char line[LINE_MAX];
	while (fgets(line, LINE_MAX, stdin) != NULL) {
		sscanf(line, "%d %d", &start, &end);
		kaprekar_range(start, end, 10);
	}
	return 0;
}

