/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SCALAR_IMPL_CONSTANTS_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SCALAR_IMPL_CONSTANTS_HPP_INCLUDED
#include <nt2/sdk/constant/constant.hpp>
//#include <nt2/sdk/constant/details/real_constant.hpp>
#include <nt2/sdk/constant/real.hpp>

namespace nt2 { namespace constants
{
  struct inv_log_2_        {};
  struct log_2_            {};
  struct log_10_           {};
  struct exp_1_            {};
  struct log_2_o_log_10_   {};
  struct inv_log_10_       {};
  struct max_log_          {};
  struct euler_            {};
  struct expni_big_        {};
  struct expx2_c1_         {};
  struct expx2_c2_         {};
}  }

namespace nt2
{
  NT2_CONSTANT_IMPLEMENTATION(constants::exp_1_         ,Exp_1       )
  NT2_CONSTANT_IMPLEMENTATION(constants::log_2_         ,Log_2       )
  NT2_CONSTANT_IMPLEMENTATION(constants::inv_log_2_     ,Invlog_2    )
  NT2_CONSTANT_IMPLEMENTATION(constants::log_10_        ,Log10       )
  NT2_CONSTANT_IMPLEMENTATION(constants::inv_log_10_    ,Invlog_10   )
  NT2_CONSTANT_IMPLEMENTATION(constants::log_2_o_log_10_,Log_2olog_10)
  NT2_CONSTANT_IMPLEMENTATION(constants::max_log_       ,Maxlog      )
  NT2_CONSTANT_IMPLEMENTATION(constants::euler_         ,Euler       )
  NT2_CONSTANT_IMPLEMENTATION(constants::expni_big_     ,Expnibig    )
  NT2_CONSTANT_IMPLEMENTATION(constants::expx2_c1_      ,Expx2c1     )
  NT2_CONSTANT_IMPLEMENTATION(constants::expx2_c2_      ,Expx2c2     )      
}


NT2_CONSTANT_MAKE_REAL(constants::exp_1_         ,0x4005bf0a8b145769LL,0x402df854)
NT2_CONSTANT_MAKE_REAL(constants::log_2_         ,0x3fe62e42fefa39efLL,0x3f317218)
NT2_CONSTANT_MAKE_REAL(constants::inv_log_2_     ,0x3ff71547652b82feLL,0x3fb8aa3b)
NT2_CONSTANT_MAKE_REAL(constants::log_10_        ,0x40026bb1bbb55516LL,0x40135d8e)
NT2_CONSTANT_MAKE_REAL(constants::inv_log_10_    ,0x3fdbcb7b1526e50dLL,0x3ede5bd9)
NT2_CONSTANT_MAKE_REAL(constants::log_2_o_log_10_,0x3fd34413509f79ffLL,0x3e9a209b)
NT2_CONSTANT_MAKE_REAL(constants::max_log_       ,0x40862e42fefa39efll,0x42b17218)
NT2_CONSTANT_MAKE_REAL(constants::euler_         ,0x3fe2788cfc6fb619ll,0x3f13c468)
NT2_CONSTANT_MAKE_REAL(constants::expni_big_     ,0x4380000000000000ll,0x4b800000) //2^57, 2^24
NT2_CONSTANT_MAKE_REAL(constants::expx2_c1_      ,0x4060000000000000ll,0x42000000) //128 , 32
NT2_CONSTANT_MAKE_REAL(constants::expx2_c2_      ,0x3f80000000000000ll,0x3d000000) //1/128,  1/32
#endif
