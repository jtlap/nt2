/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_DETAILS_SIGNMASK_HPP_INCLUDED
#define NT2_SDK_CONSTANT_DETAILS_SIGNMASK_CONSTANT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Base class for generating an integral constant
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/constant/splat.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace nt2 { namespace functors
{
  template<class Category,class Info>
  struct  call<constants::signmask_,tag::constant_(Category),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>::type {};

    NT2_FUNCTOR_CALL_DISPATCH ( 1
                              , typename meta::scalar_of<typename A0::type>::type
                              , ( 7 , ( unsigned_
                                      , int8_t,int16_t,int32_t,int64_t
                                      , double, float
                                      )
                                )
                              )

    NT2_FUNCTOR_CALL_EVAL_IF(1,unsigned_)
    {
      return splat<typename A0::type>(0);
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1,int8_t)
    {
      return splat<typename A0::type>(0x80);
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1,int16_t)
    {
      return splat<typename A0::type>(0x8000);
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1,int32_t)
    {
      return splat<typename A0::type>(0x80000000);
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1,int64_t)
    {
      return splat<typename A0::type>(0x8000000000000000LL);
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1,float)
    {
      typedef union { nt2::uint32_t bits; float val; } type;
      type const that = {0x80000000};
      return splat<typename A0::type>(that.val);
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1,double)
    {
      typedef union { nt2::uint64_t bits; double val; } type;
      type const that = {0x8000000000000000LL};
      return splat<typename A0::type>(that.val);
    }
  };
} }

#endif
