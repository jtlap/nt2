//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SCALAR_CONSTANTS_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SCALAR_CONSTANTS_HPP_INCLUDED
// ////////////////////////////////////////////////////////////////////////////////
// // Make True and False
// ////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/constant/constant.hpp>
#include <nt2/sdk/constant/real.hpp>

namespace nt2 { namespace constants
{
  struct one_o_6_  {};
  struct mone_o_6_ {};
  struct one_o_120_{};
}  }

namespace nt2
{
  NT2_CONSTANT_IMPLEMENTATION(constants::one_o_6_      , Oneo_6  )
  NT2_CONSTANT_IMPLEMENTATION(constants::mone_o_6_     , Moneo_6 ) 
  NT2_CONSTANT_IMPLEMENTATION(constants::one_o_120_    , Oneo_120) 
}

NT2_CONSTANT_MAKE_REAL(constants::one_o_6_     , 0x3fc5555555555555ll, 0x3e2aaaab)
NT2_CONSTANT_MAKE_REAL(constants::mone_o_6_    , 0xbfc5555555555555ll, 0xbe2aaaab)
NT2_CONSTANT_MAKE_REAL(constants::one_o_120_   , 0x3f81111111111111ll, 0x3c088889)

#endif
