//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_ILOG10_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_ILOG10_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  ilog10 generic tag

      Represents the ilog10 function in generic contexts.

      @par Models:
      Ilog10erarchy
    **/
    struct ilog10_ : ext::elementwise_<ilog10_>
    {
      /// @brief Parent ilog10erarchy
      typedef ext::elementwise_<ilog10_> parent;
    };
  }
  /*!
    Returns the integer part of the base 2
    logarithm of the input.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_integer<T> r = ilog10(x);
    @endcode

    The code is similar to

    @code
    as_integer<T> r = toints(log10(x));
    @endcode

    @param  a0

    @return      a value of the integer
                 type associated to the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::ilog10_, ilog10, 1)
} }

#endif
