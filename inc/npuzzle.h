#ifndef __NPUZZLE__H__
#define __NPUZZLE__H__

#include "solver.h"
#include "Node.h"
#include "heuristics.h"
#include "parser.h"
#include <string.h>
#include <iostream>

struct CLOpt
{
    char    *filename;
    int     heuristicIdx;
    bool    greedy = false;
    bool    uniform = false;
    bool    visu = false;
};

bool checkSolvability(std::vector<int> puzzle, int size);

#endif