//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_SCALAR_CONSTANTS_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_SCALAR_CONSTANTS_HPP_INCLUDED

#include <nt2/toolbox/hyperbolic/constants.hpp>
#include <nt2/sdk/constant/constant.hpp>
#include <nt2/include/constants/real.hpp>

namespace nt2
{
  NT2_MAKE_STD_CONSTANT(Oneo_6  , 0x3fc5555555555555ll, 0x3e2aaaab, 0)
  NT2_MAKE_STD_CONSTANT(Moneo_6 , 0xbfc5555555555555ll, 0xbe2aaaab, 0)
  NT2_MAKE_STD_CONSTANT(Oneo_120, 0x3f81111111111111ll, 0x3c088889, 0)
}
#endif
