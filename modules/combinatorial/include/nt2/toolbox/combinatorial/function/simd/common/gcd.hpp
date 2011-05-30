//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_COMBINATORIAL_FUNCTION_SIMD_COMMON_GCD_HPP_INCLUDED
#define NT2_TOOLBOX_COMBINATORIAL_FUNCTION_SIMD_COMMON_GCD_HPP_INCLUDED
#include <nt2/include/constants/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/round2even.hpp>
#include <nt2/include/functions/rem.hpp>
#include <nt2/include/functions/any.hpp>
#include <nt2/include/functions/bitwise_ornot.hpp>
#include <nt2/include/functions/is_flint.hpp>


#ifdef NT2_SIMD_DETECTED
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::gcd_, tag::cpu_,
                      (A0)(X),
                      ((simd_<arithmetic_<A0>,X>))
                      ((simd_<arithmetic_<A0>,X>))
                     );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::gcd_(tag::simd_<tag::arithmetic_, X> ,
                        tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      A0 a = a0, b = a1;
      A0 t= is_nez(b);
      while (nt2::any(t))
      {
        A0 r = t&rem(a, b);
        a = sel(t, b, a);
        b = r;
        t= is_nez(b);
      }
      return a;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::gcd_, tag::cpu_,
                      (A0)(X),
                      ((simd_<real_<A0>,X>))
                      ((simd_<real_<A0>,X>))
                     );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::gcd_(tag::simd_<tag::real_, X> ,
                        tag::simd_<tag::real_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      A0 ints = b_and(is_flint(a1), is_flint(a0)); 
      A0 a =  b_and(round2even(a0),ints); 
      A0 b =  b_and(round2even(a1),ints);
      A0 t= is_nez(b);
      while (nt2::any(t))
      {
        A0 r = b_and(t, rem(a, b));
        a = sel(t, b, a);
        b = r;
        t= is_nez(b);
      }
      return b_ornot(round2even(a), ints);
    }
  };
} }
#endif

#endif
// modified by jt the 05/01/2011
