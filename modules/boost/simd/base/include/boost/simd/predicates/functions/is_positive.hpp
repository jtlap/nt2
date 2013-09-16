//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREDICATES_FUNCTIONS_IS_POSITIVE_HPP_INCLUDED
#define BOOST_SIMD_PREDICATES_FUNCTIONS_IS_POSITIVE_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief is_positive generic tag

     Represents the is_positive function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct is_positive_ : ext::elementwise_<is_positive_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<is_positive_> parent;
    };}
  /*!
    Returns True if a0 is positive else False.
    \par
    This function differs from is_gtz from floating point argument,
    because Zero<A0>() is positive but not greater than zero,
    and Mzero<A0>() is not positive and not greater than zero,
    \par
    Mzero<A0>() is the floating point 'minus zero',
    i.e. all bits are zero but the sign bit.
    Such a value is treated as zero by ieee standards.

    @par Semantic:

    @code
    logical<T> r = is_positive(a0);
    @endcode

    is similar to:

    @code
    logical<T> r = ;
    @endcode

    @param a0

    @return a logical value
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_positive_, is_positive, 1)
} }

#endif

