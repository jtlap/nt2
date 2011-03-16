//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_EXPONENT_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_EXPONENT_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/include/functions/is_invalid.hpp>

#include <nt2/include/functions/shri.hpp>
#include <nt2/include/functions/exponentbits.hpp>
#include <nt2/include/functions/is_nez.hpp>

#include <nt2/toolbox/ieee/details/math.hpp>

#ifdef NT2_TOOLBOX_IEEE_HAS_ILOGB
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::exponent_, tag::cpu_,
                          (A0),
                          (double_<A0>)
                         )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::exponent_(tag::double_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0, signed>{};

    NT2_FUNCTOR_CALL(1)
    {
      if (is_invalid(a0)) return Zero<A0>(); 
      return a0 ? ::ilogb(a0) : Zero<A0>();
    }
  };
} }
#endif

#ifdef NT2_TOOLBOX_IEEE_HAS_ILOGBF
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::exponent_, tag::cpu_,
                          (A0),
                          (float_<A0>)
                         )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::exponent_(tag::float_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0, signed>{};

    NT2_FUNCTOR_CALL(1)
    {
      if (is_invalid(a0)) return Zero<A0>(); 
      return a0 ? ::ilogbf(a0) : Zero<A0>();
    }
  };
} }
#endif

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::exponent_, tag::cpu_,
                           (A0),
                           (real_<A0>)
                          );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::exponent_(tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> :meta::as_integer<A0, signed>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type result_type;
      const int nmb= Nbmantissabits<A0>();
      const result_type x = shri(exponentbits(a0), nmb);
      return x-b_and(Maxexponent<A0>(), A0(is_nez(a0)));
    }
  };
} }

#endif
// modified by jt the 26/12/2010
