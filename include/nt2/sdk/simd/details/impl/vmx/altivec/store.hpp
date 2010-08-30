/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_VMX_ALTIVEC_STORE_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_VMX_ALTIVEC_STORE_HPP_INCLUDED

#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // Store a vector
  //////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<store_,tag::simd_(tag::arithmetic_,tag::vmx_), Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1, class A2>
    struct  result<This(A0,A1,A2)> { typedef A0 type; };

    NT2_FUNCTOR_CALL(3)
    {
      vec_st(a0, a2 * meta::cardinal_of<A0>::value, a1);
      return a0;
    }
  };
} }

#endif
