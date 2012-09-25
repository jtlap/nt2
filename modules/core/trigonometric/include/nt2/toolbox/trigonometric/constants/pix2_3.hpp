//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_PIX2_3_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_CONSTANTS_PIX2_3_HPP_INCLUDED

#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    // 12.56637061
    BOOST_SIMD_CONSTANT_REGISTER( Pix2_3, double
                                , 1, 0x31885a30
                                  , 0x3bc3198a2e037073//3b498a2e03707345
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Pix2_3, Pix2_3);
}

#endif
