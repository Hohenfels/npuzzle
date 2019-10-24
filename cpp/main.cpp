#include "npuzzle.h"

using namespace std;

int     main(int argc, char** argv)
{
    std::vector<int>    puzzle(9);
    Node *n;
    Coord c;
    puzzle = {1, 3, 6, 5, 2, 8, 7, 4, 0};

    // n = new Node(nullptr, puzzle, 4);
    // c = n->getSnailCoords(13);

    // cout << c.x << "-" << c.y << "\n";

    if (checkSolvability(puzzle, 3)) {
        solvePuzzle(0, 3, puzzle);
    }
    else {
        return 1;
    }
}