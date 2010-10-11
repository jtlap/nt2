//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BESSEL_FUNCTION_SIMD_COMMON_YNI_HPP_INCLUDED
#define NT2_TOOLBOX_BESSEL_FUNCTION_SIMD_COMMON_YNI_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/y0.hpp>
#include <nt2/include/functions/y1.hpp>
#include <nt2/include/functions/cospi.hpp>

#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/is_ltz.hpp>


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<yni_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : 
      boost::mpl::and_<meta::is_real_convertible<A1>
		       ,meta::is_scalar<A0>
		       ,meta::is_integral<A0>
      >{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute yni(const A0& a0, const A0& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<yni_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :  meta::as_real<A1>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      A1,
      (3, (float,double,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(2,  float)
    {
	typedef A1 result_type; 
	result_type x = a1;
	const int32_t n1 = abs(a0);
	result_type sign = splat<result_type>(a0<0?cospi(n1):1);
	if( n1 == 0 )
	  return( sign * y0(x) );
	if( n1 == 1 )
	  return( sign * y1(x) );
	if( n1 == 2 )
	  return mul(sign, (mul(Two<result_type>(), j1(x) / x)  -  j0(x)) );
	result_type an1 = splat<result_type>(n1);
	result_type res1 = an1*log(an1/x); 
	if (n1 > 29)
	  return  res1; 
        /* forward recurrence on n */

	result_type anm2 = y0(x);
	result_type anm1 = y1(x);
	int32_t k = 1;
	result_type r = splat<result_type>(k << 1);
	result_type xinv = rec(x);
	result_type an; 
	do
	  {
	    an = r*anm1*xinv-anm2;
	    anm2 = anm1;
	    anm1 = an;
	    r +=Two<result_type>();
	    ++k;
	  }
	while( k < n1 );
	return b_or(isltz(a1), select(islt(a1,One<result_type>()),res1,sign*an));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2, double)
    {
      const A1 r(yni(a0, a1[0]),yni(a0, a1[1])) ; 
      return r; 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,       arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type type; 
      return nt2::yni(a0, tofloat(a1)); 
    }
  };
} }

      
#endif
