//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_PACK_SUM_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_PACK_SUM_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/simd/pack.hpp>
#include <nt2/sdk/dsl/terminal_of.hpp>

////////////////////////////////////////////////////////////////////////////////
// Implementation when type  is expression of pack
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::sum_, tag::cpu_,
                      (A0)(T)(Card)(Tag)(Sema),
                      ((expr_<A0, domain_< simd::domain<T,Card> >, Tag, Sema>))
                     );

namespace nt2 { namespace ext
{
  template<class T, class Card, class Tag, class Sema, class Dummy>
  struct call<tag::sum_(tag::expr_<simd::domain<T,Card>, Tag, Sema> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> { typedef T type; };

    NT2_FUNCTOR_CALL(1)
    {
      typename boost::mpl::apply< meta::terminal_of<A0>, T>::type  that;
      that = a0;
      return nt2::sum(that.value().value());
    }
  };
} }

#endif
