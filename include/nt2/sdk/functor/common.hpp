/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_COMMON_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_COMMON_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Commonly used generic functor
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/is_scalar.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/functor/functor.hpp>
#include <nt2/sdk/functor/category.hpp>
#include <nt2/sdk/functor/preprocessor/function.hpp>

namespace nt2 { namespace functors
{
  struct genmask_ {};
} }

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // Turn true/false into ~0/0
  //////////////////////////////////////////////////////////////////////////////
  template<class Category, class Info>
  struct call<genmask_,Category,Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>::type {};

    NT2_FUNCTOR_CALL_DISPATCH ( 1
                              , typename nt2::meta::scalar_of<A0>::type
                              , (2, (real_,arithmetic_))
                              )

    NT2_FUNCTOR_CALL_EVAL_IF(1, real_)        { return a0 ? Nan<A0>()  : Zero<A0>(); }
    NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)  { return a0 ? Mone<A0>() : Zero<A0>(); }
  };
} }

#endif
