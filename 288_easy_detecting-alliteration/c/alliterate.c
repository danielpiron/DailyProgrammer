#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define WHITESPACE " \t"

/**
 * Return true if the two words given alliterate. (i.e. Start with the
 * same letter, regardless of case)
 */

bool words_alliterate(const char *word1, const char *word2) {
	return tolower(*word1) == tolower(*word2);
}

int main(int argc, char *argv[])
{
	char *last_member = NULL;
	char *p;
	char text[] = "Peter Piper picked a peck of pickle peppers";

	p = strtok(text, WHITESPACE);
	while (p != NULL) {
		if (last_member == NULL) {
			last_member = p;
		}
		else if (words_alliterate(last_member, p)) {
			printf("%s\n", last_member);
			last_member = p;
		}
		p = strtok(NULL, WHITESPACE);
	}
	return 0;
}
