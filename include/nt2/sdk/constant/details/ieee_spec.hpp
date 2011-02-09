/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_DETAILS_IEEE_SPEC_HPP_INCLUDED
#define NT2_SDK_CONSTANT_DETAILS_IEEE_SPEC_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Base class for generating an integral constant
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/constant/splat.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

#define LOCAL_CALL(TAG, SEL, VAL)                                           \
template<class Dummy>                                                       \
struct call< TAG(tag::target_<SEL>), tag::cpu_, Dummy>  : callable          \
{                                                                           \
  template<class Sig> struct result;                                        \
  template<class This, class A0>                                            \
  struct  result<This(A0)>                                                  \
        : meta::as_integer<typename meta::strip<A0>::type::type,signed> {}; \
  NT2_FUNCTOR_CALL(1)                                                       \
  {                                                                         \
    typedef typename  NT2_RETURN_TYPE(1)::type type;                        \
    return splat<type>(VAL);                                                \
  }                                                                         \
}                                                                           \
/**/

#define LOCAL_CONST(TAG, VD, VF)                                        \
NT2_REGISTER_DISPATCH(TAG,tag::cpu_,(A0), (target_< double_<A0> > ) )    \
NT2_REGISTER_DISPATCH(TAG,tag::cpu_,(A0), (target_< float_<A0>  > ) )    \
namespace nt2 { namespace ext                                           \
{                                                                       \
  LOCAL_CALL(TAG, tag::double_, VD);  LOCAL_CALL(TAG, tag::float_, VF); \
} }                                                                     \
/**/

LOCAL_CONST(tag::nb_mantissa_bits_,                  52,         23);
LOCAL_CONST(tag::nb_exponent_bits_,                  11,          8);
LOCAL_CONST(tag::max_exponent_    ,                1023,        127);
LOCAL_CONST(tag::min_exponent_    ,               -1022,       -126);
LOCAL_CONST(tag::nb_digits_       ,                  53,         24);
LOCAL_CONST(tag::ldexp_mask_      ,0x7FF0000000000000ll, 0x7F800000);

#undef LOCAL_CONST
#undef LOCAL_CALL

#endif
