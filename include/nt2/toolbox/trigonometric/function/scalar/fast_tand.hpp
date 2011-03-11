//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_FAST_TAND_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_FAST_TAND_HPP_INCLUDED

#include <nt2/toolbox/trigonometric/function/scalar/impl/trigo.hpp>
//  MIGRATION WARNING you have to provide the file for the previous include from
//  nt2/core/numeric/function/details/scalar/impl/trigo.hpp
//  of the old nt2


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::fast_tand_, tag::cpu_,
                           (A0),
                           (fundamental_<A0>)
                          )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::fast_tand_(tag::fundamental_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      return impl::trig_base<type,degree_tag, fast_tag, tag::not_simd_type>::tana(type(a0));
    }

  };
} }

#endif
// modified by jt the 26/12/2010