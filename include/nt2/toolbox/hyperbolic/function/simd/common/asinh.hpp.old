//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SIMD_COMMON_ASINH_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SIMD_COMMON_ASINH_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/madd.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/bitofsign.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/log1p.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/nbtrue.hpp>


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<asinh_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      meta::is_floating_point<A0>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute asinh(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is float
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension, class Info>
  struct call<asinh_,tag::simd_(tag::arithmetic_,Extension),float,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
	A0 x = abs(a0);
	A0 lthalf = lt(x,Half<A0>());
	A0 x2 = sqr(x);
	A0 z;
	int32_t nb; 
	if( ( nb = nbtrue(lthalf)) > 0)
	  {
	    z = madd(single_constant<A0,(0x3ca4d6e6) >(),  x2, single_constant<A0,(0xbd2ee581)>());
	    z = madd(x2, z,  single_constant<A0,(0x3d9949b1)>());
	    z = madd(x2, z,  single_constant<A0,(0xbe2aa9ad)>())* x2 * x + x;
	    if(nb >= meta::cardinal_of<A0>::value) return  b_xor(z, bitofsign(a0));
	  }
	A0 zz = log(x+sqrt(oneplus(x2)));
	return b_xor(select(lthalf, z, zz), bitofsign(a0));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension, class Info>
  struct call<asinh_,tag::simd_(tag::arithmetic_,Extension),double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
        A0 xx, sign;
	//	bf::tie(sign, xx)= sign_and_abs(a0);
	xx =  abs(a0);
	sign =  bitofsign(a0);
        const A0 Infmask       = is_inf(xx);
        const A0 x2            = sqr(xx);
        return b_xor(seladd(is_equal(xx, Inf<A0>()),
			    log1p(xx+x2/oneplus(sqrt(oneplus(x2)))),
			    xx
			    ),
		     sign
		     );
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension, class Info>
  struct call<asinh_,tag::simd_(tag::arithmetic_,Extension),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::asinh(tofloat(a0));
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010
