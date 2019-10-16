#include "Node.h"
#include "heuristics.h"

struct PQCMP
{
    bool operator()(const ::Node* lhs, const ::Node* rhs)
    {
        if (lhs->getScore() == rhs->getScore())
            return lhs->getG() < rhs->getG();
        return lhs->getScore() > rhs->getScore();
    }
};

void    solvePuzzle(int hFuncIdx, size_t size, std::vector<int> grid)
{
    unsigned int (*heuristics[1])(const Coord &, const Coord &) = {Heuristics::Manhattan};
    std::priority_queue<Node*, std::vector<Node*>, PQCMP> queue;
    std::map<size_t, Node*>     seen;
    Node    *node = new Node(heuristics[hFuncIdx], grid, size); 
    
    node->processScore();

    seen.insert(std::pair<size_t, Node*>(node->getHash(), node));
    queue.push(node);

    while (!node->isSolved)
    {
        node = queue.top();
        queue.pop();

        for (Node *n : createChildren(node, seen))
        {
            n->processScore();
            queue.push(n);
            seen.insert(std::pair<size_t, Node*>(n->getHash(), n));
        }
    }

    printPath(node);
    deleteNodes(seen);
}

std::vector<Node *>   createChildren(Node *parent, std::map<size_t, Node*>& seen)
{
    std::vector<Node *>   children;
    Coord const         emptyCoord = parent->getEmptyCoord();
    static Coord        moves[4] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
    Coord               newCoords;
    Node                *newChild;


    for (auto m : moves)
    {
        newCoords = {emptyCoord.x + m.x, emptyCoord.y + m.y};
        if (newCoords.x < 0 || newCoords.x == parent->getSize() ||
                newCoords.y < 0 || newCoords.y == parent->getSize())
            continue;
        newChild = new Node(*parent);
        
        std::swap(newChild->getState()[emptyCoord.y * parent->getSize() + emptyCoord.x], newChild->getState()[newCoords.y * parent->getSize() + newCoords.x]);

        if (seen.find(newChild->getHash()) == seen.end())
            children.push_back(newChild);
        else
            delete newChild;
    }

    return children;
}

void    printPath(Node *node)
{
    std::vector<Node*>  path;
    size_t              it = 0;

    while (node->getParent())
    {
        path.push_back(node);
        node = node->getParent();
        ++it;
    }

    std::reverse(path.begin(), path.end());
    for (Node *n : path)
        std::cout << *n << "\n";
    std::cout << "Path length: " << it << "\n";
}

void    deleteNodes(std::map<size_t, Node*>& seen)
{
    for (auto &n : seen)
        delete n.second;
}
