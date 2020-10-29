//
//  test_runner.cpp
//  Unit Testing Framework
//
//  Created by Лабутин Антон Александрович on 07.08.2020.
//  Copyright © 2020 Labutin Anton. All rights reserved.
//

#include "test_runner.hpp"

using namespace std;

void
Assert(bool b, const string& hint)
{
    AssertEqual(b, true, hint);
}

TestRunner::~TestRunner()
{
    if (fail_count > 0) {
        cerr << fail_count << " unit tests failed. Terminate" << endl;
        exit(1);
    }
}
