//
//  tests.cpp
//  Text Parser
//
//  Created by Лабутин Антон Александрович on 20.10.2020.
//

#include "tests.hpp"
#include "../Parser/parser.hpp"
#include "TestTemplate/test_runner.hpp"

void
AssertTokensParsed(const TokenTypes& tokens1,
                   const TokenTypes& tokens2,
                   const std::string& text)
{
    AssertEqual(tokens1.size(), tokens2.size(), text + " : wrong count of tokens");

    for(size_t idx = 0; idx < tokens1.size(); ++idx) {
        AssertEqual(tokens1[idx].first, tokens2[idx].first, text + " : token1 != token2");
        AssertEqual(tokens1[idx].second, tokens2[idx].second, text + " : token1 type != token2 type");
    }
}

void
TestParseEmptyText()
{
     TokenTypes tokensParsed;
    TokenTypes correctTokens;
    {
        std::string emptyText = "";
        TokenParser tp1(emptyText);
        tokensParsed = tp1.ParseText();
        AssertTokensParsed(tokensParsed, correctTokens, "empty text");
    }
    {
        std::string spaces = "   		  	";
        TokenParser tp1(spaces);
        tokensParsed = tp1.ParseText();
        AssertTokensParsed(tokensParsed, correctTokens, "spaces only");
    }
}

void
TestParseOnlyNumbers()
{
    TokenTypes tokensParsed;
    TokenTypes correctTokens;

    {
        std::string text = "123";
        TokenParser tp(text);
        tokensParsed = tp.ParseText();

        correctTokens.push_back({"123", 'n'});
        AssertTokensParsed(tokensParsed, correctTokens, "123");
        correctTokens.clear();
    }
    {
        std::string text = "    123     456    ";
        TokenParser tp(text);
        tokensParsed = tp.ParseText();

        correctTokens = { {"123", 'n'}, {"456", 'n'} };
        AssertTokensParsed(tokensParsed, correctTokens, "    123     456    ");
        correctTokens.clear();
    }
    {
        std::string text = "    1";
        TokenParser tp(text);
        tokensParsed = tp.ParseText();

        correctTokens = { {"1", 'n'} };
        AssertTokensParsed(tokensParsed, correctTokens, "    1");
        correctTokens.clear();
    }
    {
        std::string text = "2   	 ";
        TokenParser tp(text);
        tokensParsed = tp.ParseText();

        correctTokens = { {"2", 'n'} };
        AssertTokensParsed(tokensParsed, correctTokens, "2        ");
        correctTokens.clear();
    }
    {
        std::string text = " 1 2 3 4 5 ";
        TokenParser tp(text);
        tokensParsed = tp.ParseText();

        correctTokens = { {"1", 'n'}, {"2", 'n'}, {"3", 'n'}, {"4", 'n'}, {"5", 'n'} };
        AssertTokensParsed(tokensParsed, correctTokens, " 1 2 3 4 5 ");
        correctTokens.clear();
    }
}

void
TestParseOnlyStringsWithoutDigits()
{
    TokenTypes tokensParsed;
    TokenTypes correctTokens;

    {
        std::string text = "abc";
        TokenParser tp(text);
        tokensParsed = tp.ParseText();

        correctTokens.push_back({"abc", 's'});
        AssertTokensParsed(tokensParsed, correctTokens, "abc");
        correctTokens.clear();
    }
    {
        std::string text = "    cde";
        TokenParser tp(text);
        tokensParsed = tp.ParseText();

        correctTokens.push_back({"cde", 's'});
        AssertTokensParsed(tokensParsed, correctTokens, "    cde");
        correctTokens.clear();
    }
    {
        std::string text = "fgh   	  	";
        TokenParser tp(text);
        tokensParsed = tp.ParseText();

        correctTokens.push_back({"fgh", 's'});
        AssertTokensParsed(tokensParsed, correctTokens, "fgh             ");
        correctTokens.clear();
    }
    {
        std::string text = "Hello world!";
        TokenParser tp(text);
        tokensParsed = tp.ParseText();

        correctTokens = { {"Hello", 's'}, {"world!", 's'} };
        AssertTokensParsed(tokensParsed, correctTokens, "Hello world!");
        correctTokens.clear();
    }
    {
        std::string text = "	Hello!   I am a string parser!		";
        TokenParser tp(text);
        tokensParsed = tp.ParseText();

        correctTokens = { {"Hello!", 's'}, {"I", 's'}, {"am", 's'}, {"a", 's'}, {"string", 's'}, {"parser!", 's'} };
        AssertTokensParsed(tokensParsed, correctTokens, "    Hello!   I am a string parser!        ");
        correctTokens.clear();
    }
    {
        std::string text = "!!! ???? &&& ))()( ";
        TokenParser tp(text);
        tokensParsed = tp.ParseText();

        correctTokens = { {"!!!", 's'}, {"????", 's'}, {"&&&", 's'}, {"))()(", 's'} };
        AssertTokensParsed(tokensParsed, correctTokens, "!!! ???? &&& ))()( ");
        correctTokens.clear();
    }
}

void
TestParseOnlyStringsWithDigits()
{
    TokenTypes tokensParsed;
    TokenTypes correctTokens;

    {
        std::string text = "abc123";
        TokenParser tp(text);
        tokensParsed = tp.ParseText();

        correctTokens.push_back({"abc123", 's'});
        AssertTokensParsed(tokensParsed, correctTokens, "abc123");
        correctTokens.clear();
    }
    {
        std::string text = "123abc";
        TokenParser tp(text);
        tokensParsed = tp.ParseText();

        correctTokens.push_back({"123abc", 's'});
        AssertTokensParsed(tokensParsed, correctTokens, "123abc");
        correctTokens.clear();
    }
    {
        std::string text = "123abc456";
        TokenParser tp(text);
        tokensParsed = tp.ParseText();

        correctTokens.push_back({"123abc456", 's'});
        AssertTokensParsed(tokensParsed, correctTokens, "123abc456");
        correctTokens.clear();
    }
    {
        std::string text = "abc123def";
        TokenParser tp(text);
        tokensParsed = tp.ParseText();

        correctTokens.push_back({"abc123def", 's'});
        AssertTokensParsed(tokensParsed, correctTokens, "abc123def");
        correctTokens.clear();
    }
    {
        std::string text = "-10";
        TokenParser tp(text);
        tokensParsed = tp.ParseText();

        correctTokens.push_back({"-10", 's'});
        AssertTokensParsed(tokensParsed, correctTokens, "-10");
        correctTokens.clear();
    }
    {
        std::string text = "100.00";
        TokenParser tp(text);
        tokensParsed = tp.ParseText();

        correctTokens.push_back({"100.00", 's'});
        AssertTokensParsed(tokensParsed, correctTokens, "100.00");
        correctTokens.clear();
    }
    {
        std::string text = "        12345a abcdef5    a1b2c3   -15   +25  3.14   10!  0:10:2 ";
        TokenParser tp(text);
        tokensParsed = tp.ParseText();

        correctTokens = { {"12345a", 's'}, {"abcdef5", 's'}, {"a1b2c3", 's'}, {"-15", 's'}, {"+25", 's'}, {"3.14", 's'}, {"10!", 's'}, {"0:10:2", 's'} };
        AssertTokensParsed(tokensParsed, correctTokens, "        12345a abcdef5    a1b2c3   -15   +25  3.14   10!  0:10:2 ");
        correctTokens.clear();
    }
}

