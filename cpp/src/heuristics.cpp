#include "heuristics.h"
#include "Node.h"

float   Heuristics::Manhattan(std::vector<int> state, size_t size)
{
    size_t  sum = 0;

    for (size_t i = 0; i < state.size(); i++)
        if (state[i] != 0)
            sum += ManhattanDistance({static_cast<int>(i % size), static_cast<int>(i / size)}, Node::getSnailCoords(state[i], size));

    return sum;
}

float   Heuristics::ManhattanDistance(const Coord & c1, const Coord & c2)
{
    return std::abs(c1.x - c2.x) + std::abs(c1.y - c2.y);
}

float   Heuristics::LinearConflict(std::vector<int> state, size_t size)
{
    float h = 0;

    //blabla

    return h + Manhattan(state, size);
}
