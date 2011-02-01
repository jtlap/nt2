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

NT2_REGISTER_DISPATCH ( tag::comma_,tag::cpu_
                      , (A0)(A1)
                      , (unspecified_<A0>)(unspecified_<A1>)
                      );

namespace nt2 { namespace ext
{
  //////////////////////////////////////////////////////////////////////////////
  // Comma basically evaluates its arguments and returns the second one
  //////////////////////////////////////////////////////////////////////////////
  template<class Dummy>
  struct  call< tag::comma_(tag::unspecified_,tag::unspecified_)
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A1> {};

    NT2_FUNCTOR_CALL(2) { details::ignore_unused(a0); return a1; }
  };
} }

#endif
