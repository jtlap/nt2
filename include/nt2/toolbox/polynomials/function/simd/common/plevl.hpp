//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_POLYNOMIALS_FUNCTION_SIMD_COMMON_PLEVL_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOMIALS_FUNCTION_SIMD_COMMON_PLEVL_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <boost/fusion/adapted/array.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::plevl_, tag::cpu_,
                        (A0)(A1)(X),
                        ((simd_<arithmetic_<A0>,X>))
                        (fusion_sequence_<A1>)
                       );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::plevl_(tag::simd_<tag::arithmetic_, X> ,
                          tag::fusion_sequence_), 
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
      struct result<This(A0, A1)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      return plevl(tofloat(a0), a1);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::plevl_, tag::cpu_,
		      (A0)(A1)(X),
                        ((simd_<real_<A0>,X>))
                        (fusion_sequence_<A1>)
                       );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::plevl_(tag::simd_<tag::real_, X> ,
                          tag::fusion_sequence_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
      struct result<This(A0, A1)> :  meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typename A1::const_iterator p = a1.begin();
      A0 ans = a0+nt2::splat<A0>(*p++);
      do
      ans = fma(ans, a0, nt2::splat<A0>(*p));
      while( ++p !=  a1.end());
      return ans;
    }
  };
} }

#endif
// modified by jt the 05/01/2011
