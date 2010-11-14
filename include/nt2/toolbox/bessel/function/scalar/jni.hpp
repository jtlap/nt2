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

namespace nt2 { namespace functors
{

  template<class Info>
  struct dispatch<jni_, tag::scalar_(tag::arithmetic_),Info>
    : boost::mpl::_2 {};
  
  template<class Info>
  struct validate<jni_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :meta::is_integral<A0>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute jni(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A1 is float
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<jni_,tag::scalar_(tag::arithmetic_),float,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : 
      boost::result_of<meta::floating(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
	typedef float result_type; 
	result_type x = a1;
	const int32_t n1 = nt2::abs(a0);
	result_type sign = a0<0?cospi(n1):1;
	if( n1 == 0 ) return( sign * j0(x) );
	if( n1 == 1 ) return( sign * j1(x) );
	if( n1 == 2 )
	  return mul(sign, (mul(Two<result_type>(),
				nt2::j1(x) / x)  -  j0(x)) );

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
	  r = r-Two<result_type>();
	}
	while( --k > 0 );
	return sign*sel(gt(abs(pk), nt2::abs(pkm1)),nt2::j1(x)/pk, nt2::j0(x)/pkm1);
	//	 return ::jnf(a0, a1);
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A1 is double
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<jni_,tag::scalar_(tag::arithmetic_),double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : 
      boost::result_of<meta::floating(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
        return ::jn(a0, a1);
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A1 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<jni_,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : 
      boost::result_of<meta::floating(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type type; 
      return nt2::jni(a0, type(a1)); 
    }
  };

} }

#endif
/// Revised by jt the 14/11/2010
