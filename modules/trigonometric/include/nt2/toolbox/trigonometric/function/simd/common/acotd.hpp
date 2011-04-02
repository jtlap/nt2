//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_ACOTD_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_ACOTD_HPP_INCLUDED
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/include/functions/atand.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/bitofsign.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/bitofsign.hpp>




/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::acotd_, tag::cpu_,
                        (A0)(X),
                        ((simd_<real_<A0>,X>))
                       );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::acotd_(tag::simd_<tag::real_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      A0 s = bitofsign(a0);
      return b_or(sel(is_inf(a0), Zero<A0>(), Ninety<A0>()-b_and(is_nez(a0),nt2::atand(abs(a0))))
		  , s);
	  //      return Ninety<type>()-nt2::atand(tofloat(a0));
    }
  };
} }

NT2_REGISTER_DISPATCH(tag::acotd_, tag::cpu_,
                        (A0)(X),
                        ((simd_<arithmetic_<A0>,X>))
                       );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::acotd_(tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::acotd(tofloat(a0)); 
    }

  };
} }

#endif
// modified by jt the 05/01/2011
