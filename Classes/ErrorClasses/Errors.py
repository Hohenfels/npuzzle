class NumberError(Exception):
    def __init__(self, i, nb):
        print("Value Error at line {}: {} is under zero\n"
              "in formatted file without comments".format(i, nb))
        exit()


class PuzzleSizeError(Exception):
    def __init__(self):
        print("Size Error: Puzzle must be of a size >= 2")
        exit()


class NumberRangeError(Exception):
    def __init__(self, i, nb, size):
        print("Number range error at line {}: Number {} must be of range <= {}".format(i, nb, size))
        quit()


class LineSizeError(Exception):
    def __init__(self, i, line, size):
        print("Error at line {}: Size of line {} > {}".format(i, line, size))
        quit()

class OccurenceError(Exception):
    def __init__(self, nb, occurence):
        print("Occurence error: {} appears {} times instead of one".format(nb, occurence))
        exit()