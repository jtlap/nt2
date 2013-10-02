//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SPLATTED_FIRST_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SPLATTED_FIRST_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief splatted_first generic tag

     Represents the splatted_first function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct splatted_first_ : ext::unspecified_<splatted_first_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<splatted_first_> parent;
    };
  }
  /*!
    returns the first element of a0 splatted in a vector

    @par Semantic:

    For every parameter of type T0

    @code
    T0 r = splatted_first(a0);
    @endcode

    is similar to:

    @code
    for(int i=0;i<Type::static_size;++i)
      x[i] = a0[0];
    @endcode

    @param a0

    @return a value of the same type as the parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::splatted_first_, splatted_first, 1)
} }

#endif
