//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_FAST_HYPOT_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_FAST_HYPOT_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/eps_related.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/exponent.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/tofloat.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::fast_hypot_, tag::cpu_,
                             (A0)(X),
                             ((simd_<arithmetic_<A0>,X>))
                             ((simd_<arithmetic_<A0>,X>))
                            );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::fast_hypot_(tag::simd_<tag::arithmetic_, X> ,
                               tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>  :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      return nt2::fast_hypot(tofloat(a0), tofloat(a1));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::fast_hypot_, tag::cpu_,
                             (A0)(X),
                             ((simd_<real_<A0>,X>))
                             ((simd_<real_<A0>,X>))
                            );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::fast_hypot_(tag::simd_<tag::real_, X> ,
                               tag::simd_<tag::real_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>  :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      A0 x =  nt2::abs(a0);
      A0 y =  nt2::abs(a1);
      A0 gtyx = gt(y,x);
      A0 xx = sel(gtyx,y,x);
      A0 yy = sel(gtyx,x,y);
      A0 r =  xx*sqrt(One<A0>()+sqr(yy/xx));
      return sel(ge(xx*Eps<A0>(), yy), xx, r);
   }
  };
} }

#endif
// modified by jt the 04/01/2011
