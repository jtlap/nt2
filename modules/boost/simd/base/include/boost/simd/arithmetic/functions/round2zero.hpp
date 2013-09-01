//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_ROUND2ZERO_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_ROUND2ZERO_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  round2zero generic tag

      Represents the round2zero function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct round2zero_ : ext::elementwise_<round2zero_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<round2zero_> parent;
    };
  }
  /*!
    Computes the round2zeroed to nearest integer down to 0 (truncate)

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = round2zero(x);
    @endcode

    Returns the nearest integer to x in the direction of 0.

    @par Note:

    down to 0 means that half integer values are rounded to the nearest
    integer of least absolute value

    @param  a0

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::round2zero_, round2zero, 1)
} }

#endif
