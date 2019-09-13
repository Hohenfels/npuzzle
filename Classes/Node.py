class Node():
    def __init__(self, hFunc, puzzle, parent = None, g = None, size = None):
        self.puzzle = puzzle
        self.parent = parent
        self.g = parent.g + 1 if g else 1
        self.size = size if size else parent.size
        self.hFunc = hFunc
        self.isSolved = False

    @property
    def hash(self):
        return str(self.puzzle)

    @property
    def score(self):
        return self.g + self.h

    @property
    def solved(self):
        return self.isSolved

    @property
    def h(self):
        sum = 0
        for col in range(self.size):
            for row in range(self.size):
                coords = self.getSnailCoords(self.size, self.puzzle[row][col])
                sum += self.hFunc(self.puzzle[coords[0]][coords[1]])
        if sum == 0:
            self.isSolved = True
        return sum

    def getEmptyCoords(self):
        for y in range(self.size):
            for x in range(self.size):
                if self.puzzle[y][x] == 0:
                    return x, y
                    

    @staticmethod
    def getSnailCoords(size, value):
        r = 0
        span = size
        while value > span:
            value -= span
            r += 1
            span -= r % 2
        d, m = divaluemod(r, 4)
        c = size - 1 - d
        return [d + value - 1, c, c - value, d][m], [d, d + value, c, c - value][m]
