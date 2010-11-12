//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BESSEL_FUNCTION_SIMD_COMMON_J1_HPP_INCLUDED
#define NT2_TOOLBOX_BESSEL_FUNCTION_SIMD_COMMON_J1_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/all.hpp>



namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<j1_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      meta::is_real_convertible<A0>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute j1(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<j1_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      typename nt2::meta::scalar_of<A0>::type,
      (3, (float,double,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,  float)
    {
      A0 x   =  abs(a0);
      A0 lt2 = lt(x, Two < A0>());
      if (all(lt2))
	return branch1(x);
      else
	return select (lt2, branch1(x), branch2(x));
      // as branch1 is quick there is no need for an "else if" case
      // computing only branch2,  this probably due to the double pipeline
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, double)
    {
	return map(functor<j1_>(), a0);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,       arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type; 
      return nt2::j1(tofloat(a0)); 
    }
    private:

    template < class A0 > static inline A0 branch1(const A0 & x)
    {
      typedef typename meta::scalar_of<A0>::type stype; 
      const A0 z = sqr(x);
      return (z-single_constant<A0,0x416ae95a> ())*x*
	horner< NT2_HORNER_COEFF_T(stype, 5,
				 (0xb1a7a246,
				 0x35214df5,
				 0xb83e7a4f,
				 0x3afdefd1,
				 0xbd0b7da6
				  ) ) > (z);
    }
    template < class A0 > static inline A0 branch2(const A0 & x)
    {
      typedef typename meta::scalar_of<A0>::type stype; 
      A0 q = rec(x);
      A0 w = sqrt(q);
      A0 p3 = w *
	horner< NT2_HORNER_COEFF_T(stype, 8,
				 (0x3d8d98f9,
				  0xbe69f6b3,
				  0x3ea0ad85,
				  0xbe574699,
				  0x3bb21b25,
				  0x3e18ec50,
				  0x36a6f7c5,
				  0x3f4c4229
				  ) ) > (q);
      w = sqr(q);
      A0 xn =  q*
      horner< NT2_HORNER_COEFF_T(stype, 8,
			       (0xc233e16d,
				0x424af04a,
				0xc1c6dca7,
				0x40e72299,
				0xbfc5bd69,
				0x3eb364d9,
				0xbe27bad7,
				0x3ebfffdd
				) ) > (w)-single_constant<A0,0x4016cbe4 > ();
      return p3*cos(xn+x);
    }

  };
} }

      
#endif
