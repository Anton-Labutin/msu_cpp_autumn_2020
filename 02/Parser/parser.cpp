//
//  parser.cpp
//  Text Parser
//
//  Created by Лабутин Антон Александрович on 15.10.2020.
//

#include "parser.hpp"

#include <iostream>
#include <cstdlib>

void
TokenParser::startParsingStandardFunc(std::ostream& out)
{
    out << "Parsing starts!" << std::endl;
}

void
TokenParser::endParsingStandardFunc(std::ostream& out)
{
    out << "Parsing ends!" << std::endl;
}

void
TokenParser::foundNumStandardFunc(int64_t num, std::ostream& out)
{
    out << "Parsed number " << num << std::endl;
}

void
TokenParser::foundStrStandardFunc(const std::string &str, std::ostream& out)
{
    out << "Parsed string " << str << std::endl;
}

void
TokenParser::SetStartCallback(const std::function<void (std::ostream& out)> &startCallback)
{
    startParsingFunc = startCallback;
}

void
TokenParser::SetEndCallback(const std::function<void (std::ostream& out)> &endCallback)
{
    endParsingFunc = endCallback;
}

void
TokenParser::SetNumCallback(const std::function<void (int64_t, std::ostream& out)> &numCallback)
{
    foundNumFunc = numCallback;
}

void
TokenParser::SetStrCallback(const std::function<void (const std::string &, std::ostream& out)> &strCallback)
{
    foundStrFunc = strCallback;
}



size_t
TokenParser::ParseNumber(size_t startIdx)
{
    size_t endIdx = text.find_first_not_of(digits, startIdx);
    if ( endIdx == std::string::npos || spaces.find_first_of(text[endIdx]) != std::string::npos) {
        return endIdx;
    }

    return startIdx;
}



size_t
TokenParser::ParseString(size_t startIdx)
{
    size_t endIdx = text.find_first_of(spaces, startIdx);
    if ( endIdx == std::string::npos || spaces.find_first_of(text[endIdx]) != std::string::npos) {
        return endIdx;
    }

    return startIdx;
}



void
TokenParser::AddNumber(TokenTypes& tokens, size_t numStartIdx, size_t numEndIdx)
{
    if (numEndIdx != std::string::npos) {
        tokens.push_back( std::pair<std::string, char>
                         (text.substr(numStartIdx, numEndIdx - numStartIdx), 'n')
                         );
        foundNumFunc(strtoul(text.substr(numStartIdx, numEndIdx - numStartIdx).c_str(), nullptr, 10), output);
    } else {
        tokens.push_back( std::pair<std::string, char>
                         (text.substr(numStartIdx), 'n')
                         );
        foundNumFunc(strtoul(text.substr(numStartIdx).c_str(), nullptr, 10), output);
    }
}



void
TokenParser::AddString(TokenTypes& tokens, size_t strStartIdx, size_t strEndIdx)
{
    if (strEndIdx != std::string::npos) {
        tokens.push_back( std::pair<std::string, char>
                         (text.substr(strStartIdx, strEndIdx - strStartIdx), 's')
                         );
        foundStrFunc(text.substr(strStartIdx, strEndIdx - strStartIdx), output);
    } else {
        tokens.push_back( std::pair<std::string, char>
                         (text.substr(strStartIdx), 's')
                         );
        foundStrFunc(text.substr(strStartIdx), output);
    }
}


TokenTypes
TokenParser::ParseText()
{
    startParsingFunc(output);

    TokenTypes tokens;

    size_t textIdx = 0;
    size_t numIdx = 0;
    size_t strIdx = 0;

    bool isString = true;

    size_t charIdx = 0;
    while (textIdx != std::string::npos && textIdx < text.length()) {
        charIdx = text.find_first_not_of(spaces, textIdx);
        if (charIdx != std::string::npos) {
            if (digits.find_first_of(text[charIdx]) != std::string::npos) {
                textIdx = ParseNumber(charIdx);
                if (textIdx != charIdx) {
                    // number parsed
                    isString = false;
                    AddNumber(tokens, charIdx, textIdx);
                } // else it is a string with digits
            }

            if (isString) {
                textIdx = ParseString(charIdx);
                AddString(tokens, charIdx, textIdx);
            }

            isString = true;
        } else {
            textIdx = charIdx;
        }
    }

    endParsingFunc(output);

    return tokens;
}
