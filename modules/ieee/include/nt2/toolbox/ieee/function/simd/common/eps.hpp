//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_EPS_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_EPS_HPP_INCLUDED
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/exponent.hpp>
#include <nt2/include/functions/abs.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::eps_, tag::cpu_,
                      (A0)(X),
                      ((simd_<arithmetic_<A0>,X>))
                     );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::eps_(tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>  : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      details::ignore_unused(a0);
      return One<A0>();
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::eps_, tag::cpu_,
                      (A0)(X),
                      ((simd_<real_<A0>,X>))
                     );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::eps_(tag::simd_<tag::real_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>  : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
      {
      typedef typename meta::as_integer<A0, signed>::type        int_type;
      const A0 a = nt2::abs(a0);
      return seladd(is_invalid(a),
                select(is_less(a, Smallestposval<A0>()),
                     Mindenormal<A0>(),
                     ldexp(One<A0>(), exponent(a)-Nbmantissabits<A0>())
                     ),
                Nan<A0>());
      }
  };
} }

#endif
// modified by jt the 04/01/2011