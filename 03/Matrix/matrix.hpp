//
//  matrix.hpp
//  Matrix
//
//  Created by Лабутин Антон Александрович on 26.10.2020.
//

#ifndef matrix_hpp
#define matrix_hpp

#include <cstddef>
#include <stdexcept>
#include <iostream>

class Matrix {
    int* *matrix = nullptr;
    size_t rowCnt = 0;
    size_t clmCnt = 0;

    class Proxy
    {
        int *matrixRow;
        size_t columnCnt;

    public:
        Proxy(int *matrixRow_, size_t columnCnt_);
        
        int&
        operator [] (size_t clmIdx) noexcept(false);

        int
        operator [] (size_t clmIdx) const noexcept(false);
    };

    int**
    GetMatrix();

    int**
    GetMatrix() const;
public:
    Matrix(size_t rowCnt_ = 0, size_t clmCnt_ = 0);

    Matrix&
    operator *= (int num);

    Matrix
    operator + (const Matrix& m) const noexcept(false);

    bool
    operator == (const Matrix& matr) const noexcept(false);

    bool
    operator != (const Matrix& matr) const noexcept(false);

    Proxy
    operator [] (size_t rowIdx) noexcept(false);

    Proxy
    operator [] (size_t rowIdx) const noexcept(false);

    int&
    Get(size_t rowIdx, size_t clmIdx) noexcept(false);

    int
    Get(size_t rowIdx, size_t clmIdx) const noexcept(false);

    size_t
    GetRowCnt() const;

    size_t
    GetColumnCnt() const;

    ~Matrix();
};

std::ostream&
operator << (std::ostream& output, const Matrix& m);

#endif /* matrix_hpp */
