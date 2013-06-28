//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_DYNARRAY_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_DYNARRAY_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/utility/swap.hpp>
#include <boost/detail/workaround.hpp>
#include <algorithm>
#include <iterator>
#include <cstddef>

namespace boost { namespace simd
{
  /*!
    @brief Runtime sized array

    Similar to std::vector, but without the ability to change the size and
    without allocators.
    See C++14 dynarray proposal.

    @tparam T     Type of the stored element
  **/
  template<class T>
  struct dynarray
       : boost::iterator_range<T*>
  {
    dynarray(std::size_t n)
    {
      T* ptr = new T[n];
      *static_cast<boost::iterator_range<T*>*>(this) = boost::iterator_range<T*>(ptr, ptr+n);
    }

    dynarray(dynarray const& other)
    {
      T* ptr = new T[other.size()];
      *static_cast<boost::iterator_range<T*>*>(this) = boost::iterator_range<T*>(ptr, ptr+other.size());
      #ifndef BOOST_NO_EXCEPTIONS
      try
      {
      #endif

      #if BOOST_WORKAROUND(BOOST_MSVC, >= 1400) && BOOST_WORKAROUND(BOOST_MSVC, < 1600)
        stdext::unchecked_copy(other.begin(), other.end(), ptr);
      #elif BOOST_WORKAROUND(BOOST_MSVC, > 1500)
        std::copy(other.begin(), other.end(), stdext::make_unchecked_array_iterator(ptr));
      #else
        std::copy(other.begin(), other.end(), ptr);
      #endif

      #ifndef BOOST_NO_EXCEPTIONS
      }
      catch(...)
      {
        delete[] ptr;
        throw;
      }
      #endif
    }

    dynarray& operator=(dynarray other)
    {
      boost::swap(static_cast<boost::iterator_range<T*>&>(*this), static_cast<boost::iterator_range<T*>&>(other));
    }

    // cast because of boost bug #8061
    std::size_t size() const
    {
      return (std::size_t)static_cast<boost::iterator_range<T*> const*>(this)->size();
    }

    ~dynarray()
    {
      delete[] this->begin();
    }
  };
} }

#endif
