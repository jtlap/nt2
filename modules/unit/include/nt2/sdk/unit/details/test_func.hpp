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
#include <nt2/sdk/unit/details/through_volatile.hpp>
#include <iostream>

namespace nt2
{
  namespace container
  {
    template<class Expr, class Result, class Dummy>
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

    template<class Expr, class Result, class Dummy>
    Result eval(nt2::container::expression<Expr, Result, Dummy> const& t)
    {
      return t;
    }
  }
}

/// INTERNAL ONLY
/// Helpers for building implementation fo some predicate based tests
#define NT2_MAKE_TEST_FUNC(NAME,OP,COP)                                   \
template<class T, class U>                                                \
inline void NAME( char const* x1, char const* x2                          \
                , int line, char const * fn                               \
                , T const & t_, U const & u_                              \
                )                                                         \
{                                                                         \
  nt2::unit::test_count()++;                                              \
  T t = through_volatile(t_);                                             \
  T u = through_volatile(u_);                                             \
  if( nt2::details::eval( t OP u ) )                                      \
  {                                                                       \
    std::cout << " * Test `"                                              \
              << x1 << " " << #OP << " " << x2                            \
              << "` **passed**."                                          \
              << " (" << line << ")"                                      \
              << std::endl;                                               \
  }                                                                       \
  else                                                                    \
  {                                                                       \
    std::cout << " * Test `"<< x1 << " "<< #OP << " " << x2               \
              << "` **failed** in function " << fn << " (" << line << ")" \
              << ":  '" << t << " "<< #COP << " " << u << "'"             \
              << std::endl;                                               \
    ++nt2::unit::error_count();                                           \
  }                                                                       \
}                                                                         \
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
                      , T const & t_, U const & u_
                      )
  {
    nt2::unit::test_count()++;
    T t = through_volatile(t_);
    U u = through_volatile(u_);
    if( nt2::details::eval( (t == u) || ((t != t) && (u != u)) ) )
    {
      std::cout << " * Test `" << x1 << " == " << x2
                << "` **passed**." << " (" << line << ")" << std::endl;
    }
    else
    {
      std::cout << " * Test `"<< x1 << " == " << x2
                << "` **failed** in function " << fn << " (" << line << ")"
                << ":  '" << t << " != " << u << "'"
                << std::endl;
      ++nt2::unit::error_count();
    }
  }
} }

#endif
