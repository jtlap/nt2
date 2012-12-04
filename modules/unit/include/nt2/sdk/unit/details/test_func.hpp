/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_UNIT_DETAILS_TEST_FUNC_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_TEST_FUNC_HPP_INCLUDED

#include <nt2/sdk/unit/stats.hpp>
#include <nt2/include/functions/isequaln.hpp>
#include <nt2/include/functions/display.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>
#include <iostream>

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
    typename boost::dispatch::meta::terminal_of<Result>::type eval(nt2::container::expression<Expr, Result> const& t)
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

/// INTERNAL ONLY
/// Helpers for building implementation fo some predicate based tests
#define NT2_MAKE_TEST_FUNC(NAME,OP,COP)                                        \
template<class T, class U>                                                     \
inline void NAME( char const* x1, char const* x2                               \
                , int line, char const * fn                                    \
                , T const & t, U const & u                                     \
                )                                                              \
{                                                                              \
  nt2::unit::test_count()++;                                                   \
  if( nt2::details::eval( t OP u ) )                                           \
  {                                                                            \
    std::cout << " * Test `"                                                   \
              << x1 << " " << #OP << " " << x2                                 \
              << "` **passed**."                                               \
              << " (" << line << ")"                                           \
              << std::endl;                                                    \
  }                                                                            \
  else                                                                         \
  {                                                                            \
    std::cout << " * Test `"<< x1 << " "<< #OP << " " << x2                    \
              << "` **failed** in function " << fn << " (" << line << ")\n";   \
    nt2::display(x1, t);                                                       \
    nt2::display(x2, u);                                                       \
    std::cout << std::flush;                                                   \
    ++nt2::unit::error_count();                                                \
  }                                                                            \
}                                                                              \
/**/

namespace nt2 { namespace details
{
  /// INTERNAL ONLY
  /// Helpers for generating implementation of all predicate tests
  NT2_MAKE_TEST_FUNC(test_neq , !=, ==  )
  NT2_MAKE_TEST_FUNC(test_lt  , < , >=  )
  NT2_MAKE_TEST_FUNC(test_gt  , > , <=  )
  NT2_MAKE_TEST_FUNC(test_le  , <= , >  )
  NT2_MAKE_TEST_FUNC(test_ge  , >= , <  )

#undef NT2_MAKE_TEST_FUNC

  /// INTERNAL ONLY
  /// Helpers for building implementation of the equality predicate tests that
  /// nees to check for NaN for both its parameters
  template<class T, class U>
  inline void test_eq ( char const* x1, char const* x2, int line, char const* fn
                      , T const & t, U const & u
                      )
  {
    nt2::unit::test_count()++;
    if( nt2::isequaln(t, u) )
    {
      std::cout << " * Test `" << x1 << " == " << x2
                << "` **passed**." << " (" << line << ")" << std::endl;
    }
    else
    {
      std::cout << " * Test `"<< x1 << " == " << x2
                << "` **failed** in function " << fn << " (" << line << ")\n";
      nt2::display(x1, t);
      nt2::display(x2, u);
      std::cout << std::flush;
      ++nt2::unit::error_count();
    }
  }
} }

#endif
