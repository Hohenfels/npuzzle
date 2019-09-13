import numpy as np

class Node():
    def __init__(self, hFunc, puzzle, parent = None, size = None):
        self.puzzle = puzzle
        self.parent = parent
        self.g = 1 if not parent else parent.g + 1
        self.size = size if size else parent.size
        self.hFunc = hFunc
        self.isSolved = False

    def __str__(self):
        return str(self.puzzle)

    def __repr__(self):
        return self.__str__()

    @property
    def hash(self):
        return hash(str(self.puzzle))

    @property
    def score(self):
        return self.g + self.h

    @property
    def solved(self):
        return self.isSolved

    @property
    def h(self):
        s = 0
        for col in range(self.size):
            for row in range(self.size):
                if self.puzzle[col][row] != 0:
                    # coords = self.getSnailCoords(self.size, self.puzzle[row][col])
                    self.getSnailCoords(self.size, self.puzzle[row][col])
                    s += self.hFunc((col, row), self.getSnailCoords(self.size, self.puzzle[row][col]))
        if s == 0:
            self.isSolved = True
        return sum

    def getEmptyCoords(self):
        c = np.where(self.puzzle == 0)
        return c[1][0], c[0][0]                    

    @staticmethod
    def getSnailCoords(size, value):
        r = 0
        span = size
        while value > span:
            value -= span
            r += 1
            span -= r % 2
        d, m = divmod(r, 4)
        c = size - 1 - d
        return [d + value - 1, c, c - value, d][m], [d, d + value, c, c - value][m]
