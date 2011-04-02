//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_AVX_RDIVIDE_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_AVX_RDIVIDE_HPP_INCLUDED
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/strip.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::rdivide_, tag::cpu_,
                          (A0),
                          ((simd_<arithmetic_<A0>,tag::avx_>))
                          ((simd_<arithmetic_<A0>,tag::avx_>))
                         );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::rdivide_(tag::simd_<tag::arithmetic_, tag::avx_),
                            tag::simd_<tag::arithmetic_, tag::avx_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      NT2_AVX_JOIN128INT2(that, nt2::rdivide);
      return that;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::rdivide_, tag::cpu_,
                          (A0),
                          ((simd_<real_<A0>,tag::avx_>))
                          ((simd_<real_<A0>,tag::avx_>))
                         );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::rdivide_(tag::simd_<tag::real_, tag::avx_),
                            tag::simd_<tag::real_, tag::avx_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      return a0/a1;
    }
  };
} }

#endif
// modified by jt the 04/01/2011