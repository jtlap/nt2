//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_SIMD_COMMON_ANP_HPP_INCLUDED
#define NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_SIMD_COMMON_ANP_HPP_INCLUDED

#include <nt2/toolbox/combinatorial/functions/anp.hpp>
#include <nt2/include/functions/simd/bitwise_cast.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/toint.hpp>
#include <nt2/include/functions/simd/split.hpp>
#include <nt2/include/functions/simd/group.hpp>
#include <nt2/sdk/meta/upgrade.hpp>

//TODO suppress the file or make a performing simd impl
//moreover the commented part induce in short errors in clang
// results depending on cout being there or not

namespace nt2 { namespace ext
{
//   NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::anp_, tag::cpu_,
//                       (A0)(X),
//                       ((simd_<arithmetic_<A0>,X>))
//                       ((simd_<arithmetic_<A0>,X>))
//                      )
//   {
//     typedef A0 result_type;
//     NT2_FUNCTOR_CALL_REPEAT(2)
//     {
//       return boost::simd::bitwise_cast<A0>(toint(anp(tofloat(a0),tofloat(a1))));
//     }
//   };
  
//   NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::anp_, tag::cpu_,
//                       (A0)(X),
//                       ((simd_<type16_<A0>,X>))
//                       ((simd_<type16_<A0>,X>))
//                      )
//   {
//     typedef A0 result_type;
//     NT2_FUNCTOR_CALL_REPEAT(2)
//     {
//       typedef typename meta::upgrade<A0> ::type utype;
//       utype a00, a01, a10, a11;
//       nt2::split(a0, a00, a01);
//       nt2::split(a1, a10, a11);
//       std::cout << a0 << "    " << a1 << std::endl;
//       std::cout << a00 << a01 << "   " << a01 << a11<< std::endl;   
//       std::cout << anp(a00, a01) << "   " << anp(a01, a11)<< std::endl;   
//       std::cout << nt2::group(anp(a00,a10),anp(a01,a11))<< std::endl;   
//       return nt2::group(anp(a00,a10),anp(a01,a11)); 
//     }
//   };
  
//   NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::anp_, tag::cpu_,
//                       (A0)(X),
//                       ((simd_<type8_<A0>,X>))
//                       ((simd_<type8_<A0>,X>))
//                      )
//   {
//     typedef A0 result_type;
//     NT2_FUNCTOR_CALL_REPEAT(2)
//     {
//       typedef typename meta::upgrade<A0> ::type utype;
//       utype a00, a01, a10, a11;
//       nt2::split(a0, a00, a01);
//       nt2::split(a1, a10, a11);
//       return nt2::group(anp(a00,a10),anp(a01,a11)); 
//     }
//   };

// ///////////////////////////////////////////////////////////////////////////////
// //Implementation when type A0 is floating_
// ///////////////////////////////////////////////////////////////////////////////


//   NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::anp_, tag::cpu_,
//                       (A0)(X),
//                       ((simd_<floating_<A0>,X>))
//                       ((simd_<floating_<A0>,X>))
//                      )
//   {
//     typedef A0 result_type;
//     NT2_FUNCTOR_CALL_REPEAT(2)
//     {
//       return map(functor<tag::anp_>(),a0,a1);
//     }
//   };
} }
#endif
