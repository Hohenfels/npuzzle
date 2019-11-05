#include "npuzzle.h"

using namespace std;

int     main(int argc, char** argv)
{
    std::pair<std::vector<int>, size_t> puzzle;

    puzzle = Parser::parseFile(argv[1]);

    if (checkSolvability(puzzle.first, puzzle.second))
        solvePuzzle(0, 3, puzzle.first);
    else
        return 1;
    return 0;
}