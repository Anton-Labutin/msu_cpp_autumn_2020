//
//  test_runner.hpp
//  Unit Testing Framework
//
//  Created by Лабутин Антон Александрович on 07.08.2020.
//  Copyright © 2020 Labutin Anton. All rights reserved.
//

#ifndef test_runner_hpp
#define test_runner_hpp

#include <sstream>
#include <exception>
#include <iostream>
#include <string>


class TestRunner {
public:
    template <class TestFunc>
    void
    RunTest(TestFunc, const std::string&);

    ~TestRunner();

private:
    int fail_count = 0;
};


void
Assert(bool, const std::string&);


template <class TestFunc>
void
TestRunner::RunTest(TestFunc func, const std::string& test_name)
{
    try {
        func();
        std::cerr << test_name << " OK" << std::endl;
    } catch (std::runtime_error& e) {
        ++fail_count;
        std::cerr << test_name << " fail: " << e.what() << std::endl;
    }
}

template<class T, class U>
void
AssertEqual(const T& t, const U& u, const std::string& hint)
{
    if (t != u) {
        std::ostringstream os;
        os << "Assertion failed: " << t << " != " << u << " hint: " << hint;
        throw std::runtime_error(os.str());
    }
}

#endif /* test_runner_hpp */
