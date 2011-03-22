//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_FUZZY_FUNCTION_SIMD_COMMON_FUZZY_GREATER_OR_EQUAL_HPP_INCLUDED
#define NT2_TOOLBOX_FUZZY_FUNCTION_SIMD_COMMON_FUZZY_GREATER_OR_EQUAL_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/abs.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::fuzzy_greater_or_equal_, tag::cpu_,
                                         (A0)(X),
                                         ((simd_<arithmetic_<A0>,X>))
                                         ((simd_<arithmetic_<A0>,X>))
                                         ((simd_<arithmetic_<A0>,X>))
                                        );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::fuzzy_greater_or_equal_(tag::simd_<tag::arithmetic_, X> ,
                                           tag::simd_<tag::arithmetic_, X> ,
                                           tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(3)
    {
      return ge(a0,a1-max(abs(a0),abs(a1))*a2);
    }

  };
} }

#endif
// modified by jt the 05/01/2011
