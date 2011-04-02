//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_SINPI_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_SINPI_HPP_INCLUDED
#include <nt2/sdk/details/ignore_unused.hpp>
#include <nt2/sdk/constant/digits.hpp>

#include <nt2/toolbox/trigonometric/function/scalar/impl/trigo.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::sinpi_, tag::cpu_,
                       (A0),
                       (arithmetic_<A0>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::sinpi_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      details::ignore_unused(a0);
      return Zero<A0>();
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::sinpi_, tag::cpu_,
                       (A0),
                       (real_<A0>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::sinpi_(tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
       return impl::trig_base<A0,pi_tag, trig_tag, tag::not_simd_type>::sina(a0);
    }
  };
} }

#endif
// modified by jt the 26/12/2010
