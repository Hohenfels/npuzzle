#include "npuzzle.h"

std::pair<std::vector<int>, size_t> Parser::parseFile(const char* file)
{
    std::ifstream               input(file);
    std::string                 line;
    std::vector<int>            puzzle;
    std::vector<bool>           integrity;
    std::vector<std::string>    tokens;
    size_t                      size;
    unsigned int                lineIdx = 0;
    int                         nb;

    if (!input.good())
        parseError(file, 0, "could not open file");
    try { size = getSize(input, lineIdx); }
    catch(const std::exception& e) { parseError(file, lineIdx, e.what()); }
    integrity.assign(size * size, false);
    while (std::getline(input, line))
    {
        lineIdx++;
        if (line.empty() || line[0] == '#')
            continue;
        if ((tokens = splitLine(splitLine(line, '#')[0], ' ')).size() != size)
            parseError(file, lineIdx, "incorrect number of values in the row");
        for (auto t : tokens)
        {
            nb = std::strtol(t.c_str(), nullptr, 10);
            try { checkNbIntegrity(nb, integrity, size, t); }
            catch(const std::exception& e) { parseError(file, lineIdx, e.what()); }
            puzzle.push_back(nb);
        }
    }
    input.close();
    try { checkPuzzleIntegrity(integrity); }
    catch(const std::exception& e) { parseError(file, 0, e.what()); }
    
    return std::make_pair(puzzle, size);
}

std::vector<std::string>    Parser::splitLine(const std::string& line, char delimiter)
{
    std::vector<std::string> tokens;
    std::string word;
    std::istringstream stream(line);
    
    while (std::getline(stream, word, delimiter))
        if (!word.empty())
            tokens.push_back(word);
    
    return tokens;
}

bool                        printable(std::string line)
{
    for (auto &c : line)
        if (!std::isprint(c))
            return false;
    return true;
}

size_t                      Parser::getSize(std::ifstream& fileStream, unsigned int& lineIdx)
{
    std::string                 line;
    std::vector<std::string>    tokens;
    size_t                      ret = 0;

    while (getline(fileStream, line))
    {
        lineIdx++;
        if (line.empty() || !printable(line))
            continue;
        if ((tokens = splitLine(line, '#')).size() > 1 || line[0] != '#')
        {
            if (splitLine(tokens[0], ' ').size() > 1)
                throw Parser::ParserException("Missing or invalid size (" + tokens[0] + ")");
            ret = std::strtol(tokens[0].c_str(), nullptr, 10);
            break;
        }
    }

    if (ret <= 0 || ret == static_cast<size_t>(LONG_MAX))
        throw Parser::ParserException("Invalid size " + (tokens.size() > 0 ? "(" + tokens[0] + ")" : ""));

    return ret;
}

void    Parser::checkNbIntegrity(const int& nb, std::vector<bool>& integrity, const size_t& size, std::string& str_nb)
{
    if (nb == 0 && str_nb != "0")
        throw Parser::ParserException("Undefined value (" + str_nb + ")");
    if (nb < 0)
        throw Parser::ParserException("Value under 0 (" + str_nb + ")");
    if (nb > static_cast<int>(size * size - 1))
        throw Parser::ParserException("Value too high (" + str_nb + ")");
    if (integrity[nb])
        throw Parser::ParserException("Value already declared (" + str_nb + ")");
    else
        integrity[nb] = true;
}

void    Parser::checkPuzzleIntegrity(const std::vector<bool>& integrity)
{
    std::vector<int>    missing;
    std::string         err("Missing value(s) in the given puzzle (");

    for (size_t i = 0; i < integrity.size(); i++)
        if (!integrity[i])
            missing.push_back(i);

    if (!missing.empty())
    {
        for (auto n : missing)
            err.append(std::to_string(n) + ' ');
        err[err.size() - 1] = ')';
        throw Parser::ParserException(err);
    }
}

void    Parser::parseError(const char *filename, unsigned int lineIdx, const char *err)
{
    std::cerr << filename << ": " << (lineIdx != 0 ? std::string("line " + std::to_string(lineIdx) + ": ") : "") << err << "\n";
    exit(1);
}
