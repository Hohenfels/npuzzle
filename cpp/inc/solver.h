#ifndef __SOLVER_H__
#define __SOLVER_H__

#include <queue>
#include <memory>
#include "unistd.h"

class Node;

void                solvePuzzle(int hFuncIdx, size_t size, std::vector<int> grid);
std::vector<Node>   createChildren(Node parent, std::vector<Node const *>& seen);

struct Coord
{
    int x;
    int y;
};

#endif