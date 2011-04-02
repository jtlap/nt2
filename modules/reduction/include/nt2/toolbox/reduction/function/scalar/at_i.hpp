//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SCALAR_AT_I_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SCALAR_AT_I_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ati_, tag::cpu_,
                    (A0)(A1),
                    (fundamental_<A0>)(integer_<A1>)
                   )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::ati_(tag::fundamental_,tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0>  {};


    NT2_FUNCTOR_CALL(2)
    {
      details::ignore_unused(a1);
      return a0;
    };

  };
} }

#endif
