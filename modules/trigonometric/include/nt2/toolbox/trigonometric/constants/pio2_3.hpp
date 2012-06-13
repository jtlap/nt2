//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_PIO2_3_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_PIO2_3_HPP_INCLUDED

#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    // 2.02226624871116645580e-21
    BOOST_SIMD_CONSTANT_REGISTER( Pio2_3, double
                                , 0, 0x2e85a300
                                , 0x3BA3198A2E000000ll
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Pio2_3, Pio2_3);
}

#endif
