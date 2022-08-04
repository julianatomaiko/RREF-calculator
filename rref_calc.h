// This header file utilizes template classes to convert a matrix to RREF form

#ifndef RREF_CALC_H_INCLUDED
#define RREF_CALC_H_INCLUDED

#include <iostream>
#include <algorithm>
#include <cstddef>
#include <cassert>

template<typename ItemType> struct matrix
{
  typedef typename ItemType::index_type index_type;

  typedef typename ItemType::value_type value_type;

  static index_type min_row(ItemType const& A)
  {
     return A.min_row();
  }

  static index_type max_row(ItemType const& A)
  {
     return A.max_row();
  }

  static index_type min_col(ItemType const& A)
  {
     return A.min_col();
  }

  static index_type max_col(ItemType const& A)
  {
     return A.max_col();
  }

  static value_type& element(ItemType& A, index_type i, index_type k)
  {
     return A(i,k);
  }

  static value_type element(ItemType const& A, index_type i, index_type k)
  {
     return A(i,k);
  }
};

template<typename T, std::size_t rows, std::size_t cols>
 struct matrix<T[rows][cols]>
{
  typedef std::size_t index_type;

  typedef T value_type;
  static index_type min_row(T const (&)[rows][cols])
  {
     return 0;
  }

  static index_type max_row(T const (&)[rows][cols])
  {
     return rows - 1;
  }
  static index_type min_col(T const (&)[rows][cols])
  {
     return 0;
  }
  static index_type max_col(T const (&)[rows][cols])
  {
     return cols - 1;
  }
  static value_type& element(T (&A)[rows][cols], index_type i, index_type k)
  {
     return A[i][k];
  }
  static value_type element(T const (&A)[rows][cols], index_type i, index_type k)
  {
     return A[i][k];
  }
};

// swaps rows i and k
template<typename ItemType>
 void swap_rows(ItemType& A, typename matrix<ItemType>::index_type i,
                typename matrix<ItemType>::index_type k)
{
  matrix<ItemType> m;
  typedef typename matrix<ItemType>::index_type index_type;

  assert(m.min_row(A) <= i);
  assert(i <= m.max_row(A));

  assert(m.min_row(A) <= k);
  assert(k <= m.max_row(A));

  for (index_type col = m.min_col(A); col <= m.max_col(A); ++col)
    std::swap(m.element(A, i, col), m.element(A, k, col));
}

// divides row i by v
template<typename ItemType>
 void divide_row(ItemType& A, typename matrix<ItemType>::index_type i,
                  typename matrix<ItemType>::value_type v)
{
  matrix<ItemType> m;
  typedef typename matrix<ItemType>::index_type index_type;

  assert(m.min_row(A) <= i);
  assert(i <= m.max_row(A));

  assert(v != 0);

  for (index_type col = m.min_col(A); col <= m.max_col(A); ++col)
    m.element(A, i, col) /= v;
}

// adds v times row k to row i
template<typename ItemType>
 void add_rows(ItemType& A, typename matrix<ItemType>::index_type i,
                  typename matrix<ItemType>::index_type k,
                  typename matrix<ItemType>::value_type v)
{
  matrix<ItemType> m;
  typedef typename matrix<ItemType>::index_type index_type;

  assert(m.min_row(A) <= i);
  assert(i <= m.max_row(A));

  assert(m.min_row(A) <= k);
  assert(k <= m.max_row(A));

  for (index_type col = m.min_col(A); col <= m.max_col(A); ++col)
  {
     m.element(A, i, col) += v * m.element(A, k, col);
  }
}

// converts matrix A to RREF form
template<typename ItemType>
 void rref_form(ItemType& A)
{
  matrix<ItemType> m;
  typedef typename matrix<ItemType>::index_type index_type;

  index_type lead = m.min_row(A);

  for (index_type row = m.min_row(A); row <= m.max_row(A); ++row)
  {
    if (lead > m.max_col(A))
    {
       return;
    }
    index_type i = row;
    while (m.element(A, i, lead) == 0)
    {
      ++i;
      if (i > m.max_row(A))
      {
        i = row;
        ++lead;
        if (lead > m.max_col(A))
        {
           return;
        }
      }
    }
    swap_rows(A, i, row);
    divide_row(A, row, m.element(A, row, lead));
    for (i = m.min_row(A); i <= m.max_row(A); ++i)
    {
      if (i != row)
      {
         add_rows(A, i, row, -m.element(A, i, lead));
      }
    }
  }
}
#endif // RREF_CALC_H_INCLUDED
