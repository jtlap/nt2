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
#include <nt2/include/constants/real.hpp>

namespace nt2 { namespace constants
{
  struct pi_o_2_   {};
  struct pi_o_4_   {};
  struct pi_x_4_   {};
  struct pi_x_2_   {};
  struct sqrt_2pi_ {};
  struct _4_o_pi_  {};
  struct _2_o_pi_  {};
  struct sqrt_2_o_pi_ {};
  struct three_pi_o_4_ {};
  struct inv_pi_   {};
  struct pi_o_180_ {};
  struct one_o_180_{};
  struct deg_in_rad_  {};
  struct rad_in_deg_  {};
  struct rad_in_deg_r_{};
  struct inv_pio2_  {}; //=  6.36619772367581382433e-01,  0x3FE45F30, 0x6DC9C883 
  struct pio2_1_  {};  // =  1.57079632673412561417e+00,  0x3FF921FB, 0x54400000 
  struct pio2_1t_  {}; // =  6.07710050650619224932e-11,  0x3DD0B461, 0x1A626331 
  struct pio2_2_  {};  // =  6.07710050630396597660e-11,  0x3DD0B461, 0x1A600000 
  struct pio2_2t_  {}; // =  2.02226624879595063154e-21,  0x3BA3198A, 0x2E037073 
  struct pio2_3_  {};  // =  2.02226624871116645580e-21,  0x3BA3198A, 0x2E000000 
  struct pio2_3t_  {}; // =  8.47842766036889956997e-32;  0x397B839A, 0x252049C1 
  
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
  NT2_CONSTANT_IMPLEMENTATION(constants::sqrt_2_o_pi_  , Sqrt_2opi)
  NT2_CONSTANT_IMPLEMENTATION(constants::three_pi_o_4_ , Threepio_4)
  NT2_CONSTANT_IMPLEMENTATION(constants::inv_pio2_     , Invpio_2)   //=  6.36619772367581382433e-01,  0x3FE45F30, 0x6DC9C883 
  NT2_CONSTANT_IMPLEMENTATION(constants::pio2_1_       , Pio2_1)     // =  1.57079632673412561417e+00,  0x3FF921FB, 0x54400000 
  NT2_CONSTANT_IMPLEMENTATION(constants::pio2_1t_      , Pio2_1t)    // =  6.07710050650619224932e-11,  0x3DD0B461, 0x1A626331 
  NT2_CONSTANT_IMPLEMENTATION(constants::pio2_2_       , Pio2_2)     // =  6.07710050630396597660e-11,  0x3DD0B461, 0x1A600000 
  NT2_CONSTANT_IMPLEMENTATION(constants::pio2_2t_      , Pio2_2t)    // =  2.02226624879595063154e-21,  0x3BA3198A, 0x2E037073 
  NT2_CONSTANT_IMPLEMENTATION(constants::pio2_3_       , Pio2_3)     // =  2.02226624871116645580e-21,  0x3BA3198A, 0x2E000000 
  NT2_CONSTANT_IMPLEMENTATION(constants::pio2_3t_      , Pio2_3t)    // =  8.47842766036889956997e-32;  0x397B839A, 0x252049C1 
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
NT2_CONSTANT_MAKE_REAL(constants::_2_o_pi_     , 0x3fe45f306dc9c883ll, 0x3f22f984) //0R 0x3f22f983 ?
NT2_CONSTANT_MAKE_REAL(constants::sqrt_2_o_pi_ , 0x3fe9884533d43651ll, 0x3f4c422a)
NT2_CONSTANT_MAKE_REAL(constants::three_pi_o_4_, 0x4002d97c7f3321d2ll, 0x4016cbe4)

NT2_CONSTANT_MAKE_REAL(constants::inv_pio2_     , 0x3FE45F306DC9C883ll,  0x3f22f984)//6.36619772367581382433e-01,   
NT2_CONSTANT_MAKE_REAL(constants::pio2_1_       , 0x3FF921FB54400000ll,  0x3fc90f80)//1.57079632673412561417e+00,  
NT2_CONSTANT_MAKE_REAL(constants::pio2_1t_      , 0x3DD0B4611A626331ll,  0x37354443)//6.07710050650619224932e-11,  
NT2_CONSTANT_MAKE_REAL(constants::pio2_2_       , 0x3DD0B4611A600000ll,  0x37354400)//6.07710050630396597660e-11,  
NT2_CONSTANT_MAKE_REAL(constants::pio2_2t_      , 0x3BA3198A2E037073ll,  0x2e85a308)//2.02226624879595063154e-21,  
NT2_CONSTANT_MAKE_REAL(constants::pio2_3_       , 0x3BA3198A2E000000ll,  0x2e85a300)//2.02226624871116645580e-21,  
NT2_CONSTANT_MAKE_REAL(constants::pio2_3t_      , 0x397B839A252049C1ll,  0x248d3132)//8.47842766036889956997e-32;  
  
  namespace nt2 {
    static const long double long_pi = 3.141592653589793238462643383279502884197l;
    static const long double long_deginrad = 0.017453292519943295769236907684886l; 
    static const long double long_radindeg =  57.295779513082320876798154814105l; 
  }
#endif
