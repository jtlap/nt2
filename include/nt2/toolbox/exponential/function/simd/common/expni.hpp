//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SIMD_COMMON_EXPNI_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SIMD_COMMON_EXPNI_HPP_INCLUDED
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/gamma.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_odd.hpp>
#include <nt2/include/functions/bitwise_ornot.hpp>
#include <nt2/include/functions/nbtrue.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::expni_, tag::cpu_,
                        (A0)(A1)(X),
                        ((integer_<A0>))
                        ((simd_<arithmetic_<A0>,X>))
                       );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::expni_(tag::integer_,
                          tag::simd_(tag::arithmetic_, X)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0, A1)> :
      boost::result_of<meta::floating(A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      return expni(a0, tofloat(a1));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::expni_, tag::cpu_,
                        (A0)(A1)(X),
                        ((integer_<A0>))
                        ((simd_<real_<A1>,X>))
                       );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::expni_(tag::integer_, X,
                          tag::simd_(tag::real_, X)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0, A1)> :
      boost::result_of<meta::floating(A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      A1 x =  a1|islez(a1);
      const int32_t sn =  a0;
      if( sn == 0 )  return nt2::exp(-x)/x;
      if (sn < 0 )   return Nan<A1>();
      A1 n = splat<A1>(sn);
      if (sn  > 5000 )
      {
        A1 xk = x + n;
        A1 yk = rec(sqr(xk));
        A1 t = n;
        A1 ans = yk*t*(Six<A1>()*sqr(x)-Eight<A1>()*t*x+sqr(t));
        ans = yk*(ans+t*(t-Two<A1>()*x));
        ans = yk*(ans+t);
        return oneplus(ans)*exp(-x)/xk;
      }
      A1 r =  Nan<A1>();
      A1 test1 = is_le(a1, One<A1>());
      int32_t nb = 0;
      if ((nb = nbtrue(test1)) > 0)
      {
        A1 xx = sel(test1, x, One<A1>());
        A1 y1 = case_1(xx, sn);
        r = b_ornot(y1, test1);
        if (nb >= meta::cardinal_of<A1>::value) return r;
      }
      A1 xx = sel(test1, Two<A1>(), x);
      A1 y2 =  case_2(xx, sn);
      r &= b_or(y2, test1);
      r =  seladd(islt(x, Maxlog<A1>()), Zero<A1>(), r);
      return b_or(r, isnan(a1)); // we are done
    }
  };
} }

#endif
// modified by jt the 05/01/2011
