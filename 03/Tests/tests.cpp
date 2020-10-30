//
//  tests.cpp
//  Matrix
//
//  Created by Лабутин Антон Александрович on 27.10.2020.
//

#include "./TestTemplate/test_runner.hpp"
#include "tests.hpp"
#include "../Matrix/matrix.hpp"

void
TestMatrixCreate()
{
    {
        Matrix matrix1;

        AssertEqual(matrix1.GetRowCnt(), 0, "matrix1 has 0 rows");
        AssertEqual(matrix1.GetColumnCnt(), 0, "matrix1 has 0 columns");
    }
    {
        Matrix matrix2(1, 1);

        AssertEqual(matrix2.GetRowCnt(), 1, "matrix2 has 1 row");
        AssertEqual(matrix2.GetColumnCnt(), 1, "matrix2 has 1 column");
    }
    {
        Matrix matrix3(2, 3);

        AssertEqual(matrix3.GetRowCnt(), 2, "matrix3 has 2 rows");
        AssertEqual(matrix3.GetColumnCnt(), 3, "matrix3 has 3 columns");
    }
}



void
TestMatrixOperatorMultNum()
{
    {
        Matrix m1(1, 1);
        m1[0][0] = 1;

        m1 *= 5;

        AssertEqual(m1[0][0], 5, "m1[0][0] = 5");
    }
    {
        Matrix m2(2, 3);
        m2[0][0] = 1;
        m2[0][1] = 2;
        m2[0][2] = 3;
        m2[1][0] = 4;
        m2[1][1] = 5;
        m2[1][2] = 6;

        m2 *= -2;

        AssertEqual(m2[0][0], -2, "m2[0][0] = -2");
        AssertEqual(m2[0][1], -4, "m2[0][1] = -4");
        AssertEqual(m2[0][2], -6, "m2[0][2] = -6");
        AssertEqual(m2[1][0], -8, "m2[1][0] = -8");
        AssertEqual(m2[1][1], -10, "m2[1][1] = -10");
        AssertEqual(m2[1][2], -12, "m2[1][2] = -12");
    }
    {
        Matrix m3(1, 2);
        m3[0][0] = 5;
        m3[0][1] = 10;

        m3 *= 0;

        AssertEqual(m3[0][0], 0, "m3[0][0] = 0");
        AssertEqual(m3[0][1], 0, "m3[0][1] = 0");
    }
}



void
TestMatrixAddition()
{
    {
        Matrix m1(1, 1);
        m1[0][0] = 1;
        Matrix m2(1, 1);
        m2[0][0] = 2;

        Matrix m3 = m1 + m2;
        AssertEqual(m3[0][0], 3, "m3[0][0] = 3");
    }
    {
        Matrix m1(2, 1);
        m1[0][0] = 1;
        m1[1][0] = 2;
        Matrix m2(2, 1);
        m2[0][0] = 3;
        m2[1][0] = 4;

        Matrix m3 = m1 + m2;
        AssertEqual(m3[0][0], 4, "m3[0][0] = 4");
        AssertEqual(m3[1][0], 6, "m3[1][0] = 6");
    }
    {
        Matrix m1(1, 2);
        m1[0][0] = 1;
        m1[0][1] = 2;
        Matrix m2(1, 2);
        m2[0][0] = 0;
        m2[0][1] = 0;

        Matrix m3 = m1 + m2;
        AssertEqual(m3[0][0], 1, "m3[0][0] = 1");
        AssertEqual(m3[0][1], 2, "m3[1][0] = 2");
    }
}


void
TestMatrixOperatorEqual()
{
    {
        Matrix m1;
        Matrix m2;

        Assert(m1 == m2, "empty matrices are equal");
    }
    {
        Matrix m1(1, 1);
        Matrix m2(1, 1);
        m1[0][0] = 1;
        m2[0][0] = 1;

        Assert(m1 == m2, "m1 = m2");
    }
    {
        Matrix m3(2, 2);
        Matrix m4(2, 2);
        m3[0][0] = m4[0][0] = 1;
        m3[0][1] = m4[0][1] = 2;
        m3[1][0] = m4[1][0] = 3;
        m3[1][1] = m4[1][1] = 4;

        Assert(m3 == m4, "m3 = m4");
    }
    {
        Matrix m5(2, 2);
        Matrix m6(2, 2);
        m5[0][0] = m6[0][0] = 1;
        m5[0][1] = m6[0][1] = 2;
        m5[1][0] = m6[1][0] = 3;
        m5[1][1] = 4;
        m6[1][1] = 5;

        Assert(!(m5 == m6), "m5 != m6");
    }
}



void
TestMatrixOperatorNotEqual()
{
    {
        Matrix m1;
        Matrix m2;

        Assert(!(m1 != m2), "empty matrices are equal");
    }
    {
        Matrix m1(1, 1);
        Matrix m2(1, 1);
        m1[0][0] = 1;
        m2[0][0] = 2;

        Assert(m1 != m2, "m1 != m2");
    }
    {
        Matrix m3(2, 2);
        Matrix m4(2, 2);
        m3[0][0] = m4[0][0] = 1;
        m3[0][1] = m4[0][1] = 2;
        m3[1][0] = m4[1][0] = 3;
        m3[1][1] = m4[1][1] = 4;

        Assert(!(m3 != m4), "m3 = m4");
    }
}



void
TestMatrixOperatorAccess()
{
    {
        Matrix m1(1, 1);
        m1[0][0] = 1;
        AssertEqual(m1[0][0], 1, "m1[0][0] = 1");
    }
    {
        Matrix m1(1, 1);
        m1[0][0] = 1;
        AssertEqual(m1[0][0], 1, "m1[0][0] = 1");
    }
    {
        Matrix m2(2, 2);
        m2[0][0] = 1;
        m2[0][1] = 2;
        m2[1][0] = 3;
        m2[1][1] = 4;

        try {
            m2[0][2];
        } catch (std::out_of_range& oor) {
            try {
                m2[3][1];
            } catch (std::out_of_range& oor) {
                AssertEqual(m2[0][0], 1, "m2[0][0] = 1");
                AssertEqual(m2[0][1], 2, "m2[0][1] = 2");
                AssertEqual(m2[1][0], 3, "m2[1][0] = 3");
                AssertEqual(m2[1][1], 4, "m2[1][1] = 4");
            }
        }
    }
}



void
TestMatrix()
{
    TestRunner tr;

    tr.RunTest(TestMatrixCreate, "TestMatrixCreate");
    tr.RunTest(TestMatrixOperatorMultNum, "TestMatrixOperatorMultNum");
    tr.RunTest(TestMatrixAddition, "TestMatrixAddition");
    tr.RunTest(TestMatrixOperatorEqual, "TestMatrixOperatorEqual");
    tr.RunTest(TestMatrixOperatorNotEqual, "TestMatrixOperatorNotEqual");
    tr.RunTest(TestMatrixOperatorAccess, "TestMatrixOperatorAccess");
}
