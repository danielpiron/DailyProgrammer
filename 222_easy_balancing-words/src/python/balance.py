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
    '''Attempt to balance a word. Returns weight or -1, if no balance
    could be found.'''
    # Map 'capitalized' letters to their values in the alphabet
    values = [ ord(c) - ord('A') + 1 for c in word.upper() ]
    # Values multiplied by their distance from the center.
    factored = [ v * (n - 2) for n, v in enumerate(values) ]
    # Start pivot at second character
    weight_left = sum(factored[:1])
    weight_right = sum(factored[2:])
    # Map initial values of each letter into a list. Assume that the first
    # possible pivot is at the second character.
    initial_values = [ for v, c in enumerate(word)] 


def main(argv):
    if len(sys.argv) < 1:
        print 'Please supply a word to balance.'
        print 'python balance.py WRONGHEADED'

    word = argv[0]
    if len(word) < 3:
        print "The word entered should be at least 3 characters long."

    balance(word)

if __name__ == '__main__':
    main(sys.argv[1:])



