//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_HALFEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_HALFEPS_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Halfeps generic tag

     Represents the Halfeps constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Halfeps, double, 1
                                , 0x33800000, 0x3CA0000000000000ULL
                                );
  }
  /*!
    Constant Halfeps Eps/2
    @c 1 for integer types
     \f$= \2^{-53}\f$ for double
     \f$= \2^{-24}\f$ for float

    The value of this constant is type dependant. This means that for different
    types it does not represent the same mathematical number.

    @par Semantic:

    @code
    T r = Halfeps<T>();
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Halfeps, Halfeps)
} }

#include <boost/simd/constant/common.hpp>

#endif
