//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_COMMON_IS_NEZ_HPP_INCLUDED
#define NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_COMMON_IS_NEZ_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::is_nez_, tag::cpu_,
                         (A0)(X),
                         ((simd_<arithmetic_<A0>,X>))
                        );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::is_nez_(tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1) {
      return is_not_equal(a0,Zero<A0>());
    }

  };
} }

#endif
// modified by jt the 04/01/2011