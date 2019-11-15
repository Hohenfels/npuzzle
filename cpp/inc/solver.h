#ifndef __SOLVER_H__
#define __SOLVER_H__

#include <queue>
#include <memory>
#include <functional>
#include <map>
#include <fstream>
#include <unistd.h>
#include <chrono>
#include <iomanip>
#include "Node.h"
#include "heuristics.h"

class Node;

void                    solvePuzzle(int hFuncIdx, size_t size, std::vector<int> grid, bool greedy, bool uniform);
std::vector<Node*>      createChildren(Node *parent, std::map<size_t, Node*>& seen);
void                    printPath(Node *node, size_t timeComplexity, size_t spaceComplexity);
void                    printTime(std::chrono::microseconds::rep diff);
void                    deleteNodes(std::map<size_t, Node*>& seen);

struct Coord
{
    int x;
    int y;
};

bool                    operator==(const Coord &lhs, const Coord &rhs) { return (lhs.x == rhs.x && lhs.y == rhs.y); }

#endif