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


def balance(word):
    '''Attempt to balance a word. Returns a tuple with the index of the
    pivot and the balanced weight.
    Example: (1, 19) for the input STEAD'''
    # Map 'capitalized' letters to their values in the alphabet
    values = [ord(c) - ord('A') + 1 for c in word.upper()]
    # Values multiplied by their distance from the center.
    factored = [v * abs(n - 1) for n, v in enumerate(values)]
    # Start pivot at second character
    left_side = sum(factored[:1])  # Take the first character
    right_side = sum(factored[2:])  # Skip 'pivot' and take rest
    # Amounts to shift to the left and right, respectively, on the first move
    leftward_shift = sum(values[:1])
    rightward_shift = sum(values[1:])
    # Attempt to find a balancing point
    for pivot in range(1, len(word) - 1):
        if left_side == right_side:
            return (pivot, left_side)  # I had to pick one
        else:
            leftward_shift += values[pivot]
            rightward_shift -= values[pivot]
            left_side += leftward_shift
            right_side -= rightward_shift
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
