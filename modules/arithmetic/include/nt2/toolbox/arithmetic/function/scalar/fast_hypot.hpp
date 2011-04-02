//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_FAST_HYPOT_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_FAST_HYPOT_HPP_INCLUDED
#include <nt2/sdk/constant/eps_related.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/real.hpp>

#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/ldexp.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::fast_hypot_, tag::cpu_,
                            (A0)(A1),
                            (arithmetic_<A0>)(arithmetic_<A1>)
                           )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::fast_hypot_(tag::arithmetic_,tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      std::tr1::result_of<meta::floating(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      return nt2::fast_hypot(type(a0), type(a1));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::fast_hypot_, tag::cpu_,
                            (A0)(A1),
                            (double_<A0>)(double_<A1>)
                           )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::fast_hypot_(tag::double_,tag::double_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      std::tr1::result_of<meta::floating(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_integer<A0, signed>::type  int_type;
      A0 x =  nt2::abs(a0);
      A0 y =  nt2::abs(a1);
      if (nt2::is_inf(x+y)) return Inf<float>();
      if (nt2::is_nan(x+y)) return Nan<float>();
      if (y > x) std::swap(x, y);
      if (x*Eps<A0>() >=  y) return x;
      return x*nt2::sqrt(One<A0>()+nt2::sqr(y/x));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::fast_hypot_, tag::cpu_,
                            (A0)(A1),
                            (float_<A0>)(float_<A1>)
                           )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::fast_hypot_(tag::float_,tag::float_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      std::tr1::result_of<meta::floating(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      // flibc do that in ::fast_hypotf(a0, a1) in asm with no more speed!
      // proper impl as for double is 30% slower
      return nt2::sqrt(nt2::sqr(double(a0))+nt2::sqr(double(a1)));
    }
  };
} }

#endif
// modified by jt the 26/12/2010