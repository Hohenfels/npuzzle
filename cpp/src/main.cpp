#include "npuzzle.h"


char    *getCLOption(char **begin, char **end, const std::string & option)
{
    auto itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
        return *itr;
    return (nullptr);
}

bool    CLOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

void    OptError(std::string err)
{
    std::cerr << err << "\n[./npuzzle --help] for help\n";
    exit(1);
}

void    checkForUndefined(int ac, char **av)
{
    for (int i = 1; i < ac; i++)
        if (strcmp(av[i], "-f") && strcmp(av[i], "-h") && strcmp(av[i], "-g")
            && strcmp(av[i - 1], "-h") && strcmp(av[i - 1], "-f") && strcmp(av[i], "--greedy") &&
            strcmp(av[i], "-u") && strcmp(av[i], "--uniform-cost") && strcmp(av[i], "-ida")) 
            OptError("Undefined option (" + std::string(av[i]) + ")");
}

CLOpt   parseCommandLine(int ac, char **av)
{
    CLOpt   opt;
    int     heuristic = 0;

    if (CLOptionExists(av, av + ac, "--help") || ac == 1)
        OptError("Usage: ./npuzzle -f {FILE} -h {1,2,3} [-g] [-u] [-ida]\n\n-f: Input file\n\n-h: Heuristic index:\n1: Manhattan distance\n2: "
                "Linear Conflicts\n3: Gaschnig\n\n-g, --greedy: Enables greedy search\n\n-u, --uniform-cost: Enables uniform-cost search\n");
    checkForUndefined(ac, av);
    if (CLOptionExists(av, av + ac, "-f") && getCLOption(av, av + ac, "-f"))
        opt.filename = getCLOption(av, av + ac, "-f");
    else
        OptError("No input file.");
    if (CLOptionExists(av, av + ac, "-h") && getCLOption(av, av + ac, "-h"))
    {
        heuristic = std::strtol(getCLOption(av, av + ac, "-h"), nullptr, 10);
        if (heuristic > 4 || heuristic < 1)
            OptError("Undefined heuristic.");
        else
            opt.heuristicIdx = heuristic - 1;
    }
    else
        OptError("No heuristic index.");
    if (CLOptionExists(av, av + ac, "-g") || CLOptionExists(av, av + ac, "--greedy"))
        opt.greedy = true;
    if (CLOptionExists(av, av + ac, "-u") || CLOptionExists(av, av + ac, "--uniform-cost"))
        opt.uniform = true;
    if (CLOptionExists(av, av + ac, "-ida"))
        opt.ida = true;

    if (opt.greedy && opt.uniform)
        OptError("Cannot perform greedy and uniform-cost searches at the same time");
    else if (opt.ida && (opt.greedy || opt.uniform))
        OptError("IDA* does not support greedy or uniform-cost searches");
    return opt;
}

int     main(int argc, char** argv)
{
    std::pair<std::vector<int>, size_t> puzzle;
    CLOpt                               opt;
    
    (void)argc;
    (void)argv;
    // opt = parseCommandLine(argc, argv);
    puzzle = Parser::parseFile("../tests/valid/test3");

    if (checkSolvability(puzzle.first, puzzle.second))
        if (true)
            IDAStar(1, puzzle.second, puzzle.first);
        else
            AStar(opt.heuristicIdx, puzzle.second, puzzle.first, opt.greedy, opt.uniform);
    else
        return 1;
    while (1);
    return 0;
}