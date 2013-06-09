//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_MEDIUM_PI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_MEDIUM_PI_HPP_INCLUDED

#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    BOOST_SIMD_CONSTANT_REGISTER( Medium_pi, double
                                , 201, 0x43490fdb       //2^6*pi
                                , 0x412921fb54442d18ll  //2^18*pi
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Medium_pi, Medium_pi);
}

#endif
