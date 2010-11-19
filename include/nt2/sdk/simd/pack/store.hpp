/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_STORE_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_STORE_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // When storing pack, we dispatch on the fact the underlying type is SIMD
  //////////////////////////////////////////////////////////////////////////////
  template<class X, class Info>
  struct dispatch<store_,tag::simd_(tag::ast_,X),Info>
  {
    template<class A0,class A1,class A2>
    struct  apply
          : meta::is_native<typename meta::strip<A0>::type::base_type>
    {};
  };

  //////////////////////////////////////////////////////////////////////////////
  // Loading native SIMD is delegated to native<>
  //////////////////////////////////////////////////////////////////////////////
  template<class X, class Info>
  struct  call<store_,tag::simd_(tag::ast_,X), boost::mpl::true_, Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1, class A2>
    struct  result<This(A0,A1,A2)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(3)
    {
      A0 that = store(boost::proto::value(a0).value(),a1,a2);
      return that;
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  // Loading emulated SIMD is memcpy
  //////////////////////////////////////////////////////////////////////////////
  template<class X, class Info>
  struct  call<store_,tag::simd_(tag::ast_,X), boost::mpl::false_, Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1, class A2>
    struct  result<This(A0,A1,A2)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(3)
    {
      for(typename A0::size_type i=0;i<A0::static_size;++i)
        a1[A0::static_size*a2+i] = a0[i];
      return a0;
    }
  };
} }

#endif
