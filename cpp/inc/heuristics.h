#ifndef __HEURISTIC_H__
#define __HEURISTIC_H__

#include "solver.h"
#include <cmath>

struct Coord;

namespace Heuristics
{
    float   Manhattan(std::vector<int> state, size_t size);
    float   ManhattanDistance(const Coord & c1, const Coord & c2);
    float   LinearConflict(std::vector<int> state, size_t size);
    float   Gaschnig(std::vector<int> state, size_t size);
    float   Yolo(std::vector<int> state, size_t size);
}

#endif