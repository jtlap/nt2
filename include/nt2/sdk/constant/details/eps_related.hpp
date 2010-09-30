/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_DETAILS_EPS_RELATED_HPP_INCLUDED
#define NT2_SDK_CONSTANT_DETAILS_EPS_RELATED_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Base class for generating an EPS related constant
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/from_bits.hpp>
#include <nt2/sdk/constant/splat.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

#define LOCAL_CONST(TAG, DOUBLE, FLOAT, INT)				\
  template<class Category,class Info>					\
  struct  call<constants::TAG,tag::constant_(Category),Info>		\
  {									\
    template<class Sig> struct result;					\
    template<class This,class A0>					\
      struct result<This(A0)> : meta::strip<A0>::type {};		\
      									\
    NT2_FUNCTOR_CALL_DISPATCH ( 1					\
		, typename meta::scalar_of<typename A0::type>::type     \
		, (3, (double, float, arithmetic_) )	                \
				)					\
      									\
    NT2_FUNCTOR_CALL_EVAL_IF(1,arithmetic_)				\
      {									\
	return splat<typename A0::type>(INT);				\
      }									\
    									\
    NT2_FUNCTOR_CALL_EVAL_IF(1,float)					\
      {									\
	meta::from_bits<float>::type const that = {FLOAT};		\
	return splat<typename A0::type>(that.value);			\
      }									\
    									\
    NT2_FUNCTOR_CALL_EVAL_IF(1,double)					\
      {									\
	meta::from_bits<double>::type const that = {DOUBLE};		\
	return splat<typename A0::type>(that.value);			\
      }									\
  }									\
/**/

namespace nt2 { namespace functors
{
  LOCAL_CONST(eps__          ,0x3CB00000FFFFFFFFLL,0x34000000,1); 
  LOCAL_CONST(half_eps__     ,0x3ca0000000000000ll,0x33800000,1); 
  LOCAL_CONST(_3_x_eps_      ,0x3cde03af9ee75615ll,0x34c00000,1); 
  LOCAL_CONST(sqrt_eps_      ,0x3e50000000000000LL,0x39b504f3,3); 
  LOCAL_CONST(forth_root_eps_,0x3f20000000000000ll,0x3c9837f0,1); 
  LOCAL_CONST(third_root_eps_,0x3ed965fea53d6e42ll,0x3ba14518,1);
  LOCAL_CONST(mlog_eps_2_    ,0x403205966f2b4f13LL,0x40ff1402,0); 
} }

#undef LOCAL_CONST

#endif
