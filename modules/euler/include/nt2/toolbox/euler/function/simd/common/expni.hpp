//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EULER_FUNCTION_SIMD_COMMON_EXPNI_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTION_SIMD_COMMON_EXPNI_HPP_INCLUDED
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
#include <nt2/include/functions/is_lez.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_odd.hpp>
#include <nt2/include/functions/bitwise_ornot.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/nbtrue.hpp>
#include <nt2/include/functions/any.hpp>

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
                          tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0, A1)> :
      std::tr1::result_of<meta::floating(A1)>{};

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
  struct call<tag::expni_(tag::integer_,
                          tag::simd_<tag::real_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0, A1)> :  meta::strip<A1>{};

    NT2_FUNCTOR_CALL(2)
    {
      A1 isleza1 = is_lez(a1); 
      A1 x =  b_or(a1, isleza1);
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
      A1 test1 = le(a1, One<A1>());
      std::cout << test1 << std::endl; 
      int32_t nb = 0;
      if ((nb = nbtrue(test1)) > 0)
      {
        A1 xx = sel(test1, x, One<A1>());
        A1 y1 = case_1(xx, sn, n);
        r = b_ornot(y1, test1);
        if (nb >= meta::cardinal_of<A1>::value) return b_or(r, isleza1);
      }
      A1 xx = sel(test1, Two<A1>(), x);
      A1 y2 =  case_2(xx, sn, n);
      r &= b_or(y2, test1);
      r =  seladd(lt(x, Maxlog<A1>()), Zero<A1>(), r);
      return b_or(r,  b_or(is_nan(a1), isleza1)); // we are done
    }
  private :
    template < class A1 >
    static inline A1 case_1(const A1 & x,  int32_t sn, const A1 & n)
    {
      typedef typename meta::scalar_of<A1>::type sA1; 
      /*		Power series expansion		*/
      sA1 psi1 = Zero<sA1>(); 
      for( int32_t i=sn-1; i; --i )  psi1 += rec((sA1)i);
      A1 psi = -Euler<A1>()-nt2::log(x)+splat<A1>(psi1); 
      A1 t; 
      A1 z = -x;
      A1 xk = Zero<A1>();
      A1 yk = One<A1>();
      A1 pk = One<A1>() - n;
      A1 ans = ( sn == 1 ) ? Zero<A1>() : rec(pk); 
      do
 	{
 	  xk += One<A1>();
 	  yk *= z/xk;
 	  pk += One<A1>();
 	  ans = seladd(is_nez(pk), ans, yk/pk);
 	  t = sel(is_nez(ans), nt2::abs(yk/ans), One<A1>());
 	}
       while( any(gt(t, Halfeps<A1>())));
       t = n;
       A1 r = n - One<A1>();
       return (nt2::powi(z, sn-1) * psi / nt2::gamma(t)) - ans;
       //TO DO pow->powi and gamma splatted from scalar or mere factorial call
    }
    
    template < class A1 >
    static inline A1 case_2(const A1 & x,  int32_t sn, const A1 & n)
    {
     typedef typename meta::scalar_of<A1>::type sA1;
      int32_t sk = 1;
      A1 t; 
      A1 pkm2 = One<A1>();
      A1 qkm2 = x;
      A1 pkm1 = One<A1>();
      A1 qkm1 = x + n;
      A1 ans = pkm1/qkm1;
      do
	{
	  A1 test =  is_nez(splat<A1>(is_odd(++sk)));
	  A1 k_2 =  splat<A1>(sk >> 1); 
	  A1 yk = sel(test, One<A1>(), x);
	  A1 xk = seladd(test, k_2, n); 
	  A1 pk = pkm1 * yk  +  pkm2 * xk;
	  A1 qk = qkm1 * yk  +  qkm2 * xk;
	  A1 r = pk/qk;
	  test = is_nez(qk); 
	  t = sel(test,nt2::abs((ans-r)/r),One<A1>());
	  ans = sel(test, r, ans);
	  pkm2 = pkm1;
	  pkm1 = pk;
	  qkm2 = qkm1;
	  qkm1 = qk;
	  test = gt(nt2::abs(pk), Expnibig<A1>());
	  A1 fac = sel(test, Halfeps<A1>(), One<A1>()); 
	  pkm2 *= fac;
	  pkm1 *= fac;
	  qkm2 *= fac;
	  qkm1 *= fac;
	}
      while( any(gt(t, Halfeps<A1>())) );
      return ans*nt2::exp(-x);
    }
  };
} }

#endif
// modified by jt the 05/01/2011
