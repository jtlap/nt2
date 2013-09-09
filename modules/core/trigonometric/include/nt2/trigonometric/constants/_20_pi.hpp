//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_20_PI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_20_PI_HPP_INCLUDED

#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    BOOST_SIMD_CONSTANT_REGISTER( _20_pi, double
                                , 63, 0x427b53d1       //20*pi
                                , 0x404f6a7a2955385ell  //20*pi
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::_20_pi, _20_pi);
}

#endif
