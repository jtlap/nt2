/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_NATIVE_CONSTANTS_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_NATIVE_CONSTANTS_HPP_INCLUDED

#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/boolean.hpp>
#include <nt2/sdk/simd/details/impl/splat.hpp>

////////////////////////////////////////////////////////////////////////////////
// in SIMD, True is not !0 but ~0 whatever the type
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // When generating true_, dispatch on integral/real of target
  //////////////////////////////////////////////////////////////////////////////
  template<class C, class X, class Info>
  struct dispatch<constants::true_,tag::simd_(C,X),Info>
  {
    template<class A0>
    struct  apply
          : meta::scalar_of<typename meta::strip<A0>::type::type>
    {};
  };

  template<class C, class X,class Info>
  struct  call< constants::true_, tag::constant_(tag::simd_(C,X))
              , real_           , Info
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)> : meta::strip<A0>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<typename A0::type>::type stype;
      typedef typename meta::as_integer<stype>::type int_type;
      typedef union { int_type bits; stype value; } type;
      type const that = { ~int_type(0) };
      return splat<typename A0::type>(that.value);
    }
  };

  template<class C, class X,class Info>
  struct  call< constants::true_, tag::constant_(tag::simd_(C,X))
              , integer_        , Info
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)> : meta::strip<A0>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<typename A0::type>::type type;
      type const that = ~type(0);
      return splat<typename A0::type>(that);
    }
  };
} }
#endif