void
TestParseComplexText()
{
    TokenTypes tokensParsed;
    TokenTypes correctTokens;

    {
        std::string text = "	123		abc		";
        TokenParser tp(text);
        tokensParsed = tp.ParseText();

        correctTokens = { {"123", 'n'}, {"abc", 's'} };
        AssertTokensParsed(tokensParsed, correctTokens, "    123        abc        ");
        correctTokens.clear();
    }
    {
        std::string text = "    def        456        ";
        TokenParser tp(text);
        tokensParsed = tp.ParseText();

        correctTokens = { {"def", 's'}, {"456", 'n'} };
        AssertTokensParsed(tokensParsed, correctTokens, "    def        456        ");
        correctTokens.clear();
    }
    {
        std::string text = "1 a 2 b 3 c";
        TokenParser tp(text);
        tokensParsed = tp.ParseText();

        correctTokens = { {"1", 'n'}, {"a", 's'}, {"2", 'n'}, {"b", 's'}, {"3", 'n'}, {"c", 's'} };
        AssertTokensParsed(tokensParsed, correctTokens, "1 a 2 b 3 c");
        correctTokens.clear();
    }
    {
        std::string text = "1 a 2 b 3 c";
        TokenParser tp(text);
        tokensParsed = tp.ParseText();

        correctTokens = { {"1", 'n'}, {"a", 's'}, {"2", 'n'}, {"b", 's'}, {"3", 'n'}, {"c", 's'} };
        AssertTokensParsed(tokensParsed, correctTokens, "1 a 2 b 3 c");
        correctTokens.clear();
    }
    {
        std::string text = "123abc 123 def456 456 789ghi987 jkl654mno";
        TokenParser tp(text);
        tokensParsed = tp.ParseText();

        correctTokens = { {"123abc", 's'}, {"123", 'n'}, {"def456", 's'}, {"456", 'n'}, {"789ghi987", 's'}, {"jkl654mno", 's'} };
        AssertTokensParsed(tokensParsed, correctTokens, "123abc 123 def456 456 789ghi987 jkl654mno");
        correctTokens.clear();
    }
    {
        std::string text = "-10 +20 30.0 40.05 (100) 001 5!";
        TokenParser tp(text);
        tokensParsed = tp.ParseText();

        correctTokens = { {"-10", 's'}, {"+20", 's'}, {"30.0", 's'}, {"40.05", 's'}, {"(100)", 's'}, {"001", 'n'}, {"5!", 's'} };
        AssertTokensParsed(tokensParsed, correctTokens, "-10 +20 30.0 40.05 (100) 001 5!");
        correctTokens.clear();
    }
}

void
StartCallback(std::ostream& out)
{
    out << "Testing StartCallback" << std::endl;
}

void
EndCallback(std::ostream& out)
{
    out << "Testing EndCallback" << std::endl;
}

void
NumCallback(int64_t num, std::ostream& out)
{
    out << "Testing NumCallback" << std::endl;
}

void
StrCallback(const std::string& str, std::ostream& out)
{
    out << "Testing StrCallback" << std::endl;
}

void
TestCallbacks()
{
    {
        std::ostringstream oss;
        std::string text = "";
        TokenParser tp(text, oss);

        tp.SetStartCallback(std::function(StartCallback));
        tp.SetEndCallback(std::function(EndCallback));

        tp.ParseText();

        AssertEqual(oss.str(), "Testing StartCallback\nTesting EndCallback\n", "test 1");
    }
    {
        std::ostringstream oss;
        std::string text = "123 abc";
        TokenParser tp(text, oss);

        tp.SetStartCallback(std::function(StartCallback));
        tp.SetEndCallback(std::function(EndCallback));
    	tp.SetNumCallback(std::function(NumCallback));
        tp.SetStrCallback(std::function(StrCallback));

        tp.ParseText();

        AssertEqual(oss.str(), "Testing StartCallback\nTesting NumCallback\nTesting StrCallback\nTesting EndCallback\n", "test 2");
    }
}

void
TestParser()
{
    TestRunner tr;

    tr.RunTest(TestParseEmptyText, "TestParseEmptyText");
    tr.RunTest(TestParseOnlyNumbers, "TestParseOnlyNumbers");
    tr.RunTest(TestParseOnlyStringsWithoutDigits, "TestParseOnlyStringsWithoutDigits");
    tr.RunTest(TestParseOnlyStringsWithDigits, "TestParseOnlyStringsWithDigits");
    tr.RunTest(TestParseComplexText, "TestParseComplexText");

    tr.RunTest(TestCallbacks, "TestCallbacks");
}
