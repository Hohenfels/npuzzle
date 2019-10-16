#include "solver.h"
#include "Node.h"
#include "heuristics.h"

#include <iostream>
using namespace std;

int     main(int argc, char** argv)
{
    std::vector<int>    puzzle(9);
    // std::vector<const Node *>  z;
    Node *n;
    puzzle = {0, 2, 7, 6, 8, 4, 3, 1, 5};

    n = solvePuzzle(0, 3, puzzle);
    
    printPath(n);
}