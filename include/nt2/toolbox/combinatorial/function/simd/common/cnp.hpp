//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_COMBINATORIAL_FUNCTION_SIMD_COMMON_CNP_HPP_INCLUDED
#define NT2_TOOLBOX_COMBINATORIAL_FUNCTION_SIMD_COMMON_CNP_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/toint.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for cnp

  /////////////////////////////////////////////////////////////////////////////
  // Compute cnp(const A0& a0, const A0& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<cnp_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      typename nt2::meta::scalar_of<A0>::type,
      (2, (real_,arithmetic_))
    )
    NT2_FUNCTOR_CALL_EVAL_IF(2,       real_)
    {
	A0 r; 
	map(functor<cnp_>(), a0, a1, r);
	return r; 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2, arithmetic_)
    {
      return simd::native_cast<A0>(toint(cnp(tofloat(a0),tofloat(a1))));
    }
  };
} }

      
#endif
