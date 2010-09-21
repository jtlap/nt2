//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_EPS_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_EPS_HPP_INCLUDED
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/exponent.hpp>
#include <nt2/include/functions/abs.hpp>


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<eps_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      meta::is_floating_point<A0>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute eps(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<eps_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL_DISPATCH ( 1
                                , A0
                                , (2, (real_,arithmetic_))
                                )

      NT2_FUNCTOR_CALL_EVAL_IF(1,  real_)
      {
      typedef typename meta::as_integer<A0, signed>::type        int_type;
      const A0 a = abs(a0);
      return seladd(isinvalid(a),
		    select(islt(a, Smallestposval<A0>()), 
			   Mindenormal<A0>(),   
			   ldexp(One<A0>(), exponent(a)-Nbmantissabits<A0>())
  			   ),
  		    Nan<A0>());
      }
    NT2_FUNCTOR_CALL_EVAL_IF(1,  arithmetic_)
    {
      details::ignore_unused(a0); 
      return One<A0>();
    }
  };
} }

      
#endif
