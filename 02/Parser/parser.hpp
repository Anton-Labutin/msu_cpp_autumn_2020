//
//  parser.hpp
//  Text Parser
//
//  Created by Лабутин Антон Александрович on 15.10.2020.
//

#ifndef parser_hpp
#define parser_hpp

#include <iostream>
#include <string>
#include <functional>
#include <cstdint>
#include <vector>
#include <utility>

typedef std::vector< std::pair< std::string, char > >  TokenTypes;

class TokenParser {
    std::string text;

    const std::string digits = "0123456789";
    const std::string spaces = " \t\n";

    std::function<void (std::ostream& out)> startParsingFunc = startParsingStandardFunc;
    std::function<void (std::ostream& out)> endParsingFunc = endParsingStandardFunc;

    std::function<void (int64_t num, std::ostream& out)> foundNumFunc = foundNumStandardFunc;
    std::function<void (const std::string &str, std::ostream& out)> foundStrFunc = foundStrStandardFunc;

    static void
    startParsingStandardFunc(std::ostream& out = std::cout);

    static void
    endParsingStandardFunc(std::ostream& out = std::cout);

    static void
    foundNumStandardFunc(int64_t num, std::ostream& out = std::cout);

    static void
    foundStrStandardFunc(const std::string& str, std::ostream& out = std::cout);

    std::ostream& output = std::cout;

    size_t
    ParseNumber(size_t);

    size_t
    ParseString(size_t);

    void
    AddNumber(TokenTypes& tokens, size_t numStartIdx, size_t numEndIdx);

    void
    AddString(TokenTypes& tokens, size_t strStartIdx, size_t strEndIdx);

public:
    TokenParser(std::string& txt, std::ostream& out = std::cout)
        : text(txt), output(out)
        {}

    void
    SetStartCallback(const std::function<void (std::ostream& out)>& startCallback);

    void
    SetEndCallback(const std::function<void (std::ostream& out)>& endCallback);

    void
    SetNumCallback(const std::function<void (int64_t num, std::ostream& out)>& numCallback);

    void
    SetStrCallback(const std::function<void (const std::string& str, std::ostream& out)>& strCallback);

    TokenTypes
    ParseText();
};

#endif /* parser_hpp */
