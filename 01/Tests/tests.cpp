//
//  tests.cpp
//  My Allocator
//
//  Created by Лабутин Антон Александрович on 10.10.2020.
//

#include "tests.hpp"
#include "TestTemplate/test_runner.hpp"
#include "../Allocator/my_allocator.hpp"

void
TestMakeAllocator()
{
    {
        Allocator al1;
        al1.MakeAllocator(10);
        AssertEqual(al1.GetMaxSize(), 10, "al1 has max size 10");
        AssertEqual(al1.GetLeftSize(), 10, "al1 has left size 10");
    }
    {
        Allocator al2;
        al2.MakeAllocator(0);
        AssertEqual(al2.GetMaxSize(), 0, "al2 has max size 0");
        AssertEqual(al2.GetLeftSize(), 0, "al2 has left size 0");
    }
}

void
TestAlloc()
{
    {
        Allocator al1;
        al1.MakeAllocator(0);
        al1.Alloc(0);
        AssertEqual(al1.GetMaxSize(), 0, "al1 has max size 0");
        AssertEqual(al1.GetLeftSize(), 0, "al1 has left size 0");
    }
    {
        Allocator al2;
        al2.MakeAllocator(10);
        al2.Alloc(6);
        AssertEqual(al2.GetMaxSize(), 10, "al2 has max size 10");
        AssertEqual(al2.GetLeftSize(), 4, "al2 has left size 4");
    }
    {
        Allocator al3;
        al3.MakeAllocator(100);
        al3.Alloc(40);
        al3.Alloc(30);
        AssertEqual(al3.GetMaxSize(), 100, "al3 has max size 100");
        AssertEqual(al3.GetLeftSize(), 30, "al3 has left size 30");
    }
    {
        Allocator al4;
        al4.MakeAllocator(1000);
        al4.Alloc(1000);
        AssertEqual(al4.GetMaxSize(), 1000, "al4 has max size 1000");
        AssertEqual(al4.GetLeftSize(), 0, "al4 has left size 0");
    }
    {
        Allocator al5;
        al5.MakeAllocator(2000);
        Assert(! al5.Alloc(3000), "al5 has not enough memory");
    }
}

void
TestReset()
{
    {
        Allocator al1;
        al1.MakeAllocator(20);
        al1.Reset();
        AssertEqual(al1.GetMaxSize(), 20, "al1 has max size 20");
        AssertEqual(al1.GetLeftSize(), 20, "al1 has left size 20");
    }
    {
        Allocator al2;
        al2.MakeAllocator(100);
        al2.Alloc(50);
        al2.Reset();
        AssertEqual(al2.GetMaxSize(), 100, "al2 has max size 100");
        AssertEqual(al2.GetLeftSize(), 100, "al2 has left size 100");
    }
    {
        Allocator al3;
        al3.MakeAllocator(1000);
        al3.Alloc(1000);
        al3.Reset();
        AssertEqual(al3.GetMaxSize(), 1000, "al3 has max size 1000");
        AssertEqual(al3.GetLeftSize(), 1000, "al3 has left size 1000");
    }
}

void
TestAllocator()
{
    TestRunner tr;
    tr.RunTest(TestMakeAllocator, "TestMakeAllocator");
    tr.RunTest(TestAlloc, "TestAlloc");
    tr.RunTest(TestReset, "TestReset");
}
