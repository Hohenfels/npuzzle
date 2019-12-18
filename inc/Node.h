#ifndef __NODE_H__
#define __NODE_H__

#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <math.h>

#include "solver.h"

struct Coord;

class Node 
{

private:
    Node() = delete;
    size_t              _size;
    float               (*_heuristic)(std::vector<int> state, size_t size);
    Node                *_parent;
    std::vector<int>    _state;
    float               _score;
    size_t              _g;

public:
    Node(float (*hFunc)(std::vector<int> state, size_t size), std::vector<int> state, size_t size);
    Node(Node & src);

    virtual ~Node();
    static Coord const          getSnailCoords(int val, size_t size);

    bool                isSolved;

    inline std::vector<int>&    getState() { return this->_state; }
    inline size_t               getScore() const { return this->_score; }
    inline size_t               getSize() const { return this->_size; }
    inline size_t               getG() const { return this->_g; }
    inline Node                 *getParent() const { return this->_parent; }

    size_t                      getHeuristic();
    Coord const                 getEmptyCoord();
    void                        processScore(bool greedy, bool uniform);
    size_t                      getHash() const;
    
    const Node&         operator=(Node const & rhs);

};

std::ostream&       operator<<(std::ostream& o, Node& n);   

typedef struct
{
    int  array[4];
} snailRet;

#endif