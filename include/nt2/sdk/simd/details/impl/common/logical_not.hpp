/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_COMMON_LOGICAL_NOT_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_COMMON_LOGICAL_NOT_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>

NT2_REGISTER_DISPATCH ( tag::logical_not_, tag::cpu_, (A0)(A1)(X)
                      , ((simd_<arithmetic_<A0>,X>))
                        ((simd_<arithmetic_<A1>,X>))
                      );

namespace nt2 { namespace ext
{
  template<class X,class Dummy>
  struct  call< tag::logical_not_ ( tag::simd_<tag::arithmetic_,X> 
                                  , tag::simd_<tag::arithmetic_,X> 
                                  )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A>
    struct result<This(A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL(1)
    {
      A0 that = { nt2::eq(a0,nt2::Zero<A0>()) };
      return that;
    }
  };
} }

#endif
