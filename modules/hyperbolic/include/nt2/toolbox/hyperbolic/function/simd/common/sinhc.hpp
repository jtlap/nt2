//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SIMD_COMMON_SINHC_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SIMD_COMMON_SINHC_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/sinh.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/toolbox/hyperbolic/function/scalar/constants.hpp>
#include <nt2/sdk/constant/eps_related.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::sinhc_, tag::cpu_,
                        (A0)(X),
                        ((simd_<arithmetic_<A0>,X>))
                       );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::sinhc_(tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>: meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      return nt2::sinhc(tofloat(a0));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::sinhc_, tag::cpu_,
                        (A0)(X),
                        ((simd_<real_<A0>,X>))
                       );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::sinhc_(tag::simd_<tag::real_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>: meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      A0 a = nt2::abs(a0);
      A0 r1 = sinh(a)*rec(a);
      A0 a2 = sqr(a);
      A0 r2 = oneplus(a2*fma(a2, Oneo_120<A0>(), Oneo_6<A0>()));
      return sel(ge(a,Four<A0>()*Four<A0>()*Fourthrooteps<A0>()), r1, r2);
    }
  };
} }

#endif
// modified by jt the 05/01/2011