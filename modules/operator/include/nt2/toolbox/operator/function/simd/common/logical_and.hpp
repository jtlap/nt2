//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_COMMON_LOGICAL_AND_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_COMMON_LOGICAL_AND_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/is_not_equal.hpp>
#include <nt2/include/functions/bitwise_and.hpp>
#include <nt2/include/constants/digits.hpp>

NT2_REGISTER_DISPATCH ( tag::logical_and_, tag::cpu_, (A0)(A1)(X)
                      , ((simd_<arithmetic_<A0>,X>))
                        ((simd_<arithmetic_<A1>,X>))
                      );

namespace nt2 { namespace ext
{
  template<class X,class Dummy>
  struct  call< tag::logical_and_ ( tag::simd_<tag::arithmetic_,X> 
                                  , tag::simd_<tag::arithmetic_,X> 
                                  )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)
    {
      return neq(a0, Zero<A0>()) & neq(a1, Zero<A0>());
    }
  };
} }

#endif
