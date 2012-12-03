//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_TESTS_DETAILS_RUN_HPP_INCLUDED
#define NT2_SDK_UNIT_TESTS_DETAILS_RUN_HPP_INCLUDED

#include <boost/dispatch/meta/terminal_of.hpp>

namespace boost { namespace simd { namespace details
{
  template<class T, class X>
  struct soa_proxy;
} } }

namespace nt2
{
  namespace container
  {
    template<class Expr, class Result>
    struct expression;
  }

  namespace details
  {
    template<class T>
    T& eval(T& t)
    {
      return t;
    }

    template<class T>
    T const& eval(T const& t)
    {
      return t;
    }

    template<class Expr, class Result>
    typename boost::dispatch::meta::terminal_of<Result>::type
    eval(nt2::container::expression<Expr, Result> const& t)
    {
      return t;
    }

    template<class T, class X>
    T eval(boost::simd::details::soa_proxy<T, X> const& t)
    {
      return t;
    }
  }
}

#endif
