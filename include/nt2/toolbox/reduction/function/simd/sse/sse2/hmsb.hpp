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

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is float
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<hmsb_,tag::simd_(tag::arithmetic_),float,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      {
	typedef typename meta::as_integer<typename meta::scalar_of<A0>::type>::type type;
      };

    NT2_FUNCTOR_CALL(1){ return _mm_movemask_ps(a0); }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<hmsb_,tag::simd_(tag::arithmetic_),double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      {
	typedef typename meta::as_integer<typename meta::scalar_of<A0>::type>::type type;
      };

    NT2_FUNCTOR_CALL(1){ return _mm_movemask_pd(a0); }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<hmsb_,tag::simd_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      {
	typedef typename meta::as_integer<typename meta::scalar_of<A0>::type>::type type;
      };

    NT2_FUNCTOR_CALL(1)
    {
      return _mm_movemask_epi8(a0);
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010
