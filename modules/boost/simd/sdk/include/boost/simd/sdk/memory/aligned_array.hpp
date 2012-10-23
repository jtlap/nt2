//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_MEMORY_ALIGNED_ARRAY_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_ALIGNED_ARRAY_HPP_INCLUDED

#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/sdk/simd/preprocessor/repeat.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/comparison/less_equal.hpp>

#include <boost/throw_exception.hpp>
#include <boost/assert.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/swap.hpp>
#include <stdexcept>
#include <iterator>

namespace boost { namespace simd
{
  namespace memory
  {
    template<class T, std::size_t N, std::size_t Align>
    struct aligned_array_data
    {
      BOOST_MPL_ASSERT_MSG( (sizeof(T) == 0)
                          , NON_SUPPORTED_ALIGNMENT_FOR_ARRAY
                          , (aligned_array_data)
                          );
    };

    #define M0t(z,n,t)                                                         \
    template<class T, std::size_t N>                                           \
    struct aligned_array_data<T, N, n>                                         \
    {                                                                          \
      BOOST_SIMD_ALIGN_ON(n) T data_[N];                                       \
    };                                                                         \
    /**/
    #define M0f(z,n,t)
    #define M0(z,n,t)                                                          \
    BOOST_PP_IF(                                                               \
      BOOST_PP_LESS_EQUAL(n, BOOST_SIMD_CONFIG_ALIGNMENT)                      \
    , M0t, M0f                                                                 \
    )(z,n,t)                                                                   \
    /**/
    BOOST_SIMD_PP_REPEAT_POWER_OF_2(M0,~)
    #undef M0
    #undef M0f
    #undef M0t

    template<class T, std::size_t N, std::size_t Align=BOOST_SIMD_CONFIG_ALIGNMENT>
    struct aligned_array : aligned_array_data<T,N,Align>
    {
      typedef T              value_type;
      typedef T*             iterator;
      typedef const T*       const_iterator;
      typedef T&             reference;
      typedef const T&       const_reference;
      typedef std::size_t    size_type;
      typedef std::ptrdiff_t difference_type;

      // iterator support
      iterator        begin()       { return this->data_; }
      const_iterator  begin() const { return this->data_; }
      const_iterator cbegin() const { return this->data_; }

      iterator        end()       { return this->data_+N; }
      const_iterator  end() const { return this->data_+N; }
      const_iterator cend() const { return this->data_+N; }

      typedef std::reverse_iterator<iterator> reverse_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

      reverse_iterator rbegin() { return reverse_iterator(end()); }
      const_reverse_iterator rbegin()  const { return const_reverse_iterator(end()); }
      const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); }

      reverse_iterator       rend()       { return reverse_iterator(begin()); }
      const_reverse_iterator rend()  const { return const_reverse_iterator(begin()); }
      const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }

      // operator[]
      reference operator[](size_type i)
      {
          BOOST_ASSERT_MSG( i < N, "out of range" );
          return this->data_[i];
      }

      const_reference operator[](size_type i) const
      {
          BOOST_ASSERT_MSG( i < N, "out of range" );
          return this->data_[i];
      }

      // at() with range check
      reference       at(size_type i)       { rangecheck(i); return this->data_[i]; }
      const_reference at(size_type i) const { rangecheck(i); return this->data_[i]; }

      // front() and back()
      reference       front()       { return this->data_[0]; }
      const_reference front() const { return this->data_[0]; }
      reference       back()        { return this->data_[N-1]; }
      const_reference back()  const { return this->data_[N-1]; }

      // size is constant
      static size_type size()     { return N;     }
      static bool      empty()    { return false; }
      static size_type max_size() { return N;     }
      enum { static_size = N };

      // swap (note: linear complexity)
      void swap (aligned_array<T,N,Align>& y)
      {
        for (size_type i = 0; i < N; ++i) boost::swap(this->data_[i],y.data_[i]);
      }

      // direct access to data (read-only)
      const T* data() const { return this->data_; }
      T*       data()       { return this->data_; }

      // use array as C array (direct read/write access to data)
      T* c_array() { return this->data_; }

      // assignment with type conversion
      template <typename T2>
      aligned_array<T,N,Align>& operator= (const aligned_array<T2,N,Align>& rhs)
      {
        std::copy(rhs.begin(),rhs.end(), begin());
        return *this;
      }

      // assign one value to all elements
      void assign (const T& value) { fill ( value ); }    // A synonym for fill
      void fill   (const T& value) { std::fill_n(begin(),size(),value); }

      // check range (may be private because it is static)
      static void rangecheck (size_type i)
      {
        if (i >= size())
        {
          std::out_of_range e("array<>: index out of range");
          boost::throw_exception(e);
        }
      }
    };
  }
} }

#endif
