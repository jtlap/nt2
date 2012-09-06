//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_CONSTANTS_EXPX2C1_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_CONSTANTS_EXPX2C1_HPP_INCLUDED

#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    BOOST_SIMD_CONSTANT_REGISTER( Expx2c1, double
                                , 0, 0x42000000
                                , 0x4060000000000000ll
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Expx2c1, Expx2c1);
}

#endif
