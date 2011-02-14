//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_SSE4_1_SELECT_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_SSE4_1_SELECT_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::select_, tag::cpu_,
                         (A0)(A1)(X),
                         ((simd_<arithmetic_<A0>,X>))
                         ((simd_<arithmetic_<A1>,X>))
                         ((simd_<arithmetic_<A1>,X>))
                        );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::select_(tag::simd_<tag::arithmetic_, X> ,
                           tag::simd_<tag::arithmetic_, X> ,
                           tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
      struct result<This(A0,A1,A1)> : meta::strip<A1>{};

    NT2_FUNCTOR_CALL(3)
    {
      //      return b_or(b_and(a1,a0),b_andnot(a2,a0));
      // return bitwise_xor(a2, b_and(b_xor(a2, a1),a0));
      return simd::native_cast<A1>(_mm_blendv_epi8(a2, a1, simd::native_cast<A1>(a0))); 

    }

  };
} }

NT2_REGISTER_DISPATCH(tag::select_, tag::cpu_,
                         (A0)(A1)(X),
                         ((simd_<arithmetic_<A0>,X>))
                         ((simd_<float_<A1>,X>))
                         ((simd_<float_<A1>,X>))
                        );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::select_(tag::simd_<tag::arithmetic_, X> ,
                           tag::simd_<tag::float_, X> ,
                           tag::simd_<tag::float_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
      struct result<This(A0,A1,A1)> : meta::strip<A1>{};

    NT2_FUNCTOR_CALL(3)
    {
      return simd::native_cast<A1>(_mm_blendv_ps(a2, a1, simd::native_cast<A1>(a0))); 
    }

  };
} }

NT2_REGISTER_DISPATCH(tag::select_, tag::cpu_,
                         (A0)(A1)(X),
                         ((simd_<arithmetic_<A0>,X>))
                         ((simd_<double_<A1>,X>))
                         ((simd_<double_<A1>,X>))
                        );
namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::select_(tag::simd_<tag::arithmetic_, X> ,
                           tag::simd_<tag::double_, X> ,
                           tag::simd_<tag::double_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
      struct result<This(A0,A1,A1)> : meta::strip<A1>{};

    NT2_FUNCTOR_CALL(3)
    {
      return simd::native_cast<A1>(_mm_blendv_pd(a2, a1, simd::native_cast<A1>(a0))); 
    }

  };
} }

//#include <nt2/toolbox/bitwise/function/simd/sse/ssse3/select.hpp>
#endif
