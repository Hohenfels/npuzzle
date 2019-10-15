#include "Node.h"
#include "heuristics.h"

void    solvePuzzle(int hFuncIdx, size_t size, std::vector<int> grid)
{
    unsigned int (*heuristics[1])(const Coord &, const Coord &) = {Heuristics::Manhattan};

    auto cmp = [](Node& left, Node& right) { return left.getScore() < right.getScore(); };
    std::priority_queue<Node, std::vector<Node>, decltype(cmp)> queue(cmp);
    
    std::vector<Node const *>  seen;

    Node    node(heuristics[hFuncIdx], grid, size);
    
    seen.push_back(node.getAddr());
    queue.push(node);

    while (!node.isSolved)
    {
        node = queue.top();
        queue.pop();

        for (auto &n : createChildren(node, seen))
        {
            n.processNode();
            queue.push(n);
            seen.push_back(n.getAddr());
        }
    }

    return;
}

std::vector<Node>   createChildren(Node parent, std::vector<Node const *>& seen)
{
    std::vector<Node>   children;
    Coord const         emptyCoord = parent.getEmptyCoord();
    static Coord        moves[4] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
    Coord               newCoords;
    std::shared_ptr<Node>   newChild;

    for (auto m : moves)
    {
        newCoords = {emptyCoord.x + m.x, emptyCoord.y + m.y};
        if (newCoords.x < 0 || newCoords.x == parent.getSize() ||
                newCoords.y < 0 || newCoords.y == parent.getSize())
            continue;
        newChild = std::make_shared<Node>(Node(parent));
        
        std::swap(newChild->getState()[emptyCoord.y * parent.getSize() + emptyCoord.x], newChild->getState()[newCoords.y * parent.getSize() + newCoords.x]);

        if (std::find(seen.begin(), seen.end(), newChild->getAddr()) == seen.end())
            children.push_back(*newChild);
    }

    return children;
}
