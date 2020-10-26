//
//  tests.hpp
//  Text Parser
//
//  Created by Лабутин Антон Александрович on 20.10.2020.
//

#ifndef tests_hpp
#define tests_hpp

#include <string>
#include <iostream>

typedef std::vector< std::pair< std::string, char > >  TokenTypes;

void
AssertTokensParsed(const TokenTypes& tokens1,
                   const TokenTypes& tokens2,
                   const std::string& text);

void
TestParseEmptyText();

void
TestParseOnlyNumbers();

void
TestParseOnlyStringsWithoutDigits();

void
TestParseOnlyStringsWithDigits();

void
TestParseComplexText();

void
StartCallback(std::ostream& out = std::cout);

void
EndCallback(std::ostream& out = std::cout);

void
NumCallback(int64_t num, std::ostream& out = std::cout);

void
StrCallback(const std::string& str, std::ostream& out = std::cout);

void
TestCallbacks();

void
TestParser();

#endif /* tests_hpp */
