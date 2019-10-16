#include "solver.h"
#include "Node.h"
#include "heuristics.h"

#include <iostream>
using namespace std;

int     main(int argc, char** argv)
{
    std::vector<int>    puzzle(9);
    Node *n;
    Coord c;
    puzzle = {0, 2, 7, 6, 8, 4, 3, 1, 5};

    // n = new Node(nullptr, puzzle, 4);
    // c = n->getSnailCoords(13);

    // cout << c.x << " " << c.y << "\n";

    solvePuzzle(0, 3, puzzle);
}