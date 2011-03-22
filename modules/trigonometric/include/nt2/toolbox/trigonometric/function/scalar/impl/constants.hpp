/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_IMPL_CONSTANTS_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_IMPL_CONSTANTS_HPP_INCLUDED
// ////////////////////////////////////////////////////////////////////////////////
// // Make True and False
// ////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/constant/constant.hpp>
#include <nt2/sdk/constant/real.hpp>

namespace nt2 { namespace constants
{
  struct pi_o_2_   {};
  struct pi_o_4_   {};
  struct pi_x_4_   {};
  struct pi_x_2_   {};
  struct sqrt_2pi_ {};
  struct _4_o_pi_  {};
  struct _2_o_pi_  {};
  struct sqrt_2_o_pi {};
  struct three_pi_o_4 {};
  struct inv_pi_   {};
  struct pi_o_180_ {};
  struct one_o_180_{};
  struct deg_in_rad_  {};
  struct rad_in_deg_  {};
  struct rad_in_deg_r_{};
  
}  }

namespace nt2
{
  NT2_CONSTANT_IMPLEMENTATION(constants::pi_o_2_       , Pio_2   )
  NT2_CONSTANT_IMPLEMENTATION(constants::pi_o_4_       , Pio_4   )
  NT2_CONSTANT_IMPLEMENTATION(constants::pi_x_4_       , Pix_4   )
  NT2_CONSTANT_IMPLEMENTATION(constants::pi_x_2_       , Pix_2   )
  NT2_CONSTANT_IMPLEMENTATION(constants::_4_o_pi_      , Fouropi )
  NT2_CONSTANT_IMPLEMENTATION(constants::inv_pi_       , Invpi   )
  NT2_CONSTANT_IMPLEMENTATION(constants::pi_o_180_     , Pio_180 )
  NT2_CONSTANT_IMPLEMENTATION(constants::one_o_180_    , Oneo_180)
  NT2_CONSTANT_IMPLEMENTATION(constants::deg_in_rad_   , Deginrad )
  NT2_CONSTANT_IMPLEMENTATION(constants::rad_in_deg_   , Radindeg )
  NT2_CONSTANT_IMPLEMENTATION(constants::rad_in_deg_r_ , Radindegr)
  NT2_CONSTANT_IMPLEMENTATION(constants::sqrt_2pi_     , Sqrt_2pi)
  NT2_CONSTANT_IMPLEMENTATION(constants::_2_o_pi_      , Twoopi) 
  NT2_CONSTANT_IMPLEMENTATION(constants::sqrt_2_o_pi   , Sqrt_2opi)
  NT2_CONSTANT_IMPLEMENTATION(constants::three_pi_o_4  , Threepio_4)
}

NT2_CONSTANT_MAKE_REAL(constants::pi_o_2_      , 0x3ff921fb54442d18LL, 0x3fc90fdb)
NT2_CONSTANT_MAKE_REAL(constants::pi_o_4_      , 0x3fe921fb54442d18LL, 0x3f490fdb)
NT2_CONSTANT_MAKE_REAL(constants::pi_x_4_      , 0x402921fb54442d18LL, 0x41490fdb)
NT2_CONSTANT_MAKE_REAL(constants::pi_x_2_      , 0x401921fb54442d18LL, 0x40c90fdb)
NT2_CONSTANT_MAKE_REAL(constants::_4_o_pi_     , 0x3ff45f306dc9c883LL, 0x3fa2f983)
NT2_CONSTANT_MAKE_REAL(constants::inv_pi_      , 0x3fd45f306dc9c883LL, 0x3ea2f983)
NT2_CONSTANT_MAKE_REAL(constants::pi_o_180_    , 0x3f91df46a2529d3all, 0x3c8efa35)
NT2_CONSTANT_MAKE_REAL(constants::one_o_180_   , 0x3f76c16c16c16c17ll, 0x3bb60b61)
NT2_CONSTANT_MAKE_REAL(constants::deg_in_rad_  , 0x3f91df46a2529d39LL, 0x3c8efa35)
NT2_CONSTANT_MAKE_REAL(constants::rad_in_deg_  , 0x404ca5dc1a63c1f8LL, 0x42652ee1)
NT2_CONSTANT_MAKE_REAL(constants::rad_in_deg_r_, 0xbce1e7ab456405f8ll, 0xb53387c1)
NT2_CONSTANT_MAKE_REAL(constants::sqrt_2pi_    , 0x40040d931ff62704ll, 0x40206c99)
NT2_CONSTANT_MAKE_REAL(constants::_2_o_pi_     , 0x3fe45f306dc9c883ll, 0x3f22f983) 
NT2_CONSTANT_MAKE_REAL(constants::sqrt_2_o_pi  , 0x3fe9884533d43651ll, 0x3f4c422a)
NT2_CONSTANT_MAKE_REAL(constants::three_pi_o_4 , 0x4002d97c7f3321d2ll, 0x4016cbe4)

  
  namespace nt2 {
    static const long double long_pi = 3.141592653589793238462643383279502884197l;
    static const long double long_deginrad = 0.017453292519943295769236907684886l; 
    static const long double long_radindeg =  57.295779513082320876798154814105l; 
  }
#endif
