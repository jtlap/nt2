//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_SMALLESTPOSVAL_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_SMALLESTPOSVAL_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Smallestposval generic tag

     Represents the Smallestposval constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Smallestposval , double, 1
                                , 0x00800000, 0x0010000000000000ULL
                                );

  }
  /*!
    Constant Smallestposval : the least non zero, non denormal, positive value of floating point numbers,
    i.e. 2.225073858507201e-308 for double and  1.1754944e-38 for float

    @par Semantic:

    @code
    T r = Smallestposval<T>();
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Smallestposval, Smallestposval)
} }

#include <boost/simd/constant/common.hpp>

#endif
