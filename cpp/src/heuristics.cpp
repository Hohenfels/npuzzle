#include "heuristics.h"

float   Heuristics::Manhattan(const Coord & c1, const Coord & c2)
{
    return std::abs(c1.x - c2.x) + std::abs(c1.y - c2.y);
}

float   Heuristics::OutOfPlace(const Coord & c1, const Coord & c2)
{
    return !(c1.x == c2.x && c1.y == c2.y);
}
