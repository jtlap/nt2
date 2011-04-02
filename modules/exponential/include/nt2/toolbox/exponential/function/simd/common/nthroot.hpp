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
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/bitofsign.hpp>




/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::nthroot_, tag::cpu_,
                          (A0)(A1)(X),
                          ((simd_<arithmetic_<A0>,X>))
                          ((simd_<integer_<A0>,X>))
                         );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::nthroot_(tag::simd_<tag::arithmetic_, X> ,
                            tag::simd_<tag::integer_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      return nt2::nthroot(tofloat(a0), a1);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::nthroot_, tag::cpu_,
                          (A0)(A1)(X),
                          ((simd_<real_<A0>,X>))
                          ((simd_<integer_<A1>,X>))
                         );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::nthroot_(tag::simd_<tag::real_, X> ,
                            tag::simd_<tag::integer_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :  meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      A0 x =  nt2::abs(a0);
      A0 aa1 = tofloat(a1);
      A0 y =nt2::pow(x,rec(aa1));
      y = seladd(is_nez(y), y, - (pow(y, a1) - x)/(aa1* pow(y, sub(a1, One<A1>()))));
      // Correct numerical errors (since, e.g., 64^(1/3) is not exactly 4)
      // by one iteration of Newton's method
      return  b_and(is_nez(a0),
		    sel(is_eqz(aa1), One<A0>(), 
			sel(is_equal(a1, One<A1>()),
			    a0,
			    sel(b_and(is_even(a1), is_ltz(a0)),
				Nan<A0>(),
				b_or(y, bitofsign(a0))
				)
			    )
			)
		    );
    }
  };
} }

#endif
// modified by jt the 05/01/2011
