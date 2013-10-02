//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_PUT_FIRST_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_PUT_FIRST_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief put_first generic tag

     Represents the put_first function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct put_first_ : ext::unspecified_<put_first_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<put_first_> parent;
    };
  }
  /*!
    returns a vector equal to a0 except that
    the first element of a0 is replaced  by its element of index a1 (scalar integer).
    the other elements are not modified.

    @par Semantic:

    For every parameters of types respectively T0, T1:

    @code
    T0 r = put_first(a0,a1);
    @endcode

    is similar to:

    @code
    T0 r = a0;
    a0[0] = a0[a1];
    @endcode

    @param a0

    @param a1

    @return a value of the same type as the first parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::put_first_, put_first, 2)
} }

#endif
