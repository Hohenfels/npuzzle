#include "solver.h"

struct PQCMP
{
    bool operator()(const ::Node* lhs, const ::Node* rhs)
    {
        if (lhs->getScore() == rhs->getScore())
            return lhs->getG() < rhs->getG();
        return lhs->getScore() > rhs->getScore();
    }
};

void    AStar(int hFuncIdx, size_t size, std::vector<int> grid, bool greedy, bool uniform)
{
    float (*heuristics[4])(std::vector<int> state, size_t size) = {Heuristics::Manhattan, Heuristics::LinearConflict, Heuristics::Gaschnig, Heuristics::Yolo};
    std::priority_queue<Node*, std::vector<Node*>, PQCMP> queue;
    std::map<size_t, Node*>     seen;
    auto        begin = std::chrono::steady_clock::now();
    Node        *node = new Node(heuristics[hFuncIdx], grid, size);
    size_t      timeComplexity = 0;
    size_t      spaceComplexity = 0;
    
    node->processScore(greedy, uniform);

    seen.insert(std::pair<size_t, Node*>(node->getHash(), node));
    queue.push(node);

    while (!node->isSolved)
    {
        node = queue.top();
        queue.pop();

        for (Node *n : createChildren(node, seen))
        {
            n->processScore(greedy, uniform);
            queue.push(n);
            seen.insert(std::pair<size_t, Node*>(n->getHash(), n));
            spaceComplexity++;
        }
        timeComplexity++;
    }

    printTime(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - begin).count());
    printPath(node, timeComplexity, spaceComplexity);
    deleteNodes(seen);
}

std::vector<Node *>   createChildren(Node *parent, std::map<size_t, Node*>& seen)
{
    std::vector<Node *>   children;
    Coord const         emptyCoord = parent->getEmptyCoord();
    static Coord        moves[4] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
    Coord               newCoords;
    Node                *newChild;


    for (auto &m : moves)
    {
        newCoords = {emptyCoord.x + m.x, emptyCoord.y + m.y};
        if (newCoords.x < 0 || newCoords.x == static_cast<int>(parent->getSize()) ||
                newCoords.y < 0 || newCoords.y == static_cast<int>(parent->getSize()))
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

void    printPath(Node *node, size_t timeComplexity, size_t spaceComplexity)
{
    std::vector<Node*>  path;
    size_t              length = 0;
    std::ofstream       output;

    if (node)
    {
        while (node->getParent())
        {
            path.push_back(node);
            node = node->getParent();
            ++length;
        }
        path.push_back(node);
        ++length;

        std::reverse(path.begin(), path.end());
    }

    output.open("path.txt");
    if (output.good())
        for (Node *n : path)
            output << *n << "\n";
    output.close();
    std::cout << "Path length: " << --length << "\nTime complexity: " << timeComplexity << "\nSpace complexity: " << spaceComplexity << "\nPath written to path.txt\n";
}

void    deleteNodes(std::map<size_t, Node*>& seen)
{
    for (auto &n : seen)
        delete n.second;
}

void                    printTime(std::chrono::microseconds::rep diff)
{
    std::cout << "Solver ran in ";
    if (diff > 999999)
        std::cout << std::setprecision(3) << static_cast<double>(diff) / 1000000.f << "s\n";
    else if (diff > 999)
        std::cout << std::setprecision(3) << static_cast<double>(diff) / 1000.f << "ms\n";
    else
        std::cout << diff << "μs\n";
}
