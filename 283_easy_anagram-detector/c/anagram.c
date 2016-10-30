#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COUNT_TABLE_SIZE ((int)'z' - (int)'a' + 1)
#define QUOTE '"'
#define QUESTION '?'

/**
 * Count occurences of alphabetic characters in a string
 **/
void count_occurences(int count_table[], const char *string)
{
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
bool is_anagram(const char *word1, const char *word2)
{
	int ctable1[COUNT_TABLE_SIZE];
	int ctable2[COUNT_TABLE_SIZE];

	count_occurences(ctable1, word1);
	count_occurences(ctable2, word2);

	return memcmp(ctable1, ctable2, COUNT_TABLE_SIZE * sizeof(ctable1[0])) == 0;
}


char *next_quoted(char *s)
{
	char *start, *end;
	start = strchr(s, QUOTE) + 1;
	end = strchr(start, QUOTE);
	*end = '\0';
	return start;
}

/**
 * Parse words from a line of input that looks like this:
 * "Word1" ? "Word2"
 **/
bool parse_words(char **word1, char **word2, char *line)
{
	char *q_ptr = strchr(line, QUESTION);

	if (q_ptr == NULL) {
		return 0;
	}

	*word1 = next_quoted(line);
	*word2 = next_quoted(q_ptr + 1);

	return 1;
}

int main(int argc, char *argv[])
{
	FILE *fp;
	char *fmt;
	char *line = NULL;
	char *word1, *word2;
	size_t len = 0;

	if (argc > 1) {
		fp = fopen(argv[1], "r");
		if (fp == NULL) {
			printf("Couldn't open input\n");
			exit(EXIT_FAILURE);
		}
	}
	else {
		fp = stdin;
	}
	
	while (getline(&line, &len, fp) != -1) {
		if (parse_words(&word1, &word2, line)) {
			if (is_anagram(word1, word2))
				fmt = "\"%s\" is an anagram of \"%s\"\n";
			else
				fmt = "\"%s\" is NOT an anagram of \"%s\"\n";
			printf(fmt, word1, word2);
		}
	}
	free(line);
}
