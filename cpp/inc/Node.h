#ifndef __NODE_H__
#define __NODE_H__

#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>

#include "solver.h"

//typedef unsigned int (*heuristic)(const Coord &, const Coord &);

class Node 
{

private:
    Node() = delete;
    std::vector<int>    _state;
    Node                *_parent;
    size_t              _size;
    size_t              _score;
    unsigned int        (*_heuristic)(const Coord &, const Coord &);

    size_t              _g;
    size_t              getHeuristicSum();
    Coord const         getSnailCoords(size_t val);

public:
    Node(unsigned int (*hFunc)(const Coord &, const Coord &), std::vector<int> state, size_t size);
    Node(Node &src);

    virtual ~Node();

    bool                isSolved;

    inline std::vector<int>&    getState() { return this->_state; }
    inline size_t               getScore() const { return this->_score; }
    inline size_t               getSize() const { return this->_size; }
    inline size_t               getG() const { return this->_g; }
    inline Node                 *getParent() const { return this->_parent; }

    Coord const     getEmptyCoord();
    size_t          processScore();
    size_t          getHash() const;
    
    const Node&         operator=(Node const & rhs);

};

std::ostream&       operator<<(std::ostream& o, Node& n);   

#endif