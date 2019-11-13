#include "../inc/Node.h"

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

size_t  Node::getHeuristicSum()
{
    return this->_heuristic(this->_state, this->_size);
}

Coord const     Node::getSnailCoords(size_t val, size_t size)
{
    int     r = 0;
    int     d, m, c;
    size_t     x[4];
    size_t     y[4];
    size_t  span = size;

    while (val > span)
    {
        val -= span;
        span -= ++r % 2;
    }
    d = r / 4;
    m = r % 4;
    c = size - 1 - d;

    x[0] = d;
    x[1] = d + val;
    x[2] = c;
    x[3] = c - val;

    y[0] = d + val - 1;
    y[1] = c;
    y[2] = c - val;
    y[3] = d;

    return {static_cast<int>(y[m]), static_cast<int>(x[m])};
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

void    Node::processScore()
{
    float   heuristicSum = this->getHeuristicSum();
    this->_score = static_cast<float>(this->_g) + heuristicSum;
    this->isSolved = (heuristicSum ? false : true);
}

std::ostream&       operator<<(std::ostream& o, Node& n)
{
    std::vector<int>    puzzle = n.getState();
    size_t              size = n.getSize();
    
    o << "Score:" << n.getScore() << "\n";
    for (size_t i = 0; i < puzzle.size(); i++)
        o << puzzle[i] << (!((i + 1) % size) ? "\n" : " ");
    
    return o;
}
