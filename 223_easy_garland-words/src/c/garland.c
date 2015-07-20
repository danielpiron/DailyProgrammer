#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int garland(char *word) {
    int left = 0;
    int right = 1;

    int degree = 0;
    size_t len = strlen(word);
    while (right < len) {
       if (word[left] == word[right]) {
           ++left;
           ++degree;
       }
       else {
           degree = 0;
           left = 0;
       }
       ++right;
    }
    return degree;
}

int main(int argc, char* argv[]) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, stdin)) != -1) {
        if (line[read - 2] == '\r') {
            /* Handle possible windows format */
            line[read - 2] = '\0';
        }
        else {
            /* Chop off delimiter */
            line[read - 1] = '\0';
        }
        int d = garland(line);
        printf("garland(\"%s\") -> %d\n", line, d);
    }
    free(line);
    exit(EXIT_SUCCESS);
}
