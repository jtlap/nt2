//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ELLIPTIC_FUNCTION_SIMD_COMMON_ELLIE_HPP_INCLUDED
#define NT2_TOOLBOX_ELLIPTIC_FUNCTION_SIMD_COMMON_ELLIE_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/eps_related.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/tan.hpp>
#include <nt2/include/functions/ceil.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/any.hpp>
#include <nt2/include/functions/tofloat.hpp>


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<ellie_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      meta::is_real_convertible<A0>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute ellie(const A0& a0, const A0& a1)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is float
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<ellie_,tag::simd_(tag::arithmetic_),float,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
	A0 lphi = abs(a0);
	A0 m   =  a1;
	A0 a = One<A0>();
	A0 b = sqrt(oneminus(m));
	A0 c = sqrt(m);
	A0 d = One<A0>();
	A0 e = Zero<A0>();
	A0 t = tan( lphi );
	A0 mod = ceil(lphi/Pi<A0>());
	while(1)
	  {
	    A0 test = gt(abs(c),Eps<A0>()*abs(a));
	    if (any(test))
	      {
		A0 temp = b/a;
		lphi = lphi + atan(t*temp) + mod * Pi < A0>();
		mod = ceil(lphi/Pi<A0>());
		t = oneplus(temp)/(rec(t)-temp*t);
		c = average(a,-b);
		temp = sqrt(a*b);
		a = average(a,b);
		b = temp;
		d = d+d;
		e = seladd(test, e, c*sin(lphi));
	      }
	    else
	      break;
	  }
	b = oneminus(m);
	A0 temp = ellpe(b)/ellpk(b);
	temp = temp*(atan(t) + mod * Pi < A0>())/(d * a);
	temp = temp+e;
	temp = b_xor(temp, bitofsign(a0));
	return b_or(b_or(is_ltz(a1), gt(a1, One<A0>())), temp);
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<ellie_,tag::simd_(tag::arithmetic_),double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      return map(functor<ellie_>(), a0, a1);
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<ellie_,tag::simd_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type; 
      return nt2::ellie(tofloat(a0), tofloat(a1));
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010
