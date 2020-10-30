//
//  matrix.cpp
//  Matrix
//
//  Created by Лабутин Антон Александрович on 26.10.2020.
//

#include "matrix.hpp"

Matrix::Matrix(size_t rowCnt_, size_t clmCnt_)
	: rowCnt(rowCnt_), clmCnt(clmCnt_)
{
    matrix = new int* [rowCnt];
    for (size_t rowIdx = 0; rowIdx < rowCnt; ++rowIdx) {
        matrix[rowIdx] = new int [clmCnt];
    }
}


Matrix::Proxy::Proxy(int *matrixRow_, size_t columnCnt_)
    : matrixRow(matrixRow_), columnCnt(columnCnt_)
{}

int&
Matrix::Proxy::operator[](size_t clmIdx)
{
    if (matrixRow == nullptr) {
        throw std::logic_error("matrixRow is null");
    }

    if (clmIdx >= columnCnt) {
        throw std::out_of_range("Column index is out of range");
    }

    return matrixRow[clmIdx];
}



int
Matrix::Proxy::operator[](size_t clmIdx) const
{
    if (matrixRow == nullptr) {
        throw std::logic_error("matrixRow is null");
    }

    if (clmIdx >= columnCnt) {
        throw std::out_of_range("Column index is out of range");
    }

    return matrixRow[clmIdx];
}


Matrix::Proxy
Matrix::operator [] (size_t rowIdx)
{
    if (GetMatrix() == nullptr) {
        throw std::logic_error("Matrix is empty");
    }

    if (rowIdx >= GetRowCnt()) {
        throw std::out_of_range("Row index is out of range");
    }

    return Proxy((GetMatrix())[rowIdx], GetColumnCnt());
}



Matrix::Proxy
Matrix::operator [] (size_t rowIdx) const
{
    if (GetMatrix() == nullptr) {
        throw std::logic_error("Matrix is empty");
    }

    if (rowIdx >= GetRowCnt()) {
        throw std::out_of_range("Row index is out of range");
    }

    return Proxy((GetMatrix())[rowIdx], GetColumnCnt());
}


Matrix&
Matrix::operator *= (int num)
{
    for (size_t rowIdx = 0; rowIdx < GetRowCnt(); ++rowIdx) {
        for (size_t clmIdx = 0; clmIdx < GetColumnCnt(); ++clmIdx) {
            Get(rowIdx, clmIdx) *= num;
        }
    }

    return *this;
}



Matrix
Matrix::operator + (const Matrix& m) const
{
    if (GetRowCnt() != m.GetRowCnt() || GetColumnCnt() != m.GetColumnCnt()) {
        throw std::invalid_argument("Incorrect matrix size");
    }

    Matrix sum(GetRowCnt(), GetColumnCnt());
    for (size_t rowIdx = 0; rowIdx < GetRowCnt(); ++rowIdx) {
        for (size_t clmIdx = 0; clmIdx < GetColumnCnt(); ++clmIdx) {
            sum[rowIdx][clmIdx] = Get(rowIdx, clmIdx) + m.Get(rowIdx, clmIdx);
        }
    }

    return sum;
}



bool
Matrix::operator == (const Matrix& matr) const
{
    if (matr.GetRowCnt() != GetRowCnt()
        || matr.GetColumnCnt() != GetColumnCnt()) {
        throw std::invalid_argument("Incorrect matrix size");
    }

    for (size_t rowIdx = 0; rowIdx < GetRowCnt(); ++rowIdx) {
        for (size_t clmIdx = 0; clmIdx < GetColumnCnt(); ++clmIdx) {
            if (Get(rowIdx, clmIdx) != matr.Get(rowIdx, clmIdx) ) {
                return false;
            }
        }
    }

    return true;
}



bool
Matrix::operator != (const Matrix& matr) const
{
    return ! (*this == matr);
}



int&
Matrix::Get(size_t rowIdx, size_t clmIdx)
{
    if (rowIdx >= GetRowCnt() || clmIdx >= GetColumnCnt()) {
        throw std::out_of_range("");
    }

    return (GetMatrix())[rowIdx][clmIdx];
}



int
Matrix::Get(size_t rowIdx, size_t clmIdx) const
{
    if (rowIdx >= rowCnt || clmIdx >= clmCnt) {
        throw std::out_of_range("Indices are out of range");
    }

    return (GetMatrix())[rowIdx][clmIdx];
}



int**
Matrix::GetMatrix()
{
    return matrix;
}



int**
Matrix::GetMatrix() const
{
    return matrix;
}



size_t
Matrix::GetRowCnt() const
{
    return rowCnt;
}



size_t
Matrix::GetColumnCnt() const
{
    return clmCnt;
}



Matrix::~Matrix()
{
    if (matrix) {
        for (size_t rowIdx = 0; rowIdx < GetRowCnt(); ++rowIdx) {
            delete [] matrix[rowIdx];
        }

        delete [] matrix;
    }
}



std::ostream&
operator << (std::ostream& output, const Matrix& m)
{
    for (size_t rowIdx = 0; rowIdx < m.GetRowCnt(); ++rowIdx) {
        for (size_t clmIdx = 0; clmIdx < m.GetColumnCnt(); ++clmIdx) {
            if (clmIdx) {
                output << " ";
            }

            output << m.Get(rowIdx, clmIdx);
        }
        if (rowIdx) {
            output << std::endl;
        }
    }

    return output;
}
