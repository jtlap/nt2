//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_FIRST_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_FIRST_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief first generic tag

     Represents the first function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct first_ : ext::unspecified_<first_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<first_> parent;
    };
  }
  /*!
    Returns the first element of the input vector.

    @par Semantic:

    For every parameter of type T0

    @code
    scalar_of<T0> r = first(a0);
    @endcode

    is similar to:

    @code
    T0 r = a0[0];
    @endcode

    @param a0

    @return a value of the scalar type associated to the parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::first_, first, 1)
} }
#endif
