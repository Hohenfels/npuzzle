#include "npuzzle.h"

enum directions
{
    RIGHT,
    DOWN,
    LEFT,
    UP,
};


std::vector<int> createOneDim(std::vector<int> &puzzle, int &size)
{
    int i = 0, y = 0;
    int span = size;
    int count = 0;
    std::vector<int> newArray;
    directions direction = RIGHT; 

    while (count != (size * size))
    {
        if (direction == RIGHT)
        {
            while (i < span)
            {
                newArray.push_back(puzzle[y * size + i]);
                i++;
                count++;
            }
            y++;
            i--;
        }
        else if (direction == DOWN)
        {
            while (y < span)
            {
                newArray.push_back(puzzle[y * size + i]);
                y++;
                count++;
            }
            y--;
            i--;
        }
        else if (direction == LEFT)
        {
            while (i >= size - span )
            {
                newArray.push_back(puzzle[y * size + i]);
                i--;
                count++;
            }
            i++;
            y--;
        }
        else if (direction == UP)
        {
            span--;
            while (y >= size - span)
            {
                newArray.push_back(puzzle[y * size + i]);
                y--;
                count++;
            }
            y++;
            i++;
        }
        direction = static_cast<directions>((direction + 1) % 4);
    }
    return newArray;
}

int findCoord(std::vector<int> puzzle, int value) {
    auto idx = std::find(puzzle.begin(), puzzle.end(), value) - puzzle.begin();
    return idx;
}

int getNbPermut(std::vector<int> puzzle) {
    int count = 0;
    for (size_t i = 0; i < puzzle.size(); i++) {
        for (size_t j = i + 1; j < puzzle.size(); j++) {
            if ((puzzle[i] != 0 && puzzle[j] != 0) && (puzzle[i] > puzzle[j]))
                count++;
        }
    }
    return count;
}

bool checkSolvability(std::vector<int> puzzle, int size) {
    std::vector<int> newArray = createOneDim(puzzle, size);
    int nbPermut = getNbPermut(newArray);
    int idxEmpty = findCoord(newArray, 0);
    if (size % 2 != 0)
    {   
        if (nbPermut % 2 == 0) {
            return true;
        }
    }
    else
    {
        if ((nbPermut % 2 == 0 && idxEmpty % 2) || (nbPermut % 2 && idxEmpty % 2 == 0)) {
            return true;
        }
    }
    std::cout << "not solvable, exit\n";
    return false;
}