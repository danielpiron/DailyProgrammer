#include <stdio.h>
#include <string.h>

int garland(char *word) {
    int word_len = strlen(word);
    int right = word_len / 2;
    int left = 0;

    int degree = word_len - right;
    while(right < word_len) {
       if (word[left] == word[right]) {
           ++left;
           ++right;
       }
       else {
           --degree;
       }
    }
    return degree;
}
