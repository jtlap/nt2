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
#include <nt2/sdk/functor/preprocessor/call.hpp>

#define LOCAL_CALL_INT(TAG, SEL, VAL)                               \
template<class Dummy>                                               \
struct call< TAG(tag::target_<SEL> ), tag::cpu_, Dummy>  : callable \
{                                                                   \
  template<class Sig> struct result;                                \
  template<class This, class A0>                                    \
  struct  result<This(A0)>  : meta::strip<A0>::type {};             \
  NT2_FUNCTOR_CALL(1)                                               \
  {                                                                 \
    typedef typename  NT2_RETURN_TYPE(1)::type type;                \
    return splat<type>(VAL);                                        \
  }                                                                 \
}                                                                   \
/**/

#define LOCAL_CALL(TAG, SEL, VAL)                                   \
template<class Dummy>                                               \
struct call< TAG(tag::target_<SEL>), tag::cpu_, Dummy>  : callable  \
{                                                                   \
  template<class Sig> struct result;                                \
  template<class This, class A0>                                    \
  struct  result<This(A0)>  : meta::strip<A0>::type {};             \
  NT2_FUNCTOR_CALL(1)                                               \
  {                                                                 \
    typedef typename  NT2_RETURN_TYPE(1)::type type;                \
    typename meta::from_bits<type>::type const that = {VAL};        \
    return splat<typename A0::type>(that.value);                    \
  }                                                                 \
}                                                                   \
/**/

#define LOCAL_CONST(TAG, VD, VF,VI)                                       \
NT2_REGISTER_DISPATCH(TAG,tag::cpu_,(A0), (target_< double_<A0>      > ) ) \
NT2_REGISTER_DISPATCH(TAG,tag::cpu_,(A0), (target_< float_<A0>       > ) ) \
NT2_REGISTER_DISPATCH(TAG,tag::cpu_,(A0), (target_< arithmetic_<A0>  > ) ) \
namespace nt2 { namespace ext                                             \
{                                                                         \
  LOCAL_CALL(TAG, tag::double_        , VD);                              \
  LOCAL_CALL(TAG, tag::float_         , VF);                              \
  LOCAL_CALL_INT(TAG, tag::arithmetic_, VI);                              \
} }                                                                       \
/**/


LOCAL_CONST(tag::eps__            ,0x3cb0000000000000LL,0X34000000,1);
LOCAL_CONST(tag::half_eps__       ,0x3ca0000000000000ll,0x33800000,1);
LOCAL_CONST(tag::_3_x_eps_        ,0x3CC8000000000000ll,0x34c00000,1);
LOCAL_CONST(tag::sqrt_eps_        ,0x3e50000000000000ll,0x39b504f3,3);
LOCAL_CONST(tag::forth_root_eps_  ,0x3f20000000000000ll,0x3c9837f0,1);
LOCAL_CONST(tag::third_root_eps_  ,0x3ed965fea53d6e42ll,0x3ba14518,1);
LOCAL_CONST(tag::mlog_eps_2_      ,0x403205966f2b4f13ll,0x40ff1402,0);
LOCAL_CONST(tag::min_denormal_    ,0x1ll               ,0x1       ,1);
LOCAL_CONST(tag::smallest_pos_val_,0x0010000000000000LL,0x00800000,1);

#undef LOCAL_CALL_INT
#undef LOCAL_CONST
#undef LOCAL_CALL

#endif
