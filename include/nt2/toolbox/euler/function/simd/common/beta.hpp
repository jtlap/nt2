//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EULER_FUNCTION_SIMD_COMMON_BETA_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTION_SIMD_COMMON_BETA_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/signgam.hpp>
#include <nt2/include/functions/gammaln.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/tofloat.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::beta_, tag::cpu_,
                       (A0)(X),
                       ((simd_<arithmetic_<A0>,X>))
                       ((simd_<arithmetic_<A0>,X>))
                      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::beta_(tag::simd_<tag::arithmetic_, X> ,
                         tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      return nt2::beta(tofloat(a0), tofloat(a1));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::beta_, tag::cpu_,
                       (A0)(X),
                       ((simd_<real_<A0>,X>))
                       ((simd_<real_<A0>,X>))
                      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::beta_(tag::simd_<tag::real_, X> ,
                         tag::simd_<tag::real_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      const A0 y = a0+a1;
      const A0 sign = signgam(a0)*signgam(a1)*signgam(y);
      return sign*exp(gammaln(a0)+gammaln(a1)-gammaln(y));
    }
  };
} }

#endif
// modified by jt the 05/01/2011