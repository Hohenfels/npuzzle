#ifndef __SOLVER_H__
#define __SOLVER_H__

#include <queue>
#include <memory>
#include <functional>
#include <map>
#include "unistd.h"

class Node;

void                    solvePuzzle(int hFuncIdx, size_t size, std::vector<int> grid);
std::vector<Node*>      createChildren(Node *parent, std::map<size_t, Node*>& seen);
void                    printPath(Node *node, size_t timeComplexity, size_t spaceComplexity);
void                    deleteNodes(std::map<size_t, Node*>& seen);

struct Coord
{
    int x;
    int y;
};

#endif