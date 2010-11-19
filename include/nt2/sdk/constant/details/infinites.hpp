/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_DETAILS_INFINITES_HPP_INCLUDED
#define NT2_SDK_CONSTANT_DETAILS_INFINITES_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Base class for generating an integral constant
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/from_bits.hpp>
#include <nt2/sdk/constant/splat.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace nt2 { namespace functors
{
  template<class Category,class Info>
  struct  call<constants::inf_,tag::constant_(Category),double,Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      meta::from_bits<double>::type const that = {0x7FF0000000000000LL};
      return splat<typename A0::type>(that.value);
    }
  };

  template<class Category,class Info>
  struct  call<constants::inf_,tag::constant_(Category),float,Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      meta::from_bits<float>::type const that = {0x7F800000};
      return splat<typename A0::type>(that.value);
    }
  };

  template<class Category,class Info>
  struct  call<constants::inf_,tag::constant_(Category),arithmetic_,Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      return Valmax<typename A0::type>();
    }
  };

  template<class Category,class Info>
  struct  call<constants::m_inf_,tag::constant_(Category),double,Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      meta::from_bits<double>::type const that = {0xFFF0000000000000LL};
      return splat<typename A0::type>(that.value);
    }
  };

  template<class Category,class Info>
  struct  call<constants::m_inf_,tag::constant_(Category),float,Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      meta::from_bits<float>::type const that = {0xFF800000};
      return splat<typename A0::type>(that.value);
    }
  };

  template<class Category,class Info>
  struct  call<constants::m_inf_,tag::constant_(Category),arithmetic_,Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>::type {};

    NT2_FUNCTOR_CALL(1) { return Valmin<typename A0::type>(); }
  };
} }

#endif
