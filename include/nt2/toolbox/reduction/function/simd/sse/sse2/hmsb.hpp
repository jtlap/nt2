//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE2_HMSB_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE2_HMSB_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
namespace nt2 { namespace functors
{
  //  no special validate for all

  /////////////////////////////////////////////////////////////////////////////
  // Compute hmsb(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Dummy>
  struct call<hmsb_,
              tag::simd_(tag::arithmetic_,Extension),Dummy>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      {
	typedef typename meta::as_integer<typename meta::scalar_of<A0>::type, signed>::type type;
      };

    NT2_FUNCTOR_CALL_DISPATCH ( 1
                              , typename nt2::meta::scalar_of<A0>::type
                              , (3, (float,double,arithmetic_))
                              )

    NT2_FUNCTOR_CALL_EVAL_IF(1,  float) { return _mm_movemask_ps(a0); }
    NT2_FUNCTOR_CALL_EVAL_IF(1, double) { return _mm_movemask_pd(a0); }

    NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)
    {
      return _mm_movemask_epi8(a0); // TO CHECK
    }
  };
} }

#endif
