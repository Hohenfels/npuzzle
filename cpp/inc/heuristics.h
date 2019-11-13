#pragma once

#include "solver.h"

#include <cmath>

namespace Heuristics
{
    float   Manhattan(const Coord &, const Coord &);
    float   OutOfPlace(const Coord &, const Coord &);
}