#include "Node.h"

Node::Node(float (*hFunc)(std::vector<int> state, size_t size), std::vector<int> state, size_t size) : _size(size), _heuristic(hFunc), _parent(nullptr), _state(state), _score(0), _g(1), isSolved(false)
{
}

Node::Node(Node& src)
{
    *this = src;
    this->_parent = &src;
    this->_score = 0;
    ++this->_g;
}

Node const &  Node::operator=(Node const & rhs)
{
    this->_state = std::vector<int>(rhs._state);
    this->_parent = rhs._parent;
    this->_g = rhs._g;
    this->_size = rhs._size;
    this->_heuristic = rhs._heuristic;
    return *this;
}

Node::~Node()
{
}

size_t  Node::getHeuristic()
{
    return this->_heuristic(this->_state, this->_size);
}

Coord const     Node::getSnailCoords(int val, size_t size)
{
    int     r = 0;
    int     d, m, c;
    int     span = size;

    while (val > span)
    {
        val -= span;
        span -= ++r % 2;
    }
    d = r / 4;
    m = r % 4;
    c = size - 1 - d;

    return {(snailRet){d + val - 1, c, c - val, d}.array[m], (snailRet){d, d + val, c, c - val}.array[m]};
}

Coord const     Node::getEmptyCoord()
{
   auto idx = std::find(_state.begin(), _state.end(), 0) - _state.begin(); 
   return {static_cast<int>(idx % this->_size), static_cast<int>(idx / this->_size)};
}

size_t          Node::getHash() const
{
    std::string     s;

    for (auto &v : this->_state)
        s.push_back(static_cast<char>(v + 48));

    return std::hash<std::string>()(s);
}

void    Node::processScore(bool greedy, bool uniform)
{
    float   heuristicSum = this->getHeuristic();
    this->_score = (greedy ? 0 : static_cast<float>(this->_g)) + (uniform ? 0 : heuristicSum);
    this->isSolved = (heuristicSum ? false : true);
}

std::ostream&       operator<<(std::ostream& o, Node& n)
{
    std::vector<int>    puzzle = n.getState();
    size_t              size = n.getSize();
    int                 width = log10(size * size - 1) + 1;

    for (size_t i = 0; i < puzzle.size(); i++)
        o << std::right << std::setw(width) << puzzle[i] << (!((i + 1) % size) ? " \n" : " ");
    
    return o;
}
