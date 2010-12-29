/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_DETAILS_BITWISE_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_DETAILS_BITWISE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// bitwise operators extended implementation
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/as_bits.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// bitwise operators on scalar arithmetic types works on real types too
// This behavior is tied to the prefix form. The traditionnal operator do
// not has this property on scalar value.
////////////////////////////////////////////////////////////////////////////////
#define NT2_MAKE_BITWISE(TAG,OP)                                          \
NT2_REGISTER_DISPATCH(TAG,tag::cpu_,(A0)(A1),(bool_<A0>)(bool_<A1>))      \
NT2_REGISTER_DISPATCH(TAG,tag::cpu_,(A0)(A1),(type8_<A0>)(type8_<A1>))    \
NT2_REGISTER_DISPATCH(TAG,tag::cpu_,(A0)(A1),(type16_<A0>)(type16_<A1>))  \
NT2_REGISTER_DISPATCH(TAG,tag::cpu_,(A0)(A1),(type32_<A0>)(type32_<A1>))  \
NT2_REGISTER_DISPATCH(TAG,tag::cpu_,(A0)(A1),(type64_<A0>)(type64_<A1>))  \
namespace nt2 { namespace ext                                             \
{                                                                         \
  template<class Dummy>                                                   \
  struct  call<TAG(tag::type8_,tag::type8_), tag::cpu_, Dummy>            \
        : callable                                                        \
  {                                                                       \
    template<class Sig> struct result;                                    \
    template<class This,class A0,class A1>                                \
    struct result<This(A0,A1)> : meta::strip<A0> {};                      \
    NT2_FUNCTOR_CALL(2)                                                   \
    {                                                                     \
      typename meta::as_bits<A0>::type t0 = {a0};                         \
      typename meta::as_bits<A1>::type t1 = {a1};                         \
      t0.bits OP t1.bits;                                                 \
      return t0.value;                                                    \
    }                                                                     \
  };                                                                      \
                                                                          \
  template<class Dummy>                                                   \
  struct  call<TAG(tag::bool_   , tag::bool_  ), tag::cpu_, Dummy>        \
        : call<TAG(tag::type8_  , tag::type8_ ), tag::cpu_, Dummy>        \
  {};                                                                     \
  template<class Dummy>                                                   \
  struct  call<TAG(tag::type16_ , tag::type16_), tag::cpu_, Dummy>        \
        : call<TAG(tag::type8_  , tag::type8_ ), tag::cpu_, Dummy>        \
  {};                                                                     \
                                                                          \
  template<class Dummy>                                                   \
  struct  call<TAG(tag::type32_ , tag::type32_), tag::cpu_, Dummy>        \
        : call<TAG(tag::type8_  , tag::type8_ ), tag::cpu_, Dummy>        \
  {};                                                                     \
                                                                          \
  template<class Dummy>                                                   \
  struct  call<TAG(tag::type64_ , tag::type64_), tag::cpu_, Dummy>        \
        : call<TAG(tag::type8_  , tag::type8_ ), tag::cpu_, Dummy>        \
  {};                                                                     \
} }                                                                       \
/**/

NT2_MAKE_BITWISE(tag::bitwise_and_, &= )
NT2_MAKE_BITWISE(tag::bitwise_or_ , |= )
NT2_MAKE_BITWISE(tag::bitwise_xor_, ^= )

#undef NT2_MAKE_BITWISE

#endif
