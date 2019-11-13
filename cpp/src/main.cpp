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
            && strcmp(av[i - 1], "-h") && strcmp(av[i - 1], "-f"))
            OptError("Undefined option (" + std::string(av[i]) + ")");
}

CLOpt   parseCommmandLine(int ac, char **av)
{
    CLOpt   opt;
    int     heuristic = 0;

    checkForUndefined(ac, av);
    if (CLOptionExists(av, av + ac, "--help") || ac == 1)
        OptError("Usage: ./npuzzle -f {FILE} -h {1,2,3} [-g]\nHeuristics:\n1: Manhattan distance\n2: Linear Conflicts\n3: ");
    if (CLOptionExists(av, av + ac, "-f") && getCLOption(av, av + ac, "-f"))
        opt.filename = getCLOption(av, av + ac, "-f");
    else
        OptError("No input file.");
    if (CLOptionExists(av, av + ac, "-h") && getCLOption(av, av + ac, "-h"))
    {
        heuristic = std::strtol(getCLOption(av, av + ac, "-h"), nullptr, 10);
        if (heuristic > 3 || heuristic < 1)
            OptError("Undefined heuristic.");
        else
            opt.heuristicIdx = heuristic - 1;
    }
    else
        OptError("No heuristic index.");
    if (CLOptionExists(av, av + ac, "-g"))
        opt.greedy = true;
    return opt;
}

int     main(int argc, char** argv)
{
    std::pair<std::vector<int>, size_t> puzzle;
    CLOpt                               opt = parseCommmandLine(argc, argv);

    puzzle = Parser::parseFile(opt.filename);

    if (checkSolvability(puzzle.first, puzzle.second))
        solvePuzzle(opt.heuristicIdx, puzzle.second, puzzle.first, opt.greedy);
    else
        return 1;
    return 0;
}