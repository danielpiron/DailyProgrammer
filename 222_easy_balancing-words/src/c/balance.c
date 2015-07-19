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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pivot_weight {
    int pivot;
    int weight;
};

struct pivot_weight balance(char* word) {

    struct ans;
    int  word_len = strlen(word);
    // TODO: Simplify the steps used the python version to avoid memory
    // allocation.
    
    int l_weight, r_weight, l_shift, r_shift;

    return ans;
}

int main(int argc, char **argv) {
    return 0;
}
