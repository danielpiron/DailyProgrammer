#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define WHITESPACE " \t"


int main(int argc, char *argv[])
{
	char *last_member;
	char *p;
	char text[] = "Peter Piper picked a peck of pickle peppers";

	p = strtok(text, WHITESPACE);
	while (p != NULL) {
		if (last_member == NULL) {
			last_member = p;
		}
		else if (tolower(last_member[0]) == tolower(p[0])) {
			printf("%s\n", last_member);
			last_member = p;
		}
		p = strtok(NULL, WHITESPACE);
	}
	return 0;
}
