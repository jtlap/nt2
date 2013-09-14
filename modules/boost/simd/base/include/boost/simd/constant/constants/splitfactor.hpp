//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_SPLITFACTOR_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_SPLITFACTOR_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Splitfactor generic tag

     Represents the Splitfactor constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Splitfactor, double, 0
                                , 0x46000000, 0x41A0000000000000ULL
                                );
  }
  /*!
    Constant Splitfactor is a constant used to split a floating number in two half,
    in floating point routines such two_add and two_prod to get extra precision.

    The value of this constant is type dependant. This means that for different
    types it does not represent the same mathematical number.

    @par Semantic:

    @code
    T r = Splitfactor<T>();
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Splitfactor, Splitfactor)
} }

#include <boost/simd/constant/common.hpp>

#endif
