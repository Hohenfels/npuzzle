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

std::vector<int>    createTarget(int size) 
{ 
    int val = 1; 
    int m = size, n = size;
    std::vector<int>    ret(size * size);
    int k = 0, l = 0; 

    while (k < m && l < n) 
    {
        for (int i = l; i < n; ++i) 
            ret[k * size + i] = val++; 
  
        k++; 
        for (int i = k; i < m; ++i) 
            ret[i * size + n-1] = val++; 
        n--; 
        if (k < m) 
        { 
            for (int i = n-1; i >= l; --i) 
                ret[(m-1) * size + i] = val++; 
            m--; 
        } 
        if (l < n) 
        { 
            for (int i = m-1; i >= k; --i) 
                 ret[i * size + l] = val++; 
            l++; 
        } 
    }
    ret[(size / 2 - !(size % 2)) + (size / 2) * size] = 0;
    return ret;
}

float   Heuristics::Gaschnig(std::vector<int> state, size_t size)
{
    int emptyIndex;
    size_t count = 0;
    static std::vector<int> goal = createTarget(size);
    
    while (state != goal)
    {

        emptyIndex = std::distance(state.begin(), std::find(state.begin(), state.end(), 0));
        if (goal[emptyIndex] != 0)
        {
            int goalValue = goal[emptyIndex];
            int stateIndex = std::distance(state.begin(), std::find(state.begin(), state.end(), goalValue));
            std::swap(state[stateIndex], state[emptyIndex]);
        }
        else
        {
            for (size_t i = 0; i < state.size(); i++)
            {
                if (goal[i] != state[i])
                {
                    std::swap(state[i], state[emptyIndex]);
                    break;
                }
            }
        }
        count++;
    }
    return count;
}

float Heuristics::Yolo(std::vector<int> state, size_t size)
{
    return Heuristics::Gaschnig(state, size) + Heuristics::LinearConflict(state, size);
}

