//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SIMD_COMMON_EXPM1_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SIMD_COMMON_EXPM1_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/round2even.hpp>
#include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/fast_ldexp.hpp>
#include <nt2/include/functions/exp.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::expm1_, tag::cpu_,
                        (A0)(X),
                        ((simd_<arithmetic_<A0>,X>))
                       );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::expm1_(tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      return nt2::exp(tofloat(a0))-One<type>();
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::expm1_, tag::cpu_,
                        (A0)(X),
                        ((simd_<double_<A0>,X>))
                       );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::expm1_(tag::simd_<tag::double_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0>::type int_type;
      typedef typename meta::scalar_of<A0>::type sA0;
      A0 k =  round2even(double_constant<A0, 0x3ff71547652b82fell>()*a0);
      int_type ki =  toint(-k);
      A0 hi = a0 - k* double_constant<A0, 0x3fe62e42fee00000ll>(); //ln2HI;
      A0 lo = k*double_constant<A0, 0x3dea39ef35793c76ll>(); //ln2LO;
      A0 x = hi-lo;
      A0 hxs = sqr(x)*Half<A0>();
      A0 r1 = One<A0>()+hxs*horner <NT2_HORNER_COEFF_T(sA0, 5,
                                           (0xBE8AFDB76E09C32Dll,
                                          0x3ED0CFCA86E65239ll,
                                          0xBF14CE199EAADBB7ll,
                                          0x3F5A01A019FE5585ll,
                                          0xBFA11111111110F4ll)
                                           )> (hxs);
      A0 t  = Three<A0>()-r1*Half<A0>()*x;
      A0 e  = hxs*((r1-t)/(Six<A0>() - x*t));
      A0 c = (hi-x)-lo;
      e  = (x*(e-c)-c)-hxs;
      //& A0 kmask = cast < A0 > (islt(k, Twenty<int_type>()));

      A0 two2mk = fast_ldexp(One<A0>(), ki);
      A0 ct1= oneminus(two2mk)-(e-x);
      A0 ct2= oneplus((x-(e+two2mk)));

      A0 y = select(lt(k, Twenty<A0>()),ct1,ct2);
      y =  fast_ldexp(y, toint(k));
      return sel(eq(a0, Inf<A0>()), a0, y);
      //return impl::expm1(a0);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::expm1_, tag::cpu_,
                        (A0)(X),
                        ((simd_<float_<A0>,X>))
                       );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::expm1_(tag::simd_<tag::float_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      const A0 u =  exp(a0);
      const A0 p = b_or(is_eqz(u),is_inf(u));
      const A0 y1 = minusone(u);
      const A0 m = b_notand(p, is_not_equal(u, One<A0>()));
      const A0 y2 = mul(y1,(rdiv(a0,log(u))));
      return select(p,y1,select(m, y2, a0));
    }
  };
} }

#endif
// modified by jt the 05/01/2011
