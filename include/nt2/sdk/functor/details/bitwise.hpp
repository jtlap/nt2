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
#include <boost/mpl/bool.hpp>
#include <nt2/sdk/meta/size.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/as_bits.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// bitwise operators on scalar arithmetic types works on real types too
////////////////////////////////////////////////////////////////////////////////
#define NT2_MAKE_BITWISE(TAG,OP)                                \
template<class Info>                                            \
struct  dispatch<TAG,tag::scalar_(tag::arithmetic_),Info>       \
      : boost::mpl::_1 {};                                      \
                                                                \
template<class Info>                                            \
struct validate<TAG,tag::scalar_(tag::arithmetic_),Info>        \
{                                                               \
  template<class Sig> struct result;                            \
  template<class This,class A0,class A1>                        \
  struct result<This(A0,A1)> :  meta::has_same_size<A0,A1>{};   \
};                                                              \
                                                                \
template<class Hierarchy,class Info>                            \
struct  call<TAG,tag::scalar_(tag::arithmetic_),Hierarchy,Info> \
      : callable                                                \
{                                                               \
  template<class Sig> struct result;                            \
  template<class This,class A0,class A1>                        \
  struct result<This(A0,A1)> : meta::strip<A0> {};              \
  NT2_FUNCTOR_CALL(2)                                           \
  {                                                             \
    typename meta::as_bits<A0>::type t0 = {a0};                 \
    typename meta::as_bits<A1>::type t1 = {a1};                 \
    t0.bits OP t1.bits;                                        \
    return t0.value;                                            \
  }                                                             \
}                                                               \
/**/

namespace nt2 { namespace functors
{
  NT2_MAKE_BITWISE(bitwise_and_, &= );
  NT2_MAKE_BITWISE(bitwise_or_ , |= );
  NT2_MAKE_BITWISE(bitwise_xor_, ^= );

  template<class Info>
  struct  dispatch<complement_,tag::scalar_(tag::arithmetic_),Info>
        : boost::mpl::_1 {};

  template<class Info>
  struct  call<complement_,tag::scalar_(tag::arithmetic_),real_,Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(1)
    {
      typename meta::as_bits<A0>::type t0 = {a0};
      t0.bits = ~t0.bits;
      return t0.value;
    }
  };

  template<class Info>
  struct  call<complement_,tag::scalar_(tag::arithmetic_),fundamental_,Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(1) { return ~a0; }
  };
} }

#undef NT2_MAKE_BITWISE

#endif
