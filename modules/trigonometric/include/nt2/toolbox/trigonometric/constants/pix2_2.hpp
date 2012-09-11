//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_PIX2_2_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_PIX2_2_HPP_INCLUDED

#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    // 12.56637061
    BOOST_SIMD_CONSTANT_REGISTER( Pix2_2, double
                                , 1, 0x38daa000
                                , 0x3df0b4611a600000ll
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Pix2_2, Pix2_2);
}

#endif
// ans =

// 401921fb54400000


// ans =

// 3df0b4611a600000


// ans =

// 3bc3198a2e037073
