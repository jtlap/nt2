//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_POLYNOMIALS_FUNCTION_SIMD_COMMON_PLEVL_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOMIALS_FUNCTION_SIMD_COMMON_PLEVL_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/tofloat.hpp>

namespace nt2 { namespace functors
{
  /////////////////////////////////////////////////////////////////////////////
  // Compute plevl(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Dummy>
  struct call<plevl_,
              tag::simd_(tag::arithmetic_,Extension),Dummy>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
      struct result<This(A0, A1)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      typename nt2::meta::scalar_of<A0>::type,
      (2, (real_,arithmetic_))
    )
    NT2_FUNCTOR_CALL_EVAL_IF(2,       real_)
    {
      typename A1::const_iterator p = a1.begin();
      A0 ans = a0+nt2::splat<A0>(*p++);
      do
	ans = fma(ans, a0, nt2::splat<A0>(*p));
      while( ++p !=  a1.end());
      return ans;
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,       arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type type;
      return plevl(tofloat(a0), a1);
    }
  };
} }

      
#endif
