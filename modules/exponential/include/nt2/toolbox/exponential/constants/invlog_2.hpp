//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_CONSTANTS_INVLOG_2_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_CONSTANTS_INVLOG_2_HPP_INCLUDED

#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    BOOST_SIMD_CONSTANT_REGISTER( Invlog_2, double
                                , 1, 0x3fb8aa3b
                                , 0x3ff71547652b82feLL
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Invlog_2, Invlog_2);
}

#endif
