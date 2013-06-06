//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ALIGNED_INPUT_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALIGNED_INPUT_ITERATOR_HPP_INCLUDED

#include <boost/simd/include/functions/aligned_load.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/memory/details/input_iterator_base.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd
{
  /*!
    @brief Read-only SIMD iterator

    aligned_input_iterator adapt a pointer to an aligned memory block into a
    standard compliant iterator that traverses this memory block using SIMD
    registers.

    @tparam T Type pointed to by the iterator
    @tparam C Width of the SIMD register to use as iteration value. By default
              this value is equal to the optimal register cardinal for current
              architecture and type @c T.
  **/
  template<typename T, std::size_t C = meta::cardinal_of< pack<T> >::value >
  struct  aligned_input_iterator
        : details::input_iterator_base<T,C,tag::aligned_load_>
  {
    typedef details::input_iterator_base<T,C,tag::aligned_load_> parent;

    /// Default constructor
    aligned_input_iterator() : parent() {}

    /// Constructor from an aligned pointer
    explicit  aligned_input_iterator(T const* p) : parent(p)
    {
      BOOST_ASSERT_MSG
      ( boost::simd::is_aligned(p, C*sizeof(T))
      , "The constructor of iterator<T,C> has been called on a pointer "
        "which alignment is not compatible with the current SIMD extension."
      );
    }
  };

  /*!
    @brief
  **/
  template<typename Iterator> BOOST_FORCEINLINE
  aligned_input_iterator<typename std::iterator_traits<Iterator>::value_type>
  aligned_input_begin(Iterator p)
  {
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    return aligned_input_iterator<value_type>(&*p);
  }

  /// @overload
  template<std::size_t C, typename Iterator> BOOST_FORCEINLINE
  aligned_input_iterator<typename std::iterator_traits<Iterator>::value_type, C>
  aligned_input_begin(Iterator p)
  {
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    return aligned_input_iterator<value_type, C>(&*p);
  }

  template<typename Iterator> BOOST_FORCEINLINE
  aligned_input_iterator<typename std::iterator_traits<Iterator>::value_type>
  aligned_input_end(Iterator p)
  {
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    return aligned_input_iterator<value_type>(&*(p-1) + 1);
  }

  /// @overload
  template<std::size_t C, typename Iterator> BOOST_FORCEINLINE
  aligned_input_iterator<typename std::iterator_traits<Iterator>::value_type,C>
  aligned_input_end(Iterator p)
  {
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    return aligned_input_iterator<value_type, C>(&*(p-1) + 1);
  }
} }

#endif
