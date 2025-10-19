#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <utility> // for std::swap
#include <cstddef> // for size_t

static constexpr size_t MAX_VECTOR_SIZE = 100000000;

template<typename T>
class TDynamicVector
{
protected:
  size_t size;
  T* pMem;

public:
  TDynamicVector(size_t sz = 1);
  TDynamicVector(T* arr, size_t sz);
  TDynamicVector(const TDynamicVector<T>& v);
  TDynamicVector(TDynamicVector<T>&& v) noexcept;
  ~TDynamicVector();

  TDynamicVector<T>& operator=(const TDynamicVector<T>& v);
  TDynamicVector<T>& operator=(TDynamicVector<T>&& v) noexcept;

  size_t GetSize() const noexcept
  {
    return size;
  }

  T& operator[](size_t ind) noexcept
  {
    return pMem[ind];
  }

  const T& operator[](size_t ind) const noexcept
  {
    return pMem[ind];
  }

  T& at(size_t ind)
  {
    if (ind >= size)
    {
      throw std::out_of_range("Index out of range");
    }
    return pMem[ind];
  }

  const T& at(size_t ind) const
  {
    if (ind >= size)
    {
      throw std::out_of_range("Index out of range");
    }
    return pMem[ind];
  }

  bool operator==(const TDynamicVector<T>& v) const noexcept;
  bool operator!=(const TDynamicVector<T>& v) const noexcept;

  // scalar ops
  TDynamicVector<T> operator+(const T& val) const;
  TDynamicVector<T> operator-(const T& val) const;
  TDynamicVector<T> operator*(const T& val) const;

  // vector ops
  TDynamicVector<T> operator+(const TDynamicVector<T>& v) const;
  TDynamicVector<T> operator-(const TDynamicVector<T>& v) const;
  T operator*(const TDynamicVector<T>& v) const noexcept(noexcept(T()));

  // utility swap (member-level convenience)
  void swap(TDynamicVector<T>& other) noexcept
  {
    std::swap(this->size, other.size);
    std::swap(this->pMem, other.pMem);
  }
};

// -------------------- Implementations --------------------

template <class T>
TDynamicVector<T>::TDynamicVector(size_t sz) : size(sz), pMem(nullptr)
{
  if (sz == 0)
  {
    throw std::out_of_range("Vector size should be greater than zero");
  }

  if (sz > MAX_VECTOR_SIZE)
  {
    throw std::length_error("Vector size exceeds maximum allowed size");
  }

  pMem = new T[sz]();
}

template <class T>
TDynamicVector<T>::TDynamicVector(T* arr, size_t sz) : size(sz), pMem(nullptr)
{
  if (arr == nullptr)
  {
    throw std::invalid_argument("Input array cannot be nullptr");
  }

  if (sz == 0)
  {
    throw std::out_of_range("Vector size should be greater than zero");
  }

  if (sz > MAX_VECTOR_SIZE)
  {
    throw std::length_error("Vector size exceeds maximum allowed size");
  }

  pMem = new T[sz];
  for (size_t i = 0; i < sz; i++)
  {
    pMem[i] = arr[i];
  }
}

template <class T>
TDynamicVector<T>::TDynamicVector(const TDynamicVector<T>& v) : size(v.size), pMem(nullptr)
{
  pMem = new T[size];
  for (size_t i = 0; i < size; i++)
  {
    pMem[i] = v.pMem[i];
  }
}

template <class T>
TDynamicVector<T>::TDynamicVector(TDynamicVector<T>&& v) noexcept : size(0), pMem(nullptr)
{
  this->size = v.size;
  this->pMem = v.pMem;
  v.size = 0;
  v.pMem = nullptr;
}

template <class T>
TDynamicVector<T>::~TDynamicVector()
{
  if (pMem != nullptr)
  {
    delete[] pMem;
    pMem = nullptr;
  }
}

// copy-and-swap for strong exception safety
template <class T>
TDynamicVector<T>& TDynamicVector<T>::operator=(const TDynamicVector<T>& v)
{
  if (this != &v)
  {
    TDynamicVector<T> tmp(v); // copy
    this->swap(tmp);          // swap with the copy
  }
  return *this;
}

