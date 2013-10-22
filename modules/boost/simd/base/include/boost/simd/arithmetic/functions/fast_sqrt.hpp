//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_FAST_SQRT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_FAST_SQRT_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief fast_sqrt generic tag

      Represents the fast_sqrt function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct fast_sqrt_ : ext::elementwise_<fast_sqrt_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<fast_sqrt_> parent;
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::fast_sqrt_, fast_sqrt, 1)
} }

#endif
