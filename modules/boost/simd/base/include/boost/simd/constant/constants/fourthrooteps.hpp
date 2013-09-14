//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_FOURTHROOTEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_FOURTHROOTEPS_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Fourthrooteps generic tag

     Represents the Fourthrooteps constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Fourthrooteps,double,1
                                , 0x3C9837F0,0x3F20000000000000ULL
                                );
  }
  /*!
    Constant Fourthrooteps \f$\root{eps, 4}\f$
    the 4th root of constant @c Eps
    @c 1 for integer types
     \f$ 2^{-13}\f$ for double
     \f$ 2^{-5.75}\f$ for float

    The value of this constant is type dependant. This means that for different
    types it does not represent the same mathematical number.

    @par Semantic:

    @code
    T r = Fourthrooteps<T>();
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Fourthrooteps, Fourthrooteps)
} }

#include <boost/simd/constant/common.hpp>

#endif
