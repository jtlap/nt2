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
#include <boost/dispatch/preprocessor/repeat.hpp>
#include <boost/throw_exception.hpp>
#include <boost/assert.hpp>
#include <boost/swap.hpp>
#include <stdexcept>

namespace boost{ namespace simd{ namespace memory{

  template<class T, std::size_t N, std::size_t Align>
  struct aligned_array_data
  {
    BOOST_SIMD_ALIGNED_TYPE(T) data[N];
  };

  #define M0(z,n,t)                                                            \
  template<class T, std::size_t N>                                             \
  struct aligned_array_data<T, N, n>                                           \
  {                                                                            \
    BOOST_SIMD_ALIGN_ON(n) T data[N];                                          \
  };                                                                           \
  /**/

  BOOST_DISPATCH_PP_REPEAT_POWER_OF_2(M0,~)
  #undef M0

  template<class T, std::size_t N, std::size_t Align>
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
    iterator        begin()       { return this->data; }
    const_iterator  begin() const { return this->data; }
    const_iterator cbegin() const { return this->data; }
    
    iterator        end()       { return this->data+N; }
    const_iterator  end() const { return this->data+N; }
    const_iterator cend() const { return this->data+N; }

    // operator[]
    reference operator[](size_type i) 
    { 
        BOOST_ASSERT_MSG( i < N, "out of range" );
        return this->data[i];
    }
    
    const_reference operator[](size_type i) const 
    {     
        BOOST_ASSERT_MSG( i < N, "out of range" );
        return this->data[i]; 
    }

    // at() with range check
    reference       at(size_type i)       { rangecheck(i); return this->data[i]; }
    const_reference at(size_type i) const { rangecheck(i); return this->data[i]; }

    // front() and back()
    reference       front()       { return this->data[0]; }
    const_reference front() const { return this->data[0]; }
    reference       back()        { return this->data[N-1]; }
    const_reference back()  const { return this->data[N-1]; }

    // size is constant
    static size_type size()     { return N;     }
    static bool      empty()    { return false; }
    static size_type max_size() { return N;     }
    enum { static_size = N };

    // swap (note: linear complexity)
    void swap (aligned_array<T,N,Align>& y) 
    {
      for (size_type i = 0; i < N; ++i) boost::swap(this->data[i],y.data[i]);
    }

    // direct access to data (read-only)
    const T* data() const { return this->data; }
    T*       data()       { return this->data; }

    // use array as C array (direct read/write access to data)
    T* c_array() { return this->data; }

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

} } }

#endif 
