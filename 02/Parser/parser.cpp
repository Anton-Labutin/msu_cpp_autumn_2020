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

TokenTypes
TokenParser::ParseText()
{
    startParsingFunc(output);

    TokenTypes tokens;
    const std::string digits("0123456789");
    const std::string spaces(" \t\n");

    size_t textIdx = 0;
    size_t numIdx = 0;
    size_t strIdx = 0;
    size_t spaceIdx = 0;

    while (textIdx < text.length()) {
        numIdx = text.find_first_of(digits, textIdx);
        strIdx = text.find_first_not_of(digits + spaces, textIdx);

        if (numIdx != std::string::npos && strIdx != std::string::npos) {
            if (numIdx < strIdx) { // number is maybe before string
                strIdx = text.find_first_not_of(digits, numIdx);
                if (spaces.find_first_of(text[strIdx]) != std::string::npos) { // no not digits
                    tokens.push_back( std::pair<std::string, char>
                        (text.substr(numIdx, strIdx - numIdx), 'n')
                    );
                    foundNumFunc(strtoul(text.substr(numIdx, strIdx - numIdx).c_str(), nullptr, 10), output);
                    textIdx = strIdx;
                } else {
                    spaceIdx = text.find_first_of(spaces, strIdx); // end of the string
                    if (spaceIdx != std::string::npos) {
                        tokens.push_back( std::pair<std::string, char>
                            (text.substr(numIdx, spaceIdx - numIdx), 's')
                        );
                        foundStrFunc(text.substr(numIdx, spaceIdx - numIdx), output);
                        textIdx = spaceIdx;
                    } else { // last string in text
                        tokens.push_back( std::pair<std::string, char>
                            (text.substr(numIdx), 's')
                        );
                        foundStrFunc(text.substr(numIdx), output);
                        textIdx = text.length();
                    }
                }
            } else { // string is maybe before number
                spaceIdx = text.find_first_of(spaces, strIdx);
                if (spaceIdx != std::string::npos) {
                    tokens.push_back( std::pair<std::string, char>
                        (text.substr(strIdx, spaceIdx - strIdx), 's')
                    );
                    foundStrFunc(text.substr(strIdx, spaceIdx - strIdx), output);
                    textIdx = spaceIdx;
                } else {
                    tokens.push_back( std::pair<std::string, char>
                        (text.substr(strIdx), 's')
                    );
                    foundStrFunc(text.substr(strIdx), output);
                    textIdx = text.length();
                }
            }
        } else { // left either numbers or strings
            if (numIdx == std::string::npos && strIdx == std::string::npos) {
                break;
            }

            if (numIdx == std::string::npos) { // left only strings
                spaceIdx = text.find_first_of(spaces, strIdx);
                if (spaceIdx != std::string::npos) { // not last string
                    tokens.push_back( std::pair<std::string, char>
                        (text.substr(strIdx, spaceIdx - strIdx), 's')
                    );
                    foundStrFunc(text.substr(strIdx, spaceIdx - strIdx), output);
                    textIdx = spaceIdx;
                } else { // the last string
                    if (strIdx != std::string::npos) {
                        tokens.push_back( std::pair<std::string, char>
                            (text.substr(strIdx), 's')
                        );
                        foundStrFunc(text.substr(strIdx), output);
                        textIdx = text.length();
                    }
                }
            } else { // left only numbers
                spaceIdx = text.find_first_of(spaces, numIdx);
                if (spaceIdx != std::string::npos) { // not last
                    tokens.push_back( std::pair<std::string, char>
                        (text.substr(numIdx, spaceIdx - numIdx), 'n')
                    );
                    foundNumFunc(strtoul(text.substr(numIdx, spaceIdx - numIdx).c_str(), nullptr, 10), output);
                    textIdx = spaceIdx;
                } else { // last num
                    // if (numIdx != std::string::npos) {
                        tokens.push_back( std::pair<std::string, char>
                            (text.substr(numIdx), 'n')
                        );
                        foundNumFunc(strtoul(text.substr(numIdx).c_str(), nullptr, 10), output);
                    	textIdx = text.length();
                    // }
                }
            }
        }
    }

    endParsingFunc(output);

    return tokens;
}
