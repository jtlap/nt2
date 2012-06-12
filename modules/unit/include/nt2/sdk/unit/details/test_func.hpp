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

#include <nt2/sdk/unit/details/stats.hpp>
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

////////////////////////////////////////////////////////////////////////////////
// Helpers for building implementation fo some predicate based tests
////////////////////////////////////////////////////////////////////////////////
#define NT2_MAKE_TEST_FUNC(NAME,OP,COP)                                     \
  template<class T, class U>                                                \
  inline void NAME( char const* x1, char const* x2                          \
                  , int line, char const * fn                               \
                  , T const & t_, U const & u_                              \
                  )                                                         \
  {                                                                         \
    test_count()++;                                                         \
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
      ++error_count();                                                      \
    }                                                                       \
  }                                                                         \
/**/
////////////////////////////////////////////////////////////////////////////////
// Helpers for building implementation fo some predicate based tests
////////////////////////////////////////////////////////////////////////////////
#define NT2_MAKE_TEST_NAN_FUNC(NAME,OP,COP)                                 \
  template<class T, class U>                                                \
  inline void NAME( char const* x1, char const* x2                          \
                  , int line, char const * fn                               \
                  , T const & t_, U const & u_                              \
                  )                                                         \
  {                                                                         \
    test_count()++;                                                         \
    T t = through_volatile(t_);                                             \
    U u = through_volatile(u_);                                             \
    if( nt2::details::eval( (t OP u) || ((t != t) && (u != u)) ) )          \
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
      ++error_count();                                                      \
    }                                                                       \
  }                                                                         \
/**/
        
namespace nt2 { namespace details
{
  template<class T>
  T through_volatile(T const& t) { return const_cast<T const&>(const_cast<T const volatile&>(t)); }

  NT2_MAKE_TEST_NAN_FUNC(test_eq  , ==, !=  )
  NT2_MAKE_TEST_FUNC(test_neq , !=, ==  )
  NT2_MAKE_TEST_FUNC(test_lt  , < , >=  )
  NT2_MAKE_TEST_FUNC(test_gt  , > , <=  )
  NT2_MAKE_TEST_FUNC(test_le  , <= , >  )
  NT2_MAKE_TEST_FUNC(test_ge  , >= , <  )
} }

#endif
