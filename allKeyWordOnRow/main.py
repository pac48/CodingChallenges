class Node:
    def __init__(self, isWord=False):
        self.letters = [None for i in range(26)]
        self.isWord = isWord


class Tri:
    def __init__(self):
        self.root = Node()

    def insert(self, word):
        node = self.root
        for letter in word:
            ind = ord(letter) - ord('a')
            if node.letters[ind] is None:
                node.letters[ind] = Node()
            node = node.letters[ind]
        node.isWord = True

    def find(self, word):
        node = self.root
        for letter in word:
            ind = ord(letter) - ord('a')
            if node.letters[ind] == None:
                return None
            node = node.letters[ind]
        return node


def recurse(subWord, words, row, tri):
    for letter in row:
        potentialWord = subWord + letter
        node = tri.find(potentialWord)
        if not node is None and node.isWord:
            words.append(potentialWord)
        if not node is None:  # did not find word, but there are more to explore
            recurse(potentialWord, words, row, tri)


def run():
    tri = Tri()
    with open("words_alpha.txt", "r") as f:
        word = "not null"
        while word:
            word = f.readline()
            tri.insert(word.strip("\n").lower())
    row1 = ['q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p']
    row2 = ['a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l']
    row3 = ['z', 'x', 'c', 'v', 'b', 'n', 'm']
    rows = [row1, row2, row3]
    for ind, row in enumerate(rows):
        words = []
        recurse("", words, row, tri)
        print(f"row {ind + 1} has the following words:")
        print(words)


if __name__ == "__main__":
    run()
