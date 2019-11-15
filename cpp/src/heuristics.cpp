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
    float conflicts = 0;
   
    for (int y = 0; y < static_cast<int>(size); y++) {
        std::vector<int> row(state.begin() + y * size, state.begin() + y * size + size);
        for (size_t i = 0; i < size - 1; i++) {
            for (size_t j = i + 1; j < size; j++) {
                if (row[i] && row[j]) {
                    Coord ti = Node::getSnailCoords(row[i], size);
                    Coord tj = Node::getSnailCoords(row[j], size);

                    if (ti.y == y && tj.y == y && tj.x < ti.x)
                        conflicts++;
                }
            }
        }
    }

    for (int x = 0; x < static_cast<int>(size); x++)
    {
        for (size_t i = 0; i < state.size() - 1; i += size) {
            for (size_t j = i + size; j < state.size(); j += size) {
                if (state[i + x] && state[j + x])
                {
                    Coord ti = Node::getSnailCoords(state[i + x], size);
                    Coord tj = Node::getSnailCoords(state[j + x], size);

                    if (ti.x == x && tj.x == x && tj.y < ti.y)
                        conflicts++;
                }
            }
        }
    }

    return 2 * conflicts + Manhattan(state, size);
}


float   Heuristics::Gaschnig(std::vector<int> state, size_t size)
{
    Coord egc = {static_cast<int>(size / 2 - !(size % 2)), static_cast<int>(size / 2)};
    size_t count = 0;
    
    for (size_t i = 0; i < state.size(); i++)
    {
        if (state[i] == 0 && Coord({static_cast<int>(i % size), static_cast<int>(i / size)}) == egc)
        {
            
        }
        else
        count++;
    }
    std::cout << count << std::endl;
    return 0;
}