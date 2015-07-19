"""
Description
Today we're going to balance words on one of the letters in them. We'll use
the position and letter itself to calculate the weight around the balance
point. A word can be balanced if the weight on either side of the balance
point is equal. Not all words can be balanced, but those that can are
interesting for this challenge.

The formula to calculate the weight of the word is to look at the letter
position in the English alphabet (so A=1, B=2, C=3 ... Z=26) as the letter
weight, then multiply that by the distance from the balance point, so the
first letter away is multiplied by 1, the second away by 2, etc.

As an example: STEAD balances at T: 1 * S(19) = 1 * E(5) + 2 * A(1) + 3 *
D(4))
"""

import sys

# This solution is predicated on the fact that multiplication is a form of
# recursive addition. Instead of calculating weights for each character at
# every attempt, I use shift amounts, which are initialized to the sum of
# the values to the left and right of the pivot. These shift amounts have
# the effect of adjusting how much each letter if factored relative to the
# location of the trial pivot.
def balance(word):
    ''' Attempt to balance a word. Returns a tuple with the index of the
    pivot and the balanced weight.
    Example: (1, 19) for the input STEAD
    NOTE: O(N) algorithm complexity
    '''
    # Map 'capitalized' letters to their values in the alphabet
    values = [ord(c) - ord('A') + 1 for c in word.upper()]
    # Values multiplied by their distance from the center.
    factored = [v * abs(n - 1) for n, v in enumerate(values)]
    # Start pivot at second character
    l_weight = sum(factored[:1])  # Take the first character
    r_weight = sum(factored[2:])  # Skip 'pivot' and take rest
    # Amounts to shift weight onto the left and right respectively
    l_shift = sum(values[:1])
    r_shift = sum(values[1:])
    # Check for balance from second character thru second to last character.
    for pivot in range(1, len(word) - 1):
        if l_weight == r_weight:
            return (pivot, l_weight)  # I had to pick one
        else:
            # Shift amounts are adjusted as the pivot is moved
            l_shift += values[pivot]
            r_shift -= values[pivot]
            l_weight += l_shift
            r_weight -= r_shift
    # Exiting the loop indicates value to find balance.
    return (None, None)


def main(argv):
    if len(sys.argv) < 1:
        print 'Please supply a word to balance.'
        print 'python balance.py WRONGHEADED'

    word = argv[0]
    if len(word) < 3:
        print 'The word entered should be at least 3 characters long.'

    p, w = balance(word)
    if p is None and w is None:
        print '%s DOES NOT BALANCE' % word
        sys.exit(1)

    print '%s %s %s - %i' % (word[:p], word[p], word[p+1:], w)

if __name__ == '__main__':
    main(sys.argv[1:])
