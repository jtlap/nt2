/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_CONSTANT_CONSTANTS_DETAILS_IEEE_SPEC_HPP_INCLUDED
#define NT2_TOOLBOX_CONSTANT_CONSTANTS_DETAILS_IEEE_SPEC_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Base class for generating an integral constant
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

#define LOCAL_CALL(TAG, SEL, VAL)                                     \
template<class A0, class Dummy>                                       \
struct implement< TAG( target_< SEL >), tag::cpu_, Dummy>             \
{                                                                     \
  typedef typename as_integer < typename strip<A0>::type::type        \
                              , signed                                \
                              >::type result_type;                    \
  NT2_FUNCTOR_CALL(1)                                                 \
  {                                                                   \
    ignore_unused(a0);                                                \
    return splat<result_type>(VAL);                                   \
  }                                                                   \
}                                                                     \
/**/

#define LOCAL_CONST(TAG, VD, VF)                                              \
NT2_REGISTER_DISPATCH(TAG,tag::cpu_,(A0), (target_<scalar_< double_<A0> > >)) \
NT2_REGISTER_DISPATCH(TAG,tag::cpu_,(A0), (target_<scalar_< float_<A0> > >))  \
LOCAL_CALL(TAG, scalar_< double_<A0> >, VD);                                  \
LOCAL_CALL(TAG, scalar_< float_<A0> >, VF);                                   \
/**/

namespace nt2 { namespace meta
{
  LOCAL_CONST(tag::nb_mantissa_bits_,                  52,         23);
  LOCAL_CONST(tag::nb_exponent_bits_,                  11,          8);
  LOCAL_CONST(tag::max_exponent_    ,                1023,        127);
  LOCAL_CONST(tag::min_exponent_    ,               -1022,       -126);
  LOCAL_CONST(tag::nb_digits_       ,                  53,         24);
  LOCAL_CONST(tag::ldexp_mask_      ,0x7FF0000000000000ll, 0x7F800000);
} }

#undef LOCAL_CONST
#undef LOCAL_CALL

#endif
