//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_INPUT_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_INPUT_ITERATOR_HPP_INCLUDED

#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/memory/details/input_iterator_base.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

namespace boost { namespace simd
{
  /*!
    @brief Read-only SIMD iterator

    input_iterator adapt a pointer into a standard compliant iterator that
    traverses this memory block using SIMD registers.

    @tparam T Type pointed to by the iterator
    @tparam C Width of the SIMD register to use as iteration value. By default
              this value is equal to the optimal register cardinal for current
              architecture and type @c T.
  **/
  template<typename T, std::size_t C = meta::cardinal_of< pack<T> >::value >
  struct  input_iterator
        : details::input_iterator_base<T,C,tag::load_>
  {
    typedef details::input_iterator_base<T,C,tag::load_> parent;

    /// Default constructor
    input_iterator() : parent() {}

    /// Constructor from an aligned pointer
    explicit  input_iterator(T const* p) : parent(p) {}
  };

  ////////////////////////////////////////////////////////////////////////////////
  // simd::input_begin()/simd::input_end() functions wrap scalar begin/end
  // iterators for input_iterator.
  ////////////////////////////////////////////////////////////////////////////////
  template<typename Iterator> BOOST_FORCEINLINE
  input_iterator<typename std::iterator_traits<Iterator>::value_type>
  input_begin(Iterator p)
  {
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    return input_iterator<value_type>(&*p);
  }

  template<std::size_t C, typename Iterator> BOOST_FORCEINLINE
  input_iterator<typename std::iterator_traits<Iterator>::value_type, C>
  input_begin(Iterator p)
  {
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    return input_iterator<value_type, C>(&*p);
  }

  template<typename Iterator> BOOST_FORCEINLINE
  input_iterator<typename std::iterator_traits<Iterator>::value_type>
  input_end(Iterator p)
  {
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    return input_iterator<value_type>(&*(p-1) + 1);
  }

  template<std::size_t C, typename Iterator> BOOST_FORCEINLINE
  input_iterator<typename std::iterator_traits<Iterator>::value_type,C>
  input_end(Iterator p)
  {
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    return input_iterator<value_type, C>(&*(p-1) + 1);
  }
} }

#endif
