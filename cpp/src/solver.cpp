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

void    AStar(int hFuncIdx, size_t size, std::vector<int> grid, bool greedy, bool uniform, bool demo)
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

        for (Node *n : createChildren(node, &seen))
        {
            n->processScore(greedy, uniform);
            queue.push(n);
            seen.insert(std::pair<size_t, Node*>(n->getHash(), n));
            spaceComplexity++;
        }
        timeComplexity++;
    }

    printTime(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - begin).count());
    printPath(node, timeComplexity, spaceComplexity, std::deque<std::pair<size_t, void*>>(), demo);
    deleteNodes(seen);
}

std::pair<bool, long long>   IDASearch(std::deque<std::pair<size_t, void*>>& path, int cost, long threshold, size_t& time, size_t& space)
{
    Node    *node = static_cast<Node*>(path[0].second);
    int     score = cost + node->getHeuristic();
    std::pair<bool, long long>          searchRet;
    long    ret = __LONG_MAX__;

    if (score > threshold)
        return std::make_pair<bool, long>(false, score);
    else if (node->getHeuristic() == 0)
        return std::make_pair<bool, long>(true, score);
    for (Node *child : createChildren(node, nullptr))
    {
        if (std::find_if(path.begin(), path.end(), [&child](const std::pair<size_t, void*>& check) { return child->getHash() == check.first; }) == path.end())
        {
            path.push_front(std::make_pair<size_t, void*>(child->getHash(), child));
            searchRet = IDASearch(path, cost + 1, threshold, time, space);
            if (searchRet.first)
                return searchRet;
            else if (searchRet.second < ret)
                ret = searchRet.second;
            delete static_cast<Node*>(path[0].second);
            path.pop_front();
            space++;
        }
        else
            delete child;
    }
    time++;

    return std::make_pair<bool, long long>(false, ret);
}

void                    IDAStar(int hFuncIdx, size_t size, std::vector<int> grid, bool demo)
{
    float (*heuristics[4])(std::vector<int> state, size_t size) = {Heuristics::Manhattan, Heuristics::LinearConflict, Heuristics::Gaschnig, Heuristics::Yolo};
    std::deque<std::pair<size_t, void*>>  path;
    size_t                              timeComplexity = 0;
    size_t                              spaceComplexity = 0;
    std::pair<bool, long long>          ret;
    long                                threshold;
    auto                                begin = std::chrono::steady_clock::now();
    Node                                *node = new Node(heuristics[hFuncIdx], grid, size);

    threshold = node->getHeuristic();
    path.push_front(std::make_pair<size_t, void*>(node->getHash(), node));

    while (!path.empty())
    {
        ret = IDASearch(path, 0, threshold, timeComplexity, spaceComplexity);
        if (ret.first || ret.second == __LONG_MAX__)
            break; //solved
        else
            threshold = ret.second;
        timeComplexity++;
    }

    printTime(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - begin).count());
    printPath(nullptr, timeComplexity, spaceComplexity, path, demo);

    for (auto i : path)
        delete static_cast<Node*>(i.second);

}

std::vector<Node *>   createChildren(Node *parent, std::map<size_t, Node*> *seen)
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

        if (!seen || seen->find(newChild->getHash()) == seen->end())
            children.push_back(newChild);
        else
            delete newChild;
    }

    return children;
}

void    printState(Node *node)
{
    std::cout << "\033[2J\033[H";
    std::cout << *node << "\n";
    sleep(1);
}

void    printPath(Node *node, size_t timeComplexity, size_t spaceComplexity, std::deque<std::pair<size_t, void*>> ida_path, bool demo)
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
    else
    {
        for (auto it = ida_path.rbegin(); it != ida_path.rend(); ++it)
        {
            path.push_back(static_cast<Node*>(it->second));
            ++length;
        }
    }

    output.open("path.txt");
    if (output.good())
        for (Node *n : path)
        {
            if (demo)
                printState(n);
            output << *n << "\n";
        }
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
