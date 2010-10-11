//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_POLYNOMIALS_FUNCTION_SIMD_COMMON_LAGUERRE_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOMIALS_FUNCTION_SIMD_COMMON_LAGUERRE_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/oneplus.hpp>


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<laguerre_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      boost::mpl::and_<meta::is_real_convertible<A1>
                      ,meta::is_scalar<A0>
                      ,meta::is_integral<A0>
      > {};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute laguerre(const A0& a0, const A0& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<laguerre_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :  meta::as_real<A1>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      A1,
      (2, (real_,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(2,  real_)
    {
      A1 p0 = One<A1>();
      if(a0 == 0) return p0;
      A1 p1 = p0-a1;
      A1 p;   
      A1 vc =  One<A1>(); 
      uint32_t c = 1;
      while(c < a0)
      	{
       	  p = p0; 
       	  p0 = p1;
	  A1 vcp1 =  oneplus(vc); 
	  p1 = ((vc + vcp1 - a1) * p0 - vc * p) /vcp1;
      	  vc = vcp1;
      	  ++c; 
      	}
      return p1;
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,       arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type type; 
      return nt2::laguerre(a0, tofloat(a1)); 
    }
//   private:
//     template < class A1>
//     static inline A1 laguerre_next(const  A1& n, const  A1& x, const  A1& Hn, const  A1& Hnm1)
//     {
//       return Two<A1>()*fma(x, Hn, - n * Hnm1);
//     }

  };
} }

      
#endif
