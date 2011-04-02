/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_COMMON_NEG_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_COMMON_NEG_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::unary_minus_, tag::cpu_, (A0)(X)
                      , ((simd_<arithmetic_<A0>,X>))
                      );

namespace nt2 { namespace ext
{
  //////////////////////////////////////////////////////////////////////////////
  // unary_minus is 0 - a0
  //////////////////////////////////////////////////////////////////////////////
  template<class X, class Dummy>
  struct  call< tag::unary_minus_( tag::simd_<tag::arithmetic_,X>  )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig>           struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(1)
    {
      A0 that = { Zero<A0>() - a0 };
      return that;
    }
  };
} }

#endif
