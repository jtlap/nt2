//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BESSEL_FUNCTION_SCALAR_JNI_HPP_INCLUDED
#define NT2_TOOLBOX_BESSEL_FUNCTION_SCALAR_JNI_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>

#include <nt2/include/functions/j0.hpp>
#include <nt2/include/functions/j1.hpp>
#include <nt2/include/functions/cospi.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::jni_, tag::cpu_,
                     (A0)(A1),
                     (integer_<A0>)(arithmetic_<A1>)
                    )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::jni_(tag::integer_,tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      std::tr1::result_of<meta::floating(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      return nt2::jni(a0, type(a1));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::jni_, tag::cpu_,
                     (A0)(A1),
                     (integer_<A0>)(double_<A1>)
                    )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::jni_(tag::integer_,tag::double_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      std::tr1::result_of<meta::floating(A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
        return ::jn(a0, a1);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::jni_, tag::cpu_,
                     (A0)(A1),
                     (integer_<A0>)(float_<A1>)
                    )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::jni_(tag::integer_,tag::float_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      std::tr1::result_of<meta::floating(A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type result_type;
      result_type x = a1;
      const int32_t n1 = nt2::abs(a0);
      result_type sign = a0<0?cospi(n1):1;
      if( n1 == 0 )
        return( sign * nt2::j0(x) );
      if( n1 == 1 )
        return( sign * nt2::j1(x) );
      if( n1 == 2 )
        return mul(sign, (mul(Two<result_type>(), nt2::j1(x) / x)  -  nt2::j0(x)) );

      /* continued fraction */
      int k = 24;
      result_type pk = 2*(n1 + k);
      result_type ans = pk;
      result_type xk = sqr(x);
      do {
        pk  = pk - Two<result_type>();
        ans = pk - (xk/ans);
      }
      while( --k > 0 );
      /* backward recurrence */

      pk = One<result_type>();
      /*pkm1 = 1.0/ans;*/
      result_type xinv = rec(x);
      result_type pkm1 = ans * xinv;
      k = n1-1;
      result_type r = 2.0f*k;

      do{
        const result_type pkm2 = (pkm1 * r  -  pk * x) * xinv;
        pk = pkm1;
        pkm1 = pkm2;
        r -= Two<result_type>();
      }
      while( --k > 0 );
      return sign*sel(gt(abs(pk), nt2::abs(pkm1)),nt2::j1(x)/pk, nt2::j0(x)/pkm1);
      //     return ::jnf(a0, a1);
    }
  };
} }

#endif
// modified by jt the 26/12/2010
// modified manually by jt the 26/12/2010
