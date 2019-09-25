from Classes.Parser import Parser
from isSolvable import isSovable
import researchTree
import argparse


def getArgs():
    parser = argparse.ArgumentParser()
    parser.add_argument("fpath", type = str, help = "File path of N-puzzle")
    parser.add_argument("heuristic", type = int, default = 1, choices = [1, 2, 3, 4], help = "1 - Manhattan\n2 - Pouet")
    args = parser.parse_args()
    return args


if __name__ == "__main__":
    args = getArgs()
    parse = Parser(args.fpath)
    parse.checkIntegrity()
    puzzle, size = parse.getPuzzle()
    # isSovable(puzzle, size)
    researchTree.solvePuzzle(puzzle, size, args.heuristic)