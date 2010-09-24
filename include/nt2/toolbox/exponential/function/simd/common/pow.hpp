//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SIMD_COMMON_POW_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SIMD_COMMON_POW_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/log.hpp>


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<pow_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : 
      meta::is_real_convertible<A0>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute pow(const A0& a0, const A0& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<pow_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      typename nt2::meta::scalar_of<A0>::type,
      (2, (real_,arithmetic_))
    )
    NT2_FUNCTOR_CALL_EVAL_IF(2,       real_)
    {
      return seladd(isnez(a0),
		    Zero<A0>(),
		    sel(iseqz(a1),
			One<A0>(),
			exp(a1*log(a0))
			)
		    );
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,       arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type type; 
      return nt2::pow(tofloat(a0), tofloat(a1));
    }
  };
} }

      
#endif
