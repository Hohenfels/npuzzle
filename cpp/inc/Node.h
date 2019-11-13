#ifndef __NODE_H__
#define __NODE_H__

#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>

#include "solver.h"

class Node 
{

private:
    Node() = delete;
    size_t              _size;
    float               (*_heuristic)(const Coord &, const Coord &);
    Node                *_parent;
    std::vector<int>    _state;
    float               _score;
    size_t              _g;
    size_t              getHeuristicSum();

public:
    Node(float (*hFunc)(const Coord &, const Coord &), std::vector<int> state, size_t size);
    Node(Node & src);

    virtual ~Node();
    Coord const         getSnailCoords(size_t val);

    bool                isSolved;

    inline std::vector<int>&    getState() { return this->_state; }
    inline size_t               getScore() const { return this->_score; }
    inline size_t               getSize() const { return this->_size; }
    inline size_t               getG() const { return this->_g; }
    inline Node                 *getParent() const { return this->_parent; }

    Coord const     getEmptyCoord();
    void            processScore();
    size_t          getHash() const;
    
    const Node&         operator=(Node const & rhs);

};

std::ostream&       operator<<(std::ostream& o, Node& n);   

#endif