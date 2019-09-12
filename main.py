from Classes.Parser import Parser
import heuristics
import argparse


def getFpath():
    parser = argparse.ArgumentParser()
    parser.add_argument("fpath", type = str, help = "File path of N-puzzle")
    parser.add_argument("heuristic", type = int, default = 1, help = "1 - Manhattan\n2 - Pouet")
    args = parser.parse_args()
    return args.fpath


if __name__ == "__main__":
    parse = Parser(getFpath())
    parse.checkIntegrity()
    pzl = parse.getPuzzle()