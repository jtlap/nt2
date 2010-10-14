//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_BITWISE_SELECT_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_BITWISE_SELECT_HPP_INCLUDED
#include <nt2/sdk/meta/size.hpp>
#include <nt2/sdk/meta/strip.hpp>


namespace nt2 { namespace functors
{
//   template<class Extension,class Info>
//   struct validate<bitwise_select_,tag::simd_(tag::arithmetic_,Extension),Info>
//   {
//     template<class Sig> struct result;
//     template<class This,class A0,class A1,class A2>
//     struct result<This(A0,A1,A2)> : 
//       meta::has_same_size<A0,A1>{};
//   };
  /////////////////////////////////////////////////////////////////////////////
  // Compute bitwise_select(const A0& a0, const A0& a1, const A0& a2)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<bitwise_select_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
      struct result<This(A0,A1,A1)>: meta::strip<A1>{}; 

    NT2_FUNCTOR_CALL(3)
    {
      return bitwise_xor(a2, b_and(bitwise_xor(a2, a1),a0)); 
      //      return b_or(b_and(a1,a0),b_andnot(a2,a0));
    }
  };
} }

      
#endif
