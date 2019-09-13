from Classes.Parser import Parser
import researchTree
import argparse


def getArgs():
    parser = argparse.ArgumentParser()
    parser.add_argument("fpath", type = str, help = "File path of N-puzzle")
    parser.add_argument("heuristic", type = int, default = 1, help = "1 - Manhattan\n2 - Pouet")
    args = parser.parse_args()
    return args


if __name__ == "__main__":
    args = getArgs()
    parse = Parser(args.fpath)
    parse.checkIntegrity()
    puzzle, size = parse.getPuzzle()
    researchTree.solvePuzzle(puzzle, size, args.heuristic)