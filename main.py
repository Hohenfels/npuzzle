import argparse
import math
import numpy as np
from modules.Parser import Parser
from solvePuzzle import solvePuzzle


def getArgs():
    parser = argparse.ArgumentParser()
    parser.add_argument("fpath", type=str, help="File path of N-puzzle")
    parser.add_argument("heuristic", type=int, default=1, choices=[1, 2, 3, 4], help="1 - Manhattan\n"
                                                                                     "2 - Euclidian\n"
                                                                                     "3 - Diagonal")
    args = parser.parse_args()
    return args


def createTarget(size):
    x = int(math.ceil(size / 2))
    target = [[0 for i in range(size)] for j in range(size)]
    s = 0
    for l in range(x):
        k = 0
        n = size - 2 * l
        p = 2 * n + 2 * (n - 2)
        h = (n - 1) * 3 + 1
        for j in range(l, n + l):
            target[l][j] = k + 1 + s
            target[size - l - 1][j] = h + s
            if (h + s) == (size * size) and j == l:
                target[size - l - 1][j] = 0
            h -= 1
            k += 1
        k = 0
        for i in range(l + 1, size - l - 1):
            target[i][l] = p + s
            target[i][size - l - 1] = n + k + 1 + s
            p -= 1
            k += 1
        s += 2 * n + 2 * (n - 2)
    return np.array(target)

if __name__ == "__main__":
    args = getArgs()
    parser = Parser(args.fpath)
    grid, size = parser.getPuzzle()
    target = createTarget(size)
    solvePuzzle(grid, size, target, args.heuristic)
