//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_NEXTPOW2_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_NEXTPOW2_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/frexp.hpp>
#include <nt2/include/functions/popcnt.hpp>
#include <nt2/include/functions/firstbitset.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for nextpow2

  /////////////////////////////////////////////////////////////////////////////
  // Compute nextpow2(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<nextpow2_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      typename nt2::meta::scalar_of<A0>::type,
      (2, (real_,arithmetic_))
    )
      NT2_FUNCTOR_CALL_EVAL_IF(1,real_)
      {
	typedef typename meta::as_integer<A0>::type int_type;
	A0 m;
	int_type p;
	boost::fusion::tie(m, p) = frexp(abs(a0));
	return tofloat(seladd(is_equal(m, Half<A0>()), p, One<int_type>()));
      }
      NT2_FUNCTOR_CALL_EVAL_IF(1,arithmetic_)
      {
	return seladd(is_not_equal(popcnt(abs(a0)),One<A0>()), simd::native_cast<A0>(firstbitset(abs(a0))), One<A0>());
	//return a0;  //TO DO
	//        return firstbitset(a0); 
// 	const A0 tmp = nt2::log2(abs(a0));
// 	return seladd(islt(exp2(tmp), abs(a0)), tmp, One<A0>());
      }

  };
} }

      
#endif
