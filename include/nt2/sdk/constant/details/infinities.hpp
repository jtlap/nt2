/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_DETAILS_INFINITIES_HPP_INCLUDED
#define NT2_SDK_CONSTANT_DETAILS_INFINITIES_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Base class for generating an integral constant
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/from_bits.hpp>
#include <nt2/sdk/constant/splat.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace nt2 { namespace constants
{
    struct inf_ 	{};
    struct m_inf_       {}; 
} }

namespace nt2 {
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::inf_         , Inf         )
  NT2_CONSTANT_IMPLEMENTATION(nt2::constants::m_inf_       , Minf        )
}

namespace nt2 { namespace functors
{
  template<class Category,class Info>
  struct  call<constants::inf_,tag::constant_(Category),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>::type {};

    NT2_FUNCTOR_CALL_DISPATCH ( 1
                              , typename meta::scalar_of<typename A0::type>::type
                              , ( 4, (double, float, unsigned_, signed_) )
                              )
															
    NT2_FUNCTOR_CALL_EVAL_IF(1,unsigned_)
    {
      typedef typename meta::scalar_of<typename A0::type>::type bits;
      return splat<typename A0::type>(~bits(0));
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1,signed_)
    {
      typedef typename meta::scalar_of<typename A0::type>::type bits;
      return splat<typename A0::type>(~(1ULL << (8*sizeof(bits)-1)));
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1,float)
    {
      return splat<typename A0::type>(0x7F800000);
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1,double)
    {
      return splat<typename A0::type>(0x7FF0000000000000LL);
    }
  };

  template<class Category,class Info>
  struct  call<constants::m_inf_,tag::constant_(Category),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>::type {};

    NT2_FUNCTOR_CALL_DISPATCH ( 1
                              , typename meta::scalar_of<typename A0::type>::type
                              , ( 4, (double, float, unsigned_, signed_) )
                              )
															
    NT2_FUNCTOR_CALL_EVAL_IF(1,unsigned_)
    {
      typedef typename meta::scalar_of<typename A0::type>::type bits;
      return splat<typename A0::type>(0);
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1,signed_)
    {
      typedef typename meta::scalar_of<typename A0::type>::type bits;
      return splat<typename A0::type>(1ULL << (8*sizeof(bits)-1));
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1,float)
    {
      return splat<typename A0::type>(0xFF800000);
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1,double)
    {
      return splat<typename A0::type>(0xFFF0000000000000LL);
    }
  };
} }

#endif
