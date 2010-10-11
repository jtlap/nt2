//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SIMD_COMMON_NTHROOT_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SIMD_COMMON_NTHROOT_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/meta/size.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/powi.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/rec.hpp>


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<nthroot_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : 
      boost::mpl::and_<meta::is_real_convertible<A0>,
		       meta::has_same_size<A0, A1, meta::scalar_of < boost::mpl::_> >, 
		       meta::is_integral<A1> >{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute nthroot(const A0& a0, const A0& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<nthroot_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      typename nt2::meta::scalar_of<A0>::type,
      (2, (real_,arithmetic_))
    )
    NT2_FUNCTOR_CALL_EVAL_IF(2,       real_)
    {
      A0 x =  abs(a0);
      A0 aa1 = tofloat(a1);
      A0 y =nt2::pow(x,rec(aa1));
      y = seladd(isnez(y), y, - (powi(y, a1) - x)/(aa1* powi(y, sub(a1, One<A1>()))));
      // Correct numerical errors (since, e.g., 64^(1/3) is not exactly 4)
      // by one iteration of Newton's method
      return  b_and(isnez(a0),
		    sel(iseq(a1, One<A1>()),
			a0,
			sel(b_and(iseven(a1), isltz(a0)),
			    Nan<A0>(),
			    y)
			)
		    );
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,       arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type type; 
      return nt2::nthroot(tofloat(a0), a1);
    }
  };
} }

      
#endif
