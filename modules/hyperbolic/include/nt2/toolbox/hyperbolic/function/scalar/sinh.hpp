//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SCALAR_SINH_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SCALAR_SINH_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/real.hpp>

#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/expm1.hpp>
#include <nt2/include/functions/rec.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::sinh_, tag::cpu_,
                      (A0),
                      (arithmetic_<A0>)
                     )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::sinh_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      if (is_eqz(a0)) return Zero<type>();
      type tmp = nt2::exp(a0);
      return (tmp-rec(tmp))*Half<type>();
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::sinh_, tag::cpu_,
                      (A0),
                      (real_<A0>)
                     )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::sinh_(tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      type tmp = nt2::exp(a0);
      if ( nt2::abs(a0) > 0.6)
      {
        return (tmp-rec(tmp))*Half<A0>();
      }
      else
      {
        return -tmp*nt2::expm1(-(a0+a0))*Half<A0>();
      }
    }
  };
} }

#endif
// modified by jt the 26/12/2010