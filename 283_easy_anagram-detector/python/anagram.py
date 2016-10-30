import os.path
import re
import sys

DIR = os.path.abspath(os.path.dirname(__file__))
INPUT_DIR = os.path.abspath(os.path.join(DIR, '..', 'inputs'))
CRE_PARSE_WORDS = re.compile(r'\s*\"([^"]+)\"\s*\?\s*\"([^"]+)\"')


def normalize(word):
    ''' Remove non-alpha characters and make all remaining characters lower '''
    return ''.join(char.lower() for char in word if char.isalpha())


def is_anagram(word1, word2):
    ''' Returns True if the two words given are anagrams '''
    word1 = normalize(word1)
    word2 = normalize(word2)
    return sorted(word1) == sorted(word2)


def parse_words(line):
    ''' Returns a 2-tuple of the words parsed from a line of input '''
    mo = CRE_PARSE_WORDS.match(line)
    if mo is None:
        return None
    return mo.group(1, 2)


if __name__ == '__main__':

    if len(sys.argv) > 1:
        fp = open(sys.argv[1], 'r')
    else:
        fp = sys.stdin

    for line in fp:
        word1, word2 = parse_words(line)
        output = line.strip()
        if is_anagram(word1, word2):
            output = output.replace('?', 'is an anagram of')
        else:
            output = output.replace('?', 'is NOT an anagram of')
        print(output)
    fp.close()
