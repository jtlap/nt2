//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ELLIPTIC_FUNCTION_SIMD_COMMON_ELLPE_HPP_INCLUDED
#define NT2_TOOLBOX_ELLIPTIC_FUNCTION_SIMD_COMMON_ELLPE_HPP_INCLUDED
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/tofloat.hpp>


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<ellpe_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      meta::is_real_convertible<A0>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute ellpe(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<ellpe_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      typename nt2::meta::scalar_of<A0>::type,
      (3, (float,double, arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,  float)
    {
      typedef typename meta::scalar_of<A0>::type sA0; 
      A0 temp = horner< NT2_HORNER_COEFF_T(sA0, 11,
					 (0x392102f5, 
					  0x3b246c1b, 
					  0x3c0e578f, 
					  0x3c2fe240, 
					  0x3bfebca9, 
					  0x3bf882cf, 
					  0x3c3d8b3f, 
					  0x3cb2d89a, 
					  0x3d68ac90, 
					  0x3ee2e430, 
					  0x3f800000) ) > (a0)
      -log(a0)*a0*horner< NT2_HORNER_COEFF_T(sA0, 10,
					   (0x38098de4, 
					    0x3a84557e, 
					    0x3bd53114, 
					    0x3c8a54f6, 
					    0x3cd67118, 
					    0x3d0925e1, 
					    0x3d2ef92b, 
					    0x3d6fffe9, 
					    0x3dc00000, 
					    0x3e800000
					    ) ) > (a0);
      return select(is_eqz(a0), One<A0>(), b_or(temp, b_or(gt(a0, One<A0>()), is_ltz(a0)))); 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, double)
    {
      return map(functor<ellpe_>(), a0);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,       arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type; 
      return nt2::ellpe(tofloat(a0));
    }
   };
} }

      
#endif
