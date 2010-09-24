//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SIMD_COMMON_ATANH_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SIMD_COMMON_ATANH_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/madd.hpp>
#include <nt2/include/functions/log1p.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/sign.hpp>


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<atanh_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      meta::is_real_convertible<A0>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute atanh(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<atanh_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      typename nt2::meta::scalar_of<A0>::type,
      (2, (real_, arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,  real_)
    {
      A0 absa0 = abs(a0); 
      const A0 small_mask    = islt(absa0, Twotom10<A0>());  /* x <  2**-10 */
      return select(small_mask,
		    a0*madd(Third<A0>(), sqr(a0), One<A0>()),
		    sign(a0)*Half<A0>()*log1p(Two<A0>()*absa0/(One<A0>()-absa0))
		    );
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,       arithmetic_)
    {
      return nt2::atanh(tofloat(a0));
    }
  };
} }

      
#endif
