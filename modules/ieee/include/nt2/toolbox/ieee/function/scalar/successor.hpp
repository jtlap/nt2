//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_SUCCESSOR_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_SUCCESSOR_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/constant/eps_related.hpp>
#include <boost/fusion/tuple.hpp>

#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/bitinteger.hpp>
#include <nt2/include/functions/bitfloating.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/fast_frexp.hpp>
#include <nt2/include/functions/fast_ldexp.hpp>
#include <nt2/include/functions/is_eqz.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::successor_, tag::cpu_,
                           (A0),
                           (arithmetic_<A0>)
                          )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::successor_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> : meta::strip<A0> {};
    NT2_FUNCTOR_CALL(1)
      {
      if (a0 != Valmax<A0>())
	return  oneplus(a0);
      else
	return Valmax<A0>(); 
      }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::successor_, tag::cpu_,
                           (A0),
                           (real_<A0>)
                          )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::successor_(tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> : meta::strip<A0> {};
    NT2_FUNCTOR_CALL(1)
    {
      return a0==Inf<A0>() ? a0 : bitfloating(oneplus(bitinteger(a0)));
    }
  };
} }

NT2_REGISTER_DISPATCH(tag::successor_, tag::cpu_,
                           (A0)(A1),
                           (arithmetic_<A0>)(integer_<A1>)
                          )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::successor_(tag::arithmetic_, tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
      struct result<This(A0, A1)> : meta::strip<A0> {};
    NT2_FUNCTOR_CALL(2)
      {
      if (Valmax<A0>()-nt2::abs(a1) <  a0) return Valmax<A0>(); 
      return a0+nt2::abs(a1);
      }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::successor_, tag::cpu_,
		      (A0)(A1),
		      (real_<A0>)(integer_<A1>)
                          )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::successor_(tag::real_, tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
      struct result<This(A0, A1)> : meta::strip<A0> {};
    NT2_FUNCTOR_CALL(2)
    {
       return a0==Inf<A0>() ? a0 : bitfloating(bitinteger(a0)+nt2::abs(a1));
    }

  };
} }

#endif
// modified by jt the 26/12/2010
// modified manually by jt the 02/01/2011 
