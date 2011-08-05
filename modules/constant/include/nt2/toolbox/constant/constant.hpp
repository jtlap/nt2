//==============================================================================
//     Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//     Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//      Distributed under the Boost Software License, Version 1.0.
//         See accompanying file LICENSE.txt or copy at
//             http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_CONSTANT_CONSTANT_HPP_INCLUDED
#define NT2_TOOLBOX_CONSTANT_CONSTANT_HPP_INCLUDED

#include <boost/simd/toolbox/constant/constant.hpp>

#define NT2_MAKE_STD_CONSTANT(NAME,HEXDOUBLE,HEXFLOAT,INT)             \
BOOST_SIMD_STD_CONSTANT_TAG(NAME)                                      \
BOOST_SIMD_STD_CONSTANT_DEF(NAME)                                      \
BOOST_SIMD_STD_CONSTANT_FUNCTOR((nt2), (ext), NAME, HEXDOUBLE, HEXFLOAT, INT) \
BOOST_SIMD_PROTOIZE_CONSTANT(NAME)                                     \
  /**/
namespace nt2
{
  namespace tag
  {
    using boost::simd::tag::Digit;
    using boost::simd::tag::Eps;
    using boost::simd::tag::Halfeps;
    using boost::simd::tag::Threeeps;
    using boost::simd::tag::Sqrteps;
    using boost::simd::tag::Fourthrooteps;
    using boost::simd::tag::Thirdrooteps;
    using boost::simd::tag::Mlogeps2;
    using boost::simd::tag::Mindenormal;
    using boost::simd::tag::Smallestposval;
    using boost::simd::tag::False;
    using boost::simd::tag::Ldexpmask;
    using boost::simd::tag::Nbmantissabits;
    using boost::simd::tag::Maxexponent;
    using boost::simd::tag::Nbdigits;
    using boost::simd::tag::Nbexponentbits;
    using boost::simd::tag::Minexponent;
    using boost::simd::tag::Inf;
    using boost::simd::tag::Minf;
    using boost::simd::tag::Nan;
    using boost::simd::tag::Maxleftshift;
    using boost::simd::tag::Pi;
    using boost::simd::tag::Sqrt_2o_2;
    using boost::simd::tag::Sqrt_2;
    using boost::simd::tag::Gold;
    using boost::simd::tag::Cgold;
    using boost::simd::tag::Mhalf;
    using boost::simd::tag::Mzero;
    using boost::simd::tag::Half;
    using boost::simd::tag::Third;
    using boost::simd::tag::Quarter;
    using boost::simd::tag::Twotom10;
    using boost::simd::tag::Two2nmb;
    using boost::simd::tag::Splitfactor;
    using boost::simd::tag::Signmask;
    using boost::simd::tag::True;
    using boost::simd::tag::Valmax;
    using boost::simd::tag::Valmin;
  }
    
  using boost::simd::Mten;
  using boost::simd::Mnine;
  using boost::simd::Meight;
  using boost::simd::Mseven;
  using boost::simd::Msix;
  using boost::simd::Mfive;
  using boost::simd::Mfour;
  using boost::simd::Mthree;
  using boost::simd::Mtwo;
  using boost::simd::Mone;
  using boost::simd::Zero;
  using boost::simd::One;
  using boost::simd::Two;
  using boost::simd::Three;
  using boost::simd::Four;
  using boost::simd::Five;
  using boost::simd::Six;
  using boost::simd::Seven;
  using boost::simd::Eight;
  using boost::simd::Nine;
  using boost::simd::Ten;
  using boost::simd::Eleven;
  using boost::simd::Twelve; 
  using boost::simd::Twenty;
  using boost::simd::Twentyfour;	
  using boost::simd::_120; //!5 
  using boost::simd::_720; //!6  
  using boost::simd::_5040; //!7 
  using boost::simd::_40320; //!8 
  using boost::simd::_362880; //!9 
  using boost::simd::_3628800; //!10 
  using boost::simd::_39916800; //!11
  using boost::simd::Hundred;
  using boost::simd::Thousand;
  using boost::simd::Fortyfive;
  using boost::simd::Ninety;
  using boost::simd::Onehundredeighty;
  using boost::simd::C_180;
  using boost::simd::_45;
  using boost::simd::_90;
  using boost::simd::_180;
  using boost::simd::integral_constant;
  
  using boost::simd::Eps;
  using boost::simd::Halfeps;
  using boost::simd::Threeeps;
  using boost::simd::Sqrteps;
  using boost::simd::Fourthrooteps;
  using boost::simd::Thirdrooteps;
  using boost::simd::Mlogeps2;
  using boost::simd::Mindenormal;
  using boost::simd::Smallestposval;
  
  using boost::simd::False;
  
  using boost::simd::Ldexpmask;
  using boost::simd::Nbmantissabits;
  using boost::simd::Nbexponentbits;
  using boost::simd::Maxexponent;
  using boost::simd::Minexponent;
  using boost::simd::Nbdigits;
  
  using boost::simd::Inf;
  using boost::simd::Minf;
  using boost::simd::Nan;
  
  using boost::simd::Maxleftshift;
  
  using boost::simd::Mhalf;
  using boost::simd::Mzero;
  using boost::simd::Half;
  using boost::simd::Third;
  using boost::simd::Quarter;
  using boost::simd::Twotom10;
  using boost::simd::Two2nmb;
  using boost::simd::Pi;
  using boost::simd::Splitfactor;
  using boost::simd::Sqrt_2o_2;
  using boost::simd::Sqrt_2;
  using boost::simd::Gold;
  using boost::simd::Cgold;
  
  using boost::simd::real_constant;
  using boost::simd::single_constant;
  using boost::simd::double_constant;
  using boost::simd::Const;
  
  using boost::simd::Signmask;
  
  using boost::simd::True;
  
  using boost::simd::Valmin;
  using boost::simd::Valmax;
  
}

#endif
