//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BESSEL_FUNCTION_SIMD_COMMON_J0_HPP_INCLUDED
#define NT2_TOOLBOX_BESSEL_FUNCTION_SIMD_COMMON_J0_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/digits.hpp>
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
  struct validate<j0_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      meta::is_real_convertible<A0>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute j0(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<j0_,
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
      A0 lt2 = lt(x, Two<A0>());
      if (all(lt2))
	return branch1(x);
      else
	return select (lt2, branch1(x), branch2(x));
      // as branch1 is quick there is no need for an "else if" case
      // computing only branch2,  this probably due to the double pipeline
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, double)
    {
	return map(functor<j0_>(), a0);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,       arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type; 
      return nt2::j0(tofloat(a0)); 
    }
    private:

    template < class A0 > static inline A0 branch1(const A0 & x)
    {
      typedef typename meta::scalar_of<A0>::type stype; 
      const A0 z = sqr(x);
      return (z-single_constant<A0,0x40b90fdc> ())*
	horner< NT2_HORNER_COEFF_T(stype, 5,
				 (0xb382511c,
				  0x36d660a0,
				  0xb9d01fb1,
				  0x3c5a6271,
				  0xbe3110a6
				  ) ) > (z);
    }
    template < class A0 > static inline A0 branch2(const A0 & x)
    {
      typedef typename meta::scalar_of<A0>::type stype; 
      A0 q = rec(x);
      A0 w = sqrt(q);
      A0 p3 = w *
	horner< NT2_HORNER_COEFF_T(stype, 8,
			       (0xbd8c100e,
				0x3e3ef887,
				0xbe5ba616,
				0x3df54214,
				0xbb69539e,
				0xbd4b8bc1,
				0xb6612dc2,
				0x3f4c422a
				) ) > (q);

       w = sqr(q);
       A0 xn =  q*
          horner< NT2_HORNER_COEFF_T(stype, 8,
			       (0x4201aee0,
				0xc2113945,
				0x418c7f6a,
				0xc09f3306,
				0x3f8040aa,
				0xbe46a57f,
				0x3d84ed6e,
				0xbdffff97
				) ) > (w)-Pio_4<A0>();
      return p3*cos(xn+x);
    }


  };
} }

      
#endif
