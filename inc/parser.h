#ifndef __PARSER_H__
#define __PARSER_H__

#include "npuzzle.h"
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <exception>
#include <climits>

namespace Parser
{
    std::pair<std::vector<int>, size_t> parseFile(const char* file);
    std::vector<std::string>            splitLine(const std::string& line, char delimiter);
    size_t                              getSize(std::ifstream& fileStream, unsigned int& lineIdx);
    void                                parseError(const char *filename, unsigned int lineIdx, const char *err);
    void                                checkNbIntegrity(const int& nb, std::vector<bool>& integrity, const size_t& size, std::string& str_nb);
    void                                checkPuzzleIntegrity(const std::vector<bool>& integrity);

    class ParserException : public std::exception
    {
        private:
            std::string msg;

        public:
            inline ParserException(std::string err) throw() { msg = err; }
            inline virtual ~ParserException() throw() {};
            inline const char *what() const throw() { return msg.c_str(); }
    };
};

#endif