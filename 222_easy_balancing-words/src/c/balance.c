/**
* Description
* Today we're going to balance words on one of the letters in them. We'll use
* the position and letter itself to calculate the weight around the balance
* point. A word can be balanced if the weight on either side of the balance
* point is equal. Not all words can be balanced, but those that can are
* interesting for this challenge.
*
* The formula to calculate the weight of the word is to look at the letter
* position in the English alphabet (so A=1, B=2, C=3 ... Z=26) as the letter
* weight, then multiply that by the distance from the balance point, so the
* first letter away is multiplied by 1, the second away by 2, etc.
*
* As an example: STEAD balances at T: 1 * S(19) = 1 * E(5) + 2 * A(1) + 3 *
* D(4))
**/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pivot_weight {
    int pivot;
    int weight;
};

#define MAX_BUFFER 128

int sum(int* list, int size) {
    assert(size > 0);
    assert(list != NULL);
    int total = 0;
    while(size) {
        total += *list;
        list++;
        size--;
    }
    return total;
}

struct pivot_weight balance(char* word) {
    int values[MAX_BUFFER];
    int factors[MAX_BUFFER];
    int word_len = strlen(word);
    /* TODO: Check that word length is not more than buffer. */
    int pivot = 1;
    for (int i = 0; i < word_len; i++) {
        values[i] = (int)(word[i] - 'A');
        factors[i] = values[i] * abs(pivot - 1);
    }
    int l_weight, r_weight, l_shift, r_shift;
    /* TODO: Check for off-by-one errors here */
    l_weight = sum(factors, 1);
    r_weight = sum(&factors[2], word_len - 3);

    l_shift = sum(values, 1);
    r_shift = sum(&values[1], word_len - 1);

    struct pivot_weight ans = { 0, 0 };
    while(pivot < word_len - 1) {
        if (l_weight == r_weight) {
            ans.pivot = pivot;
            ans.weight = l_weight;
            break;
        }
        else {
            l_shift += values[pivot];
            r_shift -= values[pivot];
            l_weight += l_shift;
            r_weight -= r_shift;
        }
        ++pivot;
    }
    return ans;
}

int main(int argc, char **argv) {
    /* TODO: Capture user input. */
    return 0;
}
