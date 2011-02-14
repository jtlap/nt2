//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BESSEL_FUNCTION_SIMD_COMMON_Y1_HPP_INCLUDED
#define NT2_TOOLBOX_BESSEL_FUNCTION_SIMD_COMMON_Y1_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/j1.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/all.hpp>




/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::y1_, tag::cpu_,
                     (A0)(X),
                     ((simd_<arithmetic_<A0>,X>))
                    );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::y1_(tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      return nt2::y1(tofloat(a0));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::y1_, tag::cpu_,
                     (A0)(X),
                     ((simd_<double_<A0>,X>))
                    );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::y1_(tag::simd_<tag::double_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      return map(functor<tag::y1_>(), a0);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::y1_, tag::cpu_,
                     (A0)(X),
                     ((simd_<float_<A0>,X>))
                    );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::y1_(tag::simd_<tag::float_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type sA0;
      A0 a0lt2 = lt(a0, Two<A0>());
      A0 q = rec(a0);
      A0 p2;
      if (any(a0lt2))
      {
        A0 z = sqr(a0);
        p2 = (z-single_constant<A0, 0x40954ae7> ())*a0*
          horner< NT2_HORNER_COEFF_T(sA0, 5,
                               (0x320a80f5,
                              0xb57eeb2e,
                              0x388ceb47,
                              0xbb2d21cf,
                              0x3d2c210b
                              ) ) > (z);
        p2 = p2+single_constant<A0, 0x3f22f983>()*(j1(a0)*log(a0)-q);
        if (all(a0lt2)) return p2;
       }
     A0 w = sqrt(q);
     A0 p3 = w *
       horner< NT2_HORNER_COEFF_T(sA0, 8,
                          (0x3d8d98f9,
                           0xbe69f6b3,
                           0x3ea0ad85,
                           0xbe574699,
                           0x3bb21b25,
                           0x3e18ec50,
                           0x36a6f7c5,
                           0x3f4c4229
                           ) ) > (q);
     w = sqr(q);
     A0 xn =  q*
     horner< NT2_HORNER_COEFF_T(sA0, 8,
                        (0xc233e16d,
                         0x424af04a,
                         0xc1c6dca7,
                         0x40e72299,
                         0xbfc5bd69,
                         0x3eb364d9,
                         0xbe27bad7,
                         0x3ebfffdd
                         ) ) > (w)-single_constant<A0,0x4016cbe4 > ();
     p3 = p3*sin(xn+a0);
     return select (a0lt2, p2, p3);
    }
  };
} }

#endif
// modified by jt the 05/01/2011
