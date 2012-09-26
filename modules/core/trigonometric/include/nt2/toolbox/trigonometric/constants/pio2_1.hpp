//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_PIO2_1_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_PIO2_1_HPP_INCLUDED

#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    // 1.57079632673412561417e+00
    BOOST_SIMD_CONSTANT_REGISTER( Pio2_1, double
                                , 1, 0x3fc90f80
                                , 0x3FF921FB54400000ll
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Pio2_1, Pio2_1);
}

#endif
