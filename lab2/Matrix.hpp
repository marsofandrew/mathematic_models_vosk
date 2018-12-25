//
// Created by marsofandrew on 12.02.18.
//

#ifndef LABS_MATRIX_HPP
#define LABS_MATRIX_HPP

#include <cstddef>
#include <vector>
#include <algorithm>

namespace detail1
{
  template<typename T>
  T abs(T &value)
  {
    return (value >= 0 ? value : -value);
  }
}

template<typename T, unsigned long rows, unsigned long columns>
class Matrix
{
public:

  static Matrix<T, rows, rows> E();

  Matrix<T, rows, columns>();

  Matrix<T, rows, columns>(const T (&matrix)[rows][columns]);

  Matrix<T, rows, columns>(const Matrix<T, rows, columns> &lhs);

  virtual ~Matrix() = default;

  Matrix<T, rows, columns> &operator=(const Matrix<T, rows, columns> &lhs);

  Matrix<T, rows, columns> &operator+=(const Matrix<T, rows, columns> &lhs);

  Matrix<T, rows, columns> &operator-=(const Matrix<T, rows, columns> &lhs);

  Matrix<T, rows, columns> operator-(const Matrix<T, rows, columns> &rhs);

  Matrix<T, rows, columns> operator+(const Matrix<T, rows, columns> &rhs);

  template<unsigned long columns2>
  Matrix<T, rows, columns2> operator*(Matrix<T, columns, columns2> &rhs);

  Matrix<T, rows, columns> &operator*=(const T &rhs);

  Matrix<T, rows, columns> operator*(const T &rhs);

  double countNorm() const;

  std::vector<std::vector<T>> &getMatrix();

  unsigned long getAmountOfRows() const;

  unsigned long getAmountOfColumns() const;
  //void setColumn(const std::size_t columnIndex, std::)

private:
  std::vector<std::vector<T>> matrix_;
};

template<typename T, unsigned long rows, unsigned long columns>
Matrix<T, rows, columns>::Matrix()
{
  std::vector<T> vector = {};
  vector.assign(columns, 0);
  matrix_.assign(rows, vector);
}

template<typename T, unsigned long rows, unsigned long columns>
Matrix<T, rows, columns>::Matrix(const T (&matrix)[rows][columns])
{
  for (std::size_t i = 0; i < rows; ++i) {
    matrix_.emplace_back(&matrix[i][0], &matrix[i][columns - 1] + 1);
  }
}

template<typename T, unsigned long rows, unsigned long columns>
Matrix<T, rows, columns>::Matrix(const Matrix<T, rows, columns> &lhs):
  matrix_(lhs.matrix_) {}

template<typename T, unsigned long rows, unsigned long columns>
Matrix<T, rows, columns> &Matrix<T, rows, columns>::operator=(const Matrix<T, rows, columns> &lhs)
{
  matrix_ = lhs.matrix_;
  return *this;
}

template<typename T, unsigned long rows, unsigned long columns>
Matrix<T, rows, columns> &Matrix<T, rows, columns>::operator+=(const Matrix<T, rows, columns> &lhs)
{
  for (std::size_t l = 0; l < rows; ++l) {
    for (std::size_t i = 0; i < columns; ++i) {
      matrix_[l][i] = matrix_[l][i] + lhs.matrix_[l][i];
    }
  }
  return *this;
}

template<typename T, unsigned long rows, unsigned long columns>
Matrix<T, rows, columns> &Matrix<T, rows, columns>::operator-=(const Matrix<T, rows, columns> &lhs)
{
  for (std::size_t l = 0; l < rows; ++l) {
    for (std::size_t i = 0; i < columns; ++i) {
      matrix_[l][i] = matrix_[l][i] - lhs.matrix_[l][i];
    }
  }
  return *this;
}

template<typename T, unsigned long rows, unsigned long columns>
Matrix<T, rows, columns> Matrix<T, rows, columns>::operator+(const Matrix<T, rows, columns> &rhs)
{
  Matrix<T, rows, columns> tmp(*this);
  tmp += rhs;
  return tmp;
}

template<typename T, unsigned long rows, unsigned long columns>
Matrix<T, rows, columns> Matrix<T, rows, columns>::operator-(const Matrix<T, rows, columns> &rhs)
{
  Matrix<T, rows, columns> tmp(*this);
  tmp -= rhs;
  return tmp;
}

template<typename T, unsigned long rows, unsigned long columns>
double Matrix<T, rows, columns>::countNorm() const
{
  double result = 0;
  for (std::size_t i = 0; i < rows; i++) {
    T columnSum = 0;
    for (const T t:matrix_[i]) {
      columnSum += detail1::abs(t);
    }
    result = std::max(result, columnSum);
  }
  return result;
}

template<typename T, unsigned long rows, unsigned long columns>
template<unsigned long columns2>
Matrix<T, rows, columns2> Matrix<T, rows, columns>::operator*(Matrix<T, columns, columns2> &rhs)
{
  Matrix<T, rows, columns2> tmp = {};
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns2; ++j) {
      for (int k = 0; k < columns; ++k) {
        tmp.getMatrix()[i][j] += matrix_[i][k] * rhs.getMatrix()[k][j];
      }
    }
  }
  return tmp;
}

template<typename T, unsigned long rows, unsigned long columns>
Matrix<T, rows, columns> Matrix<T, rows, columns>::operator*(const T &rhs)
{
  Matrix<T, rows, columns> tmp = *this;
  tmp *= rhs;
  return tmp;
}

template<typename T, unsigned long rows, unsigned long columns>
Matrix<T, rows, columns> &Matrix<T, rows, columns>::operator*=(const T &rhs)
{
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      matrix_[i][j] *= rhs;
    }
  }
  return *this;
}

template<typename T, unsigned long rows, unsigned long columns>
std::vector<std::vector<T>> &Matrix<T, rows, columns>::getMatrix()
{
  return matrix_;
}

template<typename T, unsigned long rows, unsigned long columns>
unsigned long Matrix<T, rows, columns>::getAmountOfRows() const
{
  return rows;
}

template<typename T, unsigned long rows, unsigned long columns>
unsigned long Matrix<T, rows, columns>::getAmountOfColumns() const
{
  return columns;
}

template<typename T, unsigned long rows, unsigned long columns>
Matrix<T, rows, rows> Matrix<T, rows, columns>::E()
{
  Matrix<T, rows, rows> tmp;
  for (int i = 0; i < rows; ++i) {
    tmp.getMatrix()[i][i] = 1;
  }
  return tmp;
};

template<typename T, unsigned long size>
using Vector = Matrix<T, size, 1>;

#endif //LABS_MATRIX_HPP
