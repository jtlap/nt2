//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_MAXFLINT_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_MAXFLINT_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Maxflint generic tag

     Represents the Maxflint constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Maxflint , double, 1
                                , 0x4b800000, 0x4340000000000000ll
                                );
  }
  /*!
    Constant Maxflint: the least integer value exactly representable in floating point numbers,
    equal to its integral successor (Maxflint+1)
    9007199254740992.0 for double and 16777216.0 for float

    The value of this constant is type dependant. This means that for different
    types it does not represent the same mathematical number.

    @par Semantic:

    @code
    T r = Maxflint<T>();
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Maxflint, Maxflint)
} }

#include <boost/simd/constant/common.hpp>

#endif
