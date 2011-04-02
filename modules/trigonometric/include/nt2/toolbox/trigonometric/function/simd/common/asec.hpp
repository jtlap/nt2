//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_ASEC_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_ASEC_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/acsc.hpp>
#include <nt2/include/functions/tofloat.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::asec_, tag::cpu_,
                       (A0)(X),
                       ((simd_<arithmetic_<A0>,X>))
                      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::asec_(tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::asec(tofloat(a0));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::asec_, tag::cpu_,
                       (A0)(X),
                       ((simd_<double_<A0>,X>))
                      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::asec_(tag::simd_<tag::double_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      return (Pio_2<A0>()-acsc(a0)); //+double_constant<A0,0x3c91a62633145c07ll >();
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::asec_, tag::cpu_,
                       (A0)(X),
                       ((simd_<float_<A0>,X>))
                      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::asec_(tag::simd_<tag::float_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      return (Pio_2<A0>()-acsc(a0));
    }
  };
} }

#endif
// modified by jt the 05/01/2011