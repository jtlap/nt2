/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_STORE_HPP_INCLUDED
#define NT2_SDK_MEMORY_STORE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Store a value in memory functor and function
// Documentation: http://nt2.lri.fr/sdk/memory/function/store.html
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/functor/functor.hpp>
#include <nt2/sdk/meta/is_iterator.hpp>
#include <nt2/sdk/functor/preprocessor/function.hpp>

namespace nt2 { namespace functors
{
  struct store_ {};

  //////////////////////////////////////////////////////////////////////////////
  // We only store into an iterator
  //////////////////////////////////////////////////////////////////////////////
  template<class Category, class Info>
  struct  validate< store_, Category, Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1,class A2>
    struct  result<This(A0,A1,A2)>
      : boost::mpl::and_< meta::is_iterator<typename meta::strip<A1>::type>
                        , boost::is_integral<typename meta::strip<A2>::type>
                        >
    {};
  };
} }

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // store category is given by T
  //////////////////////////////////////////////////////////////////////////////
  template<class Info,class A0,class A1,class A2>
  struct  categorize<functors::store_,Info,A0,A1,A2>
  {
    typedef typename meta::strip<A0>::type              base;
    typedef typename meta::category_of<base>::type::tag type;
  };
} }

namespace nt2
{
  NT2_FUNCTION_IMPLEMENTATION(functors::store_,store,3)
}

#include <nt2/sdk/memory/details/store.hpp>

#endif
