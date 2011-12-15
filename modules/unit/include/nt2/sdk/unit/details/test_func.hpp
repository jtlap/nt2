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
#include <boost/dispatch/details/ignore_unused.hpp>
#include <boost/type_traits/common_type.hpp>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// Helpers for building implementation fo some predicate based tests
////////////////////////////////////////////////////////////////////////////////
#define NT2_MAKE_TEST_FUNC(NAME,OP,COP)                                     \
  template<class T, class U>                                                \
  inline void NAME( char const* x1, char const* x2                          \
                  , int line, char const * fn                               \
                  , T const & t, U const & u                                \
                  )                                                         \
  {                                                                         \
    test_count()++;                                                         \
    typedef typename boost::common_type<T, U>::type R;                      \
    if( R(t) OP R(u) )                                                      \
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
                  , T const & t, U const & u                                \
                  )                                                         \
  {                                                                         \
    test_count()++;                                                         \
    typedef typename boost::common_type<T, U>::type R;                      \
    if( (R(t) OP R(u)) || ((R(t) != R(t)) && (R(u) != R(u))) )              \
      {                                                                     \
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
  NT2_MAKE_TEST_NAN_FUNC(test_eq  , ==, !=  )
  NT2_MAKE_TEST_FUNC(test_neq , !=, ==  )
  NT2_MAKE_TEST_FUNC(test_lt  , < , >=  )
  NT2_MAKE_TEST_FUNC(test_gt  , > , <=  )
  NT2_MAKE_TEST_FUNC(test_le  , <= , >  )
  NT2_MAKE_TEST_FUNC(test_ge  , >= , <  )
} }

#endif
