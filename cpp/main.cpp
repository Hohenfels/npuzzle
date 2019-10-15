#include "solver.h"
#include "Node.h"

#include <iostream>
using namespace std;

int     main(int argc, char** argv)
{
    std::vector<int>    puzzle(9);
    std::vector<const Node *>  z;
    puzzle = {2, 4, 5, 3, 0, 7, 6, 1, 8};

    Node n(nullptr, puzzle, 3);

    std::vector<Node> children = createChildren(n, z);

    cout << n << "\n\n";

    for (auto c : children)
        cout << c << "\n\n";

    //solvePuzzle(0, 3, puzzle);
}