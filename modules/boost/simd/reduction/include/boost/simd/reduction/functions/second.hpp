//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_SECOND_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_SECOND_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief second generic tag

     Represents the second function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct second_ : ext::unspecified_<second_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<second_> parent;
    };
  }
  /*!
    returns the second element of the input vector.

    In scalar mode returns the first element!

    @par Semantic:

    For every parameter of type T0

    @code
    scalar<T0> r = second(a0);
    @endcode

    is similar to:

    @code
    scalar<T0> r = a0[1];
    @endcode

    @param a0

    @return a value of the scalar type associated to the parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::second_, second, 1)
} }
#endif

