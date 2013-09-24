//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_FAST_DIVIDES_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_FAST_DIVIDES_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief load generic tag

      Represents the load function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct fast_divides_ : ext::elementwise_<fast_divides_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<fast_divides_> parent;
    };
  }

  /*!
    @brief Approximate division

    Performs the division between two values using an approximate algorithm
    whenever possible. Contrary to divides, fast_divides does not make any
    provision for handling inputs or outputs.

    @par Semantic:

    For any values @c x and @c y of type @c T,

    @code
    T r = fast_divides(x,y)
    @endcode

    is equivalent to

    - if  @c T is a floating point type:
    @code
    T r = x * fast_rec(y)
    @endcode

    - if  @c T is a integral type:
    @code
    T r = x / y
    @endcode

    Precision of result is around 0.5 ULPs.

    @par Alias:

    fast_div, fast_rdiv

    @param a0
    @param a1

    @return An approximate value of a0/a1
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::fast_divides_ , fast_divides  , 2)

  /// INTERNAL ONLY
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::fast_divides_ , fast_div      , 2)

  /// INTERNAL ONLY
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::fast_divides_ , fast_rdiv     , 2)
} }

#endif
