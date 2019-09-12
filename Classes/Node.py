class Node():
    def __init__(self, h, puzzle, parent = None, g = None, size = None):
        self.puzzle = puzzle
        self.parent = parent
        self.g = parent.g + 1 if g else 1
        self.size = size if size else parent.size
        self.hFunc = h

    @property
    def score(self):
        return self.g + self.h

    @property
    def solved(self):
        return self.h == 0

    @property
    def h(self):
        s = 0
        for row in range(self.size):
            for col in range(self.size):
                s += self.hFunc(self.puzzle[row * self.size + col])
