//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_THIRDROOTEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_THIRDROOTEPS_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Thirdrooteps generic tag

     Represents the Thirdrooteps constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Thirdrooteps, double, 1
                                , 0x3BA14518, 0x3ED965FEA53D6E42ULL
                                );
  }
  /*!
    Constant Thirdrooteps
    the cubic root of constant Eps
    @c 1 for integer types
    @c 6.055454452393343e-06 for double
    @c 4.9215667e-03 for float

    The value of this constant is type dependant. This means that for different
    types it does not represent the same mathematical number.

    @par Semantic:

    @code
    T r = Thirdrooteps<T>();
    @endcode

  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Thirdrooteps, Thirdrooteps)
} }

#include <boost/simd/constant/common.hpp>

#endif
