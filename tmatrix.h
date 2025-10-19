#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm> // std::swap
#include "tvector.h" // assumes TDynamicVector is available and header-only

static constexpr size_t MAX_MATRIX_SIZE = 10000;

template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using Base = TDynamicVector<TDynamicVector<T>>;
  using Base::pMem;
  using Base::size;

public:
  TDynamicMatrix(size_t s = 1);
  TDynamicMatrix(const TDynamicMatrix& other);
  TDynamicMatrix(TDynamicMatrix&& other) noexcept;
  ~TDynamicMatrix() = default;

  TDynamicMatrix& operator=(const TDynamicMatrix& other);
  TDynamicMatrix& operator=(TDynamicMatrix&& other) noexcept;

  using Base::operator[];

  size_t GetSize() const noexcept
  {
    return size;
  }

  bool operator==(const TDynamicMatrix& m) const noexcept;
  bool operator!=(const TDynamicMatrix& m) const noexcept;

  TDynamicMatrix operator*(const T& val) const;
  TDynamicVector<T> operator*(const TDynamicVector<T>& v) const;
  TDynamicMatrix operator+(const TDynamicMatrix& m) const;
  TDynamicMatrix operator-(const TDynamicMatrix& m) const;
  TDynamicMatrix operator*(const TDynamicMatrix& m) const;

  void swap(TDynamicMatrix& other) noexcept
  {
    std::swap(this->size, other.size);
    std::swap(this->pMem, other.pMem);
  }
};

// -------------------- Implementations --------------------

template <class T>
TDynamicMatrix<T>::TDynamicMatrix(size_t s) : Base(s)
{
  if (s == 0)
  {
    throw std::out_of_range("Matrix size should be greater than zero");
  }

  if (s > MAX_MATRIX_SIZE)
  {
    throw std::length_error("Matrix size exceeds maximum allowed size");
  }

  // initialize each row to the correct length
  for (size_t i = 0; i < size; i++)
  {
    pMem[i] = TDynamicVector<T>(size);
  }
}

template <class T>
TDynamicMatrix<T>::TDynamicMatrix(const TDynamicMatrix<T>& other) : Base(other)
{
  // Base copy ctor already copies rows; nothing extra needed
}

template <class T>
TDynamicMatrix<T>::TDynamicMatrix(TDynamicMatrix<T>&& other) noexcept : Base(std::move(other))
{
  // Base move ctor does the work
}

template <class T>
TDynamicMatrix<T>& TDynamicMatrix<T>::operator=(const TDynamicMatrix<T>& other)
{
  if (this != &other)
  {
    TDynamicMatrix<T> tmp(other);
    this->swap(tmp);
  }
  return *this;
}

template <class T>
TDynamicMatrix<T>& TDynamicMatrix<T>::operator=(TDynamicMatrix<T>&& other) noexcept
{
  if (this != &other)
  {
    // steal resources
    std::swap(this->size, other.size);
    std::swap(this->pMem, other.pMem);
  }
  return *this;
}

template <class T>
bool TDynamicMatrix<T>::operator==(const TDynamicMatrix<T>& m) const noexcept
{
  if (this->size != m.size)
  {
    return false;
  }

  for (size_t i = 0; i < this->size; i++)
  {
    if (this->pMem[i] != m.pMem[i])
    {
      return false;
    }
  }

  return true;
}

template <class T>
bool TDynamicMatrix<T>::operator!=(const TDynamicMatrix<T>& m) const noexcept
{
  return !(*this == m);
}

template <class T>
TDynamicMatrix<T> TDynamicMatrix<T>::operator*(const T& val) const
{
  TDynamicMatrix<T> result(this->size);

  for (size_t i = 0; i < this->size; i++)
  {
    result.pMem[i] = this->pMem[i] * val;
  }

  return result;
}

template <class T>
TDynamicVector<T> TDynamicMatrix<T>::operator*(const TDynamicVector<T>& v) const
{
  if (this->size != v.GetSize())
  {
    throw std::invalid_argument("Matrix columns must match vector size for multiplication");
  }

  TDynamicVector<T> result(this->size);

  for (size_t i = 0; i < this->size; i++)
  {
    // pMem[i] is a row vector; pMem[i] * v is dot-product (scalar)
    result[i] = this->pMem[i] * v;
  }

  return result;
}

template <class T>
TDynamicMatrix<T> TDynamicMatrix<T>::operator+(const TDynamicMatrix<T>& m) const
{
  if (this->size != m.size)
  {
    throw std::invalid_argument("Matrices must be of the same size for addition");
  }

  for (size_t i = 0; i < this->size; i++)
  {
    if (this->pMem[i].GetSize() != m.pMem[i].GetSize())
    {
      throw std::invalid_argument("Matrices must have rows of the same length for addition");
    }
  }

  TDynamicMatrix<T> result(this->size);

  for (size_t i = 0; i < this->size; i++)
  {
    result.pMem[i] = this->pMem[i] + m.pMem[i];
  }

  return result;
}

template <class T>
TDynamicMatrix<T> TDynamicMatrix<T>::operator-(const TDynamicMatrix<T>& m) const
{
  if (this->size != m.size)
  {
    throw std::invalid_argument("Matrices must be of the same size for subtraction");
  }

  for (size_t i = 0; i < this->size; i++)
  {
    if (this->pMem[i].GetSize() != m.pMem[i].GetSize())
    {
      throw std::invalid_argument("Matrices must have rows of the same length for subtraction");
    }
  }

  TDynamicMatrix<T> result(this->size);

  for (size_t i = 0; i < this->size; i++)
  {
    result.pMem[i] = this->pMem[i] - m.pMem[i];
  }

  return result;
}

template <class T>
TDynamicMatrix<T> TDynamicMatrix<T>::operator*(const TDynamicMatrix<T>& m) const
{
  if (this->size != m.size)
  {
    throw std::invalid_argument("Matrices must be of the same size for multiplication");
  }

  for (size_t i = 0; i < this->size; i++)
  {
    if (this->pMem[i].GetSize() != m.pMem[i].GetSize())
    {
      throw std::invalid_argument("Matrix rows must match for multiplication");
    }
  }

  TDynamicMatrix<T> result(this->size);

  for (size_t i = 0; i < this->size; i++)
  {
    for (size_t j = 0; j < this->size; j++)
    {
      result.pMem[i][j] = T();

      for (size_t k = 0; k < this->size; k++)
      {
        result.pMem[i][j] += this->pMem[i][k] * m.pMem[k][j];
      }
    }
  }

  return result;
}

// -------------------- Non-member utilities and IO --------------------

template <class T>
void swap(TDynamicMatrix<T>& lhs, TDynamicMatrix<T>& rhs) noexcept
{
  lhs.swap(rhs);
}

template <class T>
std::istream& operator>>(std::istream& istr, TDynamicMatrix<T>& m)
{
  for (size_t i = 0; i < m.GetSize(); i++)
  {
    istr >> m[i];
  }
  return istr;
}

template <class T>
std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix<T>& m)
{
  for (size_t i = 0; i < m.GetSize(); i++)
  {
    ostr << m[i] << std::endl;
  }
  return ostr;
}
