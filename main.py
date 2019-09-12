from classes.Parser import Parser
import argparse

def getFpath():
    parser = argparse.ArgumentParser()
    parser.add_argument("fpath",
                         type=str,
                         help="File path of N-puzzle")
    args = parser.parse_args()
    return args.fpath

if __name__ == "__main__":
    parse = Parser(getFpath())
    parse.checkIntegrity()