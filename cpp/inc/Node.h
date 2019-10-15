#ifndef __NODE_H__
#define __NODE_H__

#include <vector>
#include <algorithm>
#include <iostream>

#include "solver.h"

//typedef unsigned int (*heuristic)(const Coord &, const Coord &);

class Node 
{

private:
    Node() = delete;
    std::vector<int>    _state;
    Node const          *_parent;
    size_t              _g;
    size_t              _size;
    size_t              _score;
    unsigned int        (*_heuristic)(const Coord &, const Coord &);

    size_t              getHeuristicSum();
    Coord const         getSnailCoords(size_t val);
    size_t              processScore();

public:
    Node(unsigned int (*hFunc)(const Coord &, const Coord &), std::vector<int> state, size_t size);
    Node(const Node &src);

    virtual ~Node();

    bool                isSolved;

    inline std::vector<int>&    getState() { return this->_state; }
    inline size_t               getScore() const { return this->_score; }
    inline size_t               getSize() const { return this->_size; }
    inline const Node           *getAddr() const { return this; }

    Coord const     getEmptyCoord();
    void            processNode();
    

    const Node&         operator=(Node const & rhs);

};

std::ostream&       operator<<(std::ostream& o, Node& n);   

#endif