from Classes.ErrorClasses.Errors import NumberError, \
                                        PuzzleSizeError, \
                                        NumberRangeError, \
                                        LineSizeError, \
                                        OccurenceError


class Parser:
    puzzle = []

    def __init__(self, fpath):
        self.fpath = fpath
        with open(self.fpath, 'r') as f:
            self.puzzle = f.read().split('\n')

    def checkIntegrity(self):
        self.removeComments(self)
        if self.checkNbValidity(self) and self.puzzleValidity(self):
            # self.formatPuzzle()
            print("OK")

    @staticmethod
    def removeComments(self):
        for i, line in enumerate(self.puzzle):
            self.puzzle[i] = line.split('#')[0]
        self.puzzle = list(filter(None, self.puzzle))

    @staticmethod
    def checkNbValidity(self):
        for i, line in enumerate(self.puzzle):
            line = line.split(' ')
            if len(line) == 1:
                if int(line[0]) < 0:
                    raise(PuzzleSizeError())
            for nb in line:
                if nb:
                    if int(nb) < 0:
                        raise(NumberError(i, nb))
        return 1

    @staticmethod
    def puzzleValidity(self):
        size = int(self.puzzle[0])
        for i, line in enumerate(self.puzzle[1:]):
            line = line.split(' ')
            if '' not in line:
                if len(line) > size:
                    raise(LineSizeError(i, line, size))
                for nb in line:
                    if nb:
                        if int(nb) >= size * size:
                            raise(NumberRangeError(i, nb, size))
                    occur = sum(line.count(nb) for line in self.puzzle)
                    if occur > 2:
                        raise(OccurenceError(nb, occur))
