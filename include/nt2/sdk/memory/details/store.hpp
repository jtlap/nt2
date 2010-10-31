/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_DETAILS_STORE_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_STORE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// load for scalar types
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/functor/category.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace nt2 { namespace functors
{
  template<class Category, class Info>
  struct  call<store_,tag::scalar_(Category), fundamental_, Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1, class A2>
    struct  result<This(A0,A1,A2)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(3)
    {
      A1 that = a1;
      std::advance(that,a2);
      return *that = a0;
    }
  };
} }

#endif
