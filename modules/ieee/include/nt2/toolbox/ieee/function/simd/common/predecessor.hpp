//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_PREDECESSOR_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_PREDECESSOR_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/bitinteger.hpp>
#include <nt2/include/functions/bitfloating.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/fast_frexp.hpp>
#include <nt2/include/functions/fast_ldexp.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/prev.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_ unary
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::predecessor_, tag::cpu_,
                              (A0)(X),
                              ((simd_<arithmetic_<A0>,X>))
                             );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::predecessor_(tag::simd_<tag::arithmetic_, X>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
      {
	return seladd(neq(a0, Valmin<A0>()), a0, Mone<A0>());
      }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_ unary
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::predecessor_, tag::cpu_,
                              (A0)(X),
                              ((simd_<real_<A0>,X>))
                             );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::predecessor_(tag::simd_<tag::real_, X>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
      {
	return prev(a0);
      }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_ 
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::predecessor_, tag::cpu_,
		      (A0)(A1)(X),
                              ((simd_<integer_<A0>,X>))
                              ((simd_<integer_<A1>,X>))
                             );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::predecessor_(tag::simd_<tag::integer_, X> ,
                                tag::simd_<tag::integer_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
      struct result<This(A0, A1)>  : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      return selsub( le(Valmin<A0>()+nt2::abs(a1), a0), a0, nt2::abs(a1));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::predecessor_, tag::cpu_,
		      (A0)(A1)(X),
		      ((simd_<real_<A0>,X>))
		      ((simd_<integer_<A1>,X>))
		      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::predecessor_(tag::simd_<tag::real_, X> ,
                                tag::simd_<tag::integer_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
      struct result<This(A0, A1)>  : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
      {
	return sel(eq(a0, Minf<A0>()), a0,  bitfloating(bitinteger(a0)-nt2::abs(a1)));
//       typedef typename meta::as_integer<A0, signed>::type itype;
//       A0 m;
//       itype expon;
//       const A0 fac =  nt2::abs(tofloat(a1));
//       boost::fusion::tie(m, expon) = fast_frexp(a0);
//       expon =  seladd(is_equal(m, Mhalf<A0>()), expon, Mone<itype>());
//       A0 diff =  fast_ldexp(One<A0>(), expon-Nbdigits<A0>());
//       diff = b_and(sel(is_eqz(diff)||is_eqz(a0),  Mindenormal<A0>(), diff), is_finite(a0));
//       return sel(is_equal(a0, Inf<A0>()), fac*Valmax<A0>(), a0-fac*diff);
      }
  };
} }

#endif
// modified by jt the 04/01/2011
