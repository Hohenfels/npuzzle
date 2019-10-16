#ifndef __SOLVER_H__
#define __SOLVER_H__

#include <queue>
#include <memory>
#include <functional>
#include "unistd.h"

class Node;

Node                    *solvePuzzle(int hFuncIdx, size_t size, std::vector<int> grid);
std::vector<Node*>      createChildren(Node *parent, std::vector<size_t>& seen);
void                    printPath(Node *node);

struct Coord
{
    int x;
    int y;
};

#endif