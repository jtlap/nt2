/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_DETAILS_COMMA_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_DETAILS_COMMA_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// comma operator implementation
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/bool.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // Whatever the typs, we can always do x,y
  //////////////////////////////////////////////////////////////////////////////
  template<class Category, class Info>
  struct validate<comma_,Category, Info>
  {
    typedef boost::mpl::true_ result_type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Comma basically evaluates its arguments and returns the second one
  //////////////////////////////////////////////////////////////////////////////
  template<class Category, class Info>
  struct call<comma_,Category, Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> { typedef A1 type; };

    NT2_FUNCTOR_CALL(2) { details::ignore_unused(a0); return a1; }
  };
} }

#endif
