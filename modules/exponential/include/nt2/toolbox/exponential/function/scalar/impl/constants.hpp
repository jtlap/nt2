//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SCALAR_IMPL_CONSTANTS_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SCALAR_IMPL_CONSTANTS_HPP_INCLUDED
#include <nt2/sdk/constant/constant.hpp>
#include <nt2/include/constants/real.hpp>
  
NT2_MAKE_STD_CONSTANT(Exp_1        ,0x4005bf0a8b145769LL,0x402df854, 2)
NT2_MAKE_STD_CONSTANT(Log_2        ,0x3fe62e42fefa39efLL,0x3f317218, 0)
NT2_MAKE_STD_CONSTANT(Invlog_2     ,0x3ff71547652b82feLL,0x3fb8aa3b, 1)
NT2_MAKE_STD_CONSTANT(Log_10       ,0x40026bb1bbb55516LL,0x40135d8e, 1)
NT2_MAKE_STD_CONSTANT(Invlog_10    ,0x3fdbcb7b1526e50dLL,0x3ede5bd9, 0)
NT2_MAKE_STD_CONSTANT(Log_2olog_10 ,0x3fd34413509f79ffLL,0x3e9a209b, 0)
NT2_MAKE_STD_CONSTANT(Maxlog       ,0x40862e42fefa39efll,0x42b17218, 0)
NT2_MAKE_STD_CONSTANT(Euler        ,0x3fe2788cfc6fb619ll,0x3f13c468, 0)
NT2_MAKE_STD_CONSTANT(Expnibig     ,0x4380000000000000ll,0x4b800000, 0) //2^57, 2^24
NT2_MAKE_STD_CONSTANT(Expx2c1      ,0x4060000000000000ll,0x42000000, 0) //128 , 32
NT2_MAKE_STD_CONSTANT(Expx2c2      ,0x3f80000000000000ll,0x3d000000, 0) //1/128,  1/32
#endif
