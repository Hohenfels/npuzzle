import numpy as np


class Node:
    def __init__(self, hFunc, state, parent=None, size=None):
        self.state = state
        self.parent = parent
        self.g = 1 if not parent else parent.g + 1
        self.size = size if size else parent.size
        self.hFunc = hFunc
        self.isSolved = False

    def __str__(self):
        return str(self.state)

    def __repr__(self):
        return self.__str__()

    @property
    def hash(self):
        return hash(str(self.state))

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
                if self.state[col][row] != 0:
                    s += self.hFunc((row, col), self.getSnailCoords(self.size, self.state[row][col]))
        if s == 0:
            self.isSolved = True
        return s

    def getEmptyCoords(self):
        c = np.where(self.state == 0)
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
        return [d, d + value, c, c - value][m], [d + value - 1, c, c - value, d][m]

    def __lt__(self, other):
        return self.score

    def __eq__(self, other):
        return self.score
