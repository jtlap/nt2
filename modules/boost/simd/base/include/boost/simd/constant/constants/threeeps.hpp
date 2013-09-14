//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_THREEEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_THREEEPS_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Threeeps generic tag

     Represents the Threeeps constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Threeeps, double, 3
                                , 0x34C00000, 0x3CC8000000000000ULL
                                );
  }
  /*!
    Constant Threeeps = 3\f$\times\f$ Eps
     3 for integer types
     6.661338147750939e-16 for double
     3.5762787e-07 for float
    \par
    The value of this constant is type dependant. This means that for different
    types it does not represent the same mathematical number.

    @par Semantic:

    @code
    T r = Threeeps<T>();
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Threeeps, Threeeps)
} }

#include <boost/simd/constant/common.hpp>

#endif
