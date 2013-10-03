//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_DEINTERLEAVE_FIRST_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_DEINTERLEAVE_FIRST_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd {
  namespace tag
  {
   /*!
     @brief deinterleave_first generic tag

     Represents the deinterleave_first function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct deinterleave_first_ : ext::unspecified_<deinterleave_first_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<deinterleave_first_> parent;
    };
  }

  /*!
    Computes a vector from a combination of the two inputs.

    @par Semantic:

    For every parameters of type T0
    @code
    T0 r = deinterleave_first(a0,a1);
    @endcode

    is similar to:

    @code
    T0 r;
    const std::size_t middle = meta::cardinal_of<T0>::value/2;
    for(std::size_t i=0,j=middle;i<middle;++i,++j)
    {
      r[i] = a0[i*2];
      r[j] = a1[i*2];
    }
    @endcode

    @param a0

    @param a1

    @return a value of the same type as the parameters
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::deinterleave_first_, deinterleave_first, 2)

} }

#endif