template <class T>
TDynamicVector<T>& TDynamicVector<T>::operator=(TDynamicVector<T>&& v) noexcept
{
  if (this != &v)
  {
    delete[] this->pMem;
    this->size = v.size;
    this->pMem = v.pMem;
    v.size = 0;
    v.pMem = nullptr;
  }
  return *this;
}

template <class T>
bool TDynamicVector<T>::operator==(const TDynamicVector<T>& v) const noexcept
{
  if (this->size != v.size)
  {
    return false;
  }

  for (size_t i = 0; i < this->size; i++)
  {
    if (this->pMem[i] != v.pMem[i])
    {
      return false;
    }
  }

  return true;
}

template <class T>
bool TDynamicVector<T>::operator!=(const TDynamicVector<T>& v) const noexcept
{
  return !(*this == v);
}

// scalar ops
template <class T>
TDynamicVector<T> TDynamicVector<T>::operator+(const T& val) const
{
  TDynamicVector<T> result(this->size);

  for (size_t i = 0; i < this->size; i++)
  {
    result.pMem[i] = this->pMem[i] + val;
  }

  return result;
}

template <class T>
TDynamicVector<T> TDynamicVector<T>::operator-(const T& val) const
{
  TDynamicVector<T> result(this->size);

  for (size_t i = 0; i < this->size; i++)
  {
    result.pMem[i] = this->pMem[i] - val;
  }

  return result;
}

template <class T>
TDynamicVector<T> TDynamicVector<T>::operator*(const T& val) const
{
  TDynamicVector<T> result(this->size);

  for (size_t i = 0; i < this->size; i++)
  {
    result.pMem[i] = this->pMem[i] * val;
  }

  return result;
}

// vector ops
template <class T>
TDynamicVector<T> TDynamicVector<T>::operator+(const TDynamicVector<T>& v) const
{
  if (this->size != v.size)
  {
    throw std::invalid_argument("Vectors must be of the same size for addition");
  }

  TDynamicVector<T> result(this->size);

  for (size_t i = 0; i < this->size; i++)
  {
    result.pMem[i] = this->pMem[i] + v.pMem[i];
  }

  return result;
}

template <class T>
TDynamicVector<T> TDynamicVector<T>::operator-(const TDynamicVector<T>& v) const
{
  if (this->size != v.size)
  {
    throw std::invalid_argument("Vectors must be of the same size for subtraction");
  }

  TDynamicVector<T> result(this->size);

  for (size_t i = 0; i < this->size; i++)
  {
    result.pMem[i] = this->pMem[i] - v.pMem[i];
  }

  return result;
}

template <class T>
T TDynamicVector<T>::operator*(const TDynamicVector<T>& v) const noexcept(noexcept(T()))
{
  if (this->size != v.size)
  {
    throw std::invalid_argument("Vectors must be of the same size for dot product");
  }

  T result = T();

  for (size_t i = 0; i < this->size; i++)
  {
    result += this->pMem[i] * v.pMem[i];
  }

  return result;
}

// -------------------- Non-member utilities and IO --------------------

// swap non-member (ADL-friendly)
template <class T>
void swap(TDynamicVector<T>& lhs, TDynamicVector<T>& rhs) noexcept
{
  lhs.swap(rhs);
}

// stream operators as non-member templates
template <class T>
std::istream& operator>>(std::istream& istr, TDynamicVector<T>& v)
{
  for (size_t i = 0; i < v.GetSize(); i++)
  {
    istr >> v[i];
  }
  return istr;
}

template <class T>
std::ostream& operator<<(std::ostream& ostr, const TDynamicVector<T>& v)
{
  ostr << '(';

  if (v.GetSize() >= 1)
  {
    ostr << v[0];
  }

  for (size_t i = 1; i < v.GetSize(); i++)
  {
    ostr << ", " << v[i];
  }

  ostr << ')';
  return ostr;
}
