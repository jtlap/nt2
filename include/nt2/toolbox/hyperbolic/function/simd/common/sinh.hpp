//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SIMD_COMMON_SINH_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SIMD_COMMON_SINH_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/expm1.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/all.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::sinh_, tag::cpu_,
                       (A0)(X),
                       ((simd_<arithmetic_<A0>,X>))
                      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::sinh_(tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      return sinh(tofloat(a0));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::sinh_, tag::cpu_,
                       (A0)(X),
                       ((simd_<real_<A0>,X>))
                      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::sinh_(tag::simd_<tag::real_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
/* __ieee754_sinh(x)//TODO
 * Method :
 * mathematically sinh(x) if defined to be (exp(x)+exp(-x))/2
 *    1. Replace x by |x| (sinh(x) = sinh(-x)).
 *    2.
 *                                                  [ exp(x) - 1 ]^2
 *        0        <= x <= ln2/2  :  sinh(x) := 1 + -------------------
 *                                                   2*exp(x)
 *
 *                                            exp(x) +  1/exp(x)
 *        ln2/2    <= x <= 22     :  sinh(x) := -------------------
 *                                                  2
 *        22       <= x <= lnovft :  sinh(x) := exp(x)/2
 *        lnovft   <= x <= ln2ovft:  sinh(x) := exp(x/2)/2 * exp(x/2)
 *        ln2ovft  <  x     :  sinh(x) := huge*huge (overflow)
 *
 * Special cases:
 *    sinh(x) is |x| if x is +INF, -INF, or NaN.
 *    only sinh(0)=1 is exact for finite x.
 */
        const A0 tmp=exp(a0);
        if (all(gt(abs(a0), Half<A0>())))
          {
            return (tmp-rec(tmp))*Half<A0>();
          }
        else
          {
            return -tmp*nt2::expm1(-(a0+a0))*Half<A0>();
          }
    }
  };
} }

#endif
// modified by jt the 05/01/2011
