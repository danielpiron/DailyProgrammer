#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define COUNT_TABLE_SIZE ((int)'z' - (int)'a' + 1)

/**
 * Count occurences of alphabetic characters in a string
 **/
void count_occurences(int count_table[], const char *string) {
	int i;
	char c;
	const char *p;
	memset(count_table, 0, sizeof(count_table[0]) * COUNT_TABLE_SIZE);
	for (p = string; *p; p++) {
		c = *p;
		if (isalpha(c)) 
			count_table[tolower(c) - (int)'a']++;
	}
}

/**
 * Returns 1 if the given words are anagrams.
 **/
bool is_anagram(const char *word1, const char *word2) {
	int ctable1[COUNT_TABLE_SIZE];
	int ctable2[COUNT_TABLE_SIZE];

	count_occurences(ctable1, word1);
	count_occurences(ctable2, word2);

	return memcmp(ctable1, ctable2, COUNT_TABLE_SIZE * sizeof(ctable1[0])) == 0;
}

int main(int argc, char *argv[]) {
	printf("wisdom & mid sow - %d\n", is_anagram("wisdom", "mid sow"));
	printf("Reddit & Eat Dirt - %d\n", is_anagram("Reddit", "Eat Dirt"));
}
