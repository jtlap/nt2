/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_DETAILS_VALMIN_HPP_INCLUDED
#define NT2_SDK_CONSTANT_DETAILS_VALMIN_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Base class for generating valmin constant
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/from_bits.hpp>
#include <nt2/sdk/constant/splat.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace nt2 { namespace functors
{
  template<class Category,class Info>
  struct  call<constants::val_min_,tag::constant_(Category),unsigned_, Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<typename A0::type>::type base;
      return splat<typename A0::type>(static_cast<base>(0));
    }
  };

  template<class Category,class Info>
  struct  call<constants::val_min_,tag::constant_(Category),int8_t, Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<typename A0::type>::type base;
      return splat<typename A0::type>(static_cast<base>(0x80));
    }
  };

  template<class Category,class Info>
  struct  call<constants::val_min_,tag::constant_(Category),int16_t, Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<typename A0::type>::type base;
      return splat<typename A0::type>(static_cast<base>(0x8000));
    }
  };

  template<class Category,class Info>
  struct  call<constants::val_min_,tag::constant_(Category),int32_t, Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<typename A0::type>::type base;
      return splat<typename A0::type>(static_cast<base>(0x80000000));
    }
  };

  template<class Category,class Info>
  struct  call<constants::val_min_,tag::constant_(Category),int64_t, Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<typename A0::type>::type base;
      return splat<typename A0::type>(static_cast<base>(0x8000000000000000LL));
    }
  };

  template<class Category,class Info>
  struct  call<constants::val_min_,tag::constant_(Category),double, Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      meta::from_bits<double>::type const that = {0xffefffffffffffffLL};
      return splat<typename A0::type>(that.value);
    }
  };

  template<class Category,class Info>
  struct  call<constants::val_min_,tag::constant_(Category),float, Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      meta::from_bits<float>::type const that = {0xff7fffff};
      return splat<typename A0::type>(that.value);
    }
  };
} }

#endif

