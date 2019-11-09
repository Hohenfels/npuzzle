#include "npuzzle.h"

/*

[[7 3 1]
 [2 0 6]
 [8 4 5]]

7 3 1 2 0 6 8 4 5
*/

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

    std::cout << "SIZE - 1 = : " << size - 1 << '\n';

    while (count != (size * size))
    {
        if (direction == RIGHT)
        {
            std::cout << "\nRIGHT\n";
            while (i < span)
            {
                // newArray.push_back(puzzle[y * size + i]);
                std::cout << puzzle[y * size + i] << "\ni = " << i << " y = " << y << '\n';
                i++;
                count++;
            }
            y++;
            i--;
        }
        else if (direction == DOWN)
        {
            std::cout << "\nDOWN " << i <<"\n";
            while (y < span)
            {
                // newArray.push_back(puzzle[y * size + i]);
                std::cout << puzzle[y * size + i] << "\ni = " << i << " y = " << y << '\n'; // y = 6 + 3
                y++;
                count++;
            }
            y--;
            i--;
        }
        else if (direction == LEFT)
        {
            std::cout << "\nLEFT\n";
            while (i >= 0 )
            {
                std::cout << puzzle[y * size + i % size] << "\ni = " << i << " y = " << y << '\n';
                // newArray.push_back(puzzle[y * size + i]);
                i--;
                count++;
            }
            i++;
            y--;
        }
        else if (direction == UP)
        {
            std::cout << "\nUP\n";
            while (y >= 0)
            {
                std::cout << puzzle[y * size + i % size] << "\ni = " << i << " y = " << y << '\n';
                // newArray.push_back(puzzle[y * size + i]);
                y--;
                count++;
            }
            y++;
            i++;
            exit(-1);
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
    for (int i = 0; i < puzzle.size(); i++) {
        for (int j = i + 1; j < puzzle.size(); j++) {
            if ((puzzle[i] != 0 && puzzle[j] != 0) && (puzzle[i] > puzzle[j]))
                count++;
        }
    }
    return count;
}

bool checkSolvability(std::vector<int> puzzle, int size) {
    std::vector<int> newArray = createOneDim(puzzle, size);
    int nbPermut = getNbPermut(puzzle);
    std::cout << '\n';
    std::cout << "size: " << size << "\n";
    std::cout << "permut: " << nbPermut << "\n";
    int idxEmpty = findCoord(puzzle, 0);
    if (size % 2 != 0)
    {   
        std::cout << "Is impair\n";
        if (nbPermut % 2 == 0) {
            std::cout << "Puzzle OK\n";
            return true;
        }
    }
    else
    {
        std::cout << "IS PAIR\n";
        if ((nbPermut % 2 == 0 && idxEmpty % 2) || (nbPermut % 2 && idxEmpty % 2 == 0)) {
            std::cout << "Puzzle OK\n";
            return true;
        }
    }
    std::cout << "not solvable, exit\n";
    return false;
}