/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_EULER_FUNCTION_SCALAR_CONSTANTS_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTION_SCALAR_CONSTANTS_HPP_INCLUDED
#include <nt2/sdk/constant/constant.hpp>
#include <nt2/sdk/constant/real.hpp>

namespace nt2 { namespace constants
{
  struct stirling_splitlim_  {};
  struct stirling_largelim_  {};
  struct digamma_largelim_   {};
  struct fast_gamma_largelim_{};
}  }

namespace nt2
{
  NT2_CONSTANT_IMPLEMENTATION(constants::stirling_splitlim_,Stirlingsplitlim )
  NT2_CONSTANT_IMPLEMENTATION(constants::stirling_largelim_,Stirlinglargelim )
  NT2_CONSTANT_IMPLEMENTATION(constants::digamma_largelim_,Digammalargelim )
  NT2_CONSTANT_IMPLEMENTATION(constants::fast_gamma_largelim_,Fastgammalargelim )
}


NT2_CONSTANT_MAKE_REAL(constants::stirling_splitlim_   ,0x4061e083ba3443d4ll,0x41d628f6)// double 143.01608 float  26.77 //TODO
NT2_CONSTANT_MAKE_REAL(constants::stirling_largelim_   ,0x4061e083ba3443d4ll,0x41d628f6)// double 172.0     float  35.0399895
NT2_CONSTANT_MAKE_REAL(constants::digamma_largelim_    ,0x4034000000000000ll,0x41200000)
NT2_CONSTANT_MAKE_REAL(constants::fast_gamma_largelim_ ,0x4040800000000000ll,0x41200000)// double 33.0      float  10.0

#endif
// NT2_CONSTANT(fast_gamma_small_   , fast_gamma_small    )
// // double 1.0e-9
// // float  1.0e-4
// NT2_SPECIALIZE_CONSTANT( fast_gamma_small_, Category, boost::mpl::_
//                        , ((double   ,0x3e112e0be826d695ll))
//                          ((float    ,0x38d1b717          ))
//                        )

