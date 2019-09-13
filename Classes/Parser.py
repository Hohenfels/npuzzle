from Classes.ErrorsModule.Errors import *


class Parser:
    puzzle = []
    size = None

    def __init__(self, fpath):
        self.fpath = fpath
        with open(self.fpath, 'r') as f:
            self.puzzle = f.read().split('\n')

    def checkIntegrity(self):
        self.removeComments(self)
        self.checkNbValidity(self)
        self.puzzleValidity(self)

    @staticmethod
    def removeComments(self):
        for i, line in enumerate(self.puzzle):
            self.puzzle[i] = line.split('#')[0].strip(' ')
        self.puzzle = list(filter(None, self.puzzle))

    @staticmethod
    def checkNbValidity(self):
        for i, line in enumerate(self.puzzle):
            line = line.split(' ')
            if len(line) == 1:
                if int(line[0]) < 0:
                    raise(PuzzleSizeError())
            for nb in line:
                if int(nb) != 0:
                    if int(nb) < 0:
                        raise(NumberError(i, nb))

    @staticmethod
    def puzzleValidity(self):
        self.size = int(self.puzzle[0])
        for i, line in enumerate(self.puzzle[1:]):
            line = line.split(' ')
            if '' not in line:
                if len(line) > self.size:
                    raise(LineSizeError(i, line, self.size))
                for nb in line:
                    if int(nb) != 0:
                        if int(nb) >= self.size * self.size:
                            raise(NumberRangeError(i, nb, self.size))
                    occur = sum(line.count(nb) for line in self.puzzle[1:])
                    if occur > 2:
                        raise(OccurenceError(nb, occur))

    @property
    def getPuzzle(self):
        return self.puzzle, self.size
