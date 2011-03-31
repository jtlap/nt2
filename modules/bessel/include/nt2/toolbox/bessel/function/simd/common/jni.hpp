//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BESSEL_FUNCTION_SIMD_COMMON_JNI_HPP_INCLUDED
#define NT2_TOOLBOX_BESSEL_FUNCTION_SIMD_COMMON_JNI_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/j0.hpp>
#include <nt2/include/functions/j1.hpp>
#include <nt2/include/functions/cospi.hpp>




/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::jni_, tag::cpu_,
                      (A0)(A1)(X),
                      ((integer_<A0>))
                      ((simd_<arithmetic_<A1>,X>))
                     );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::jni_(tag::integer_,
                        tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :  meta::as_real<A1>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      return nt2::jni(a0, tofloat(a1));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::jni_, tag::cpu_,
                      (A0)(A1)(X),
                      ((integer_<A0>))
                      ((simd_<double_<A1>,X>))
                     );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::jni_(tag::integer_,
                        tag::simd_<tag::double_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :  meta::as_real<A1>{};

    NT2_FUNCTOR_CALL(2)
    {
      const A1 r = {{jni(a0, a1[0]),jni(a0, a1[1])}} ;
      return r;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::jni_, tag::cpu_,
                      (A0)(A1)(X),
                      ((integer_<A0>))
                      ((simd_<float_<A1>,X>))
                     );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::jni_(tag::integer_,
                        tag::simd_<tag::float_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :  meta::as_real<A1>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef A1 type;
      type x = a1;
      const int32_t n1 = nt2::abs(a0);
      type sign = splat<type>(a0<0?nt2::cospi(n1):1);
      if( n1 == 0 )
        return( sign * j0(x) );
      if( n1 == 1 )
        return( sign * j1(x) );
      if( n1 == 2 )
        return mul(sign, (mul(Two<type>(), j1(x) / x)  -  j0(x)) );

      /* continued fraction */
      int k = 24;
      type pk = splat<type>(2*(n1 + k));
      type ans = pk;
      type xk = sqr(x);
      do {
        pk  = pk - Two<type>();
        ans = pk - (xk/ans);
      }
      while( --k > 0 );
      /* backward recurrence */

      pk = One<type>();
      /*pkm1 = 1.0/ans;*/
      type xinv = rec(x);
      type pkm1 = ans * xinv;
      k = n1-1;
      type r = splat<type>(2.0f*k);

      do{
        const type pkm2 = (pkm1 * r  -  pk * x) * xinv;
        pk = pkm1;
        pkm1 = pkm2;
        r = r-Two<type>();
      }
      while( --k > 0 );
      return sign*sel(is_greater(nt2::abs(pk), nt2::abs(pkm1)),j1(x)/pk, j0(x)/pkm1);
    }
  };
} }

#endif
// modified by jt the 05/01/2011
