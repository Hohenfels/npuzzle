class ValueUnderZero(Exception):
    def __init__(self, i, nb):
        print("Value Error at line {}: {} is under zero\n"
              "in formatted file without comments".format(i, nb))
        exit()


class WrongPuzzleSize(Exception):
    def __init__(self):
        print("Size Error: Puzzle must be of a size >= 2")
        exit()


class Parser():
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
        print(self.puzzle)

    @staticmethod
    def checkNbValidity(self):
        for i, line in enumerate(self.puzzle):
            line = line.split(' ')
            if len(line) == 1:
                if int(line[0]) < 0:
                    raise(WrongPuzzleSize())
            for nb in line:
                if nb:
                    if int(nb) < 0:
                        raise(ValueUnderZero(i, nb))
        return 1

    @staticmethod
    def puzzleValidity(self):
        size = int(self.puzzle[0])
        for i, line in enumerate(self.puzzle[1:]):
            line = line.split(' ')
            if len(line) > size:
                print("NOT OK") #TODO faire Exception
            for nb in line:
                if nb:
                    if int(nb) > size:
                        print("NOT OK") #TODO aire Exception







