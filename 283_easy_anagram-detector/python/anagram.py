import os.path
import re

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


def get_input_file(input_id):
    return open(os.path.join(INPUT_DIR, input_id + '.txt'))


if __name__ == '__main__':
    for line in get_input_file('1'):
        word1, word2 = parse_words(line)
        output = line.strip()
        if is_anagram(word1, word2):
            output = output.replace('?', 'is an anagram of')
        else:
            output = output.replace('?', 'is NOT an anagram of')
        print(output)
