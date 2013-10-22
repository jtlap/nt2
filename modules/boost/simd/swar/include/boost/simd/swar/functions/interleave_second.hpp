//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_INTERLEAVE_SECOND_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_INTERLEAVE_SECOND_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd {
  namespace tag
  {
   /*!
     @brief interleave_second generic tag

     Represents the interleave_second function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct interleave_second_ : ext::unspecified_<interleave_second_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<interleave_second_> parent;
    };
  }

  /*!
    Computes a vector from a combination of the two inputs.

    @par Semantic:

    For every parameters of type T0:

    @code
    T0 r = interleave_second(a0,a1);
    @endcode

    is similar to:

    @code
      T0 r;
      size_t n = meta::cardinal_of<T0>::value;
      size_t  middle = meta::cardinal_of<T0>::value/2;
      for(size_t i=0;i<n/2;++i)
      {
        r[i*2]   = a0[middle];
        r[i*2+1] = a1[middle++];
      }
    @endcode

    @param a0

    @param a1

    @return a value of the same type as the parameters
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::interleave_second_, interleave_second, 2)

} }

#endif
