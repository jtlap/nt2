//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_TESTS_EXCEPTIONS_HPP_INCLUDED
#define NT2_SDK_UNIT_TESTS_EXCEPTIONS_HPP_INCLUDED

/*!
  @file
  @brief Exceptions and assertions related testing macros
**/

#include <nt2/sdk/unit/stats.hpp>
#include <boost/dispatch/preprocessor/strip.hpp>
#include <boost/dispatch/details/ignore_unused.hpp>

/*!
  @brief Check exception being thrown

  For any given expression @c X, consider the test successful if and only if
  @c X throws an exception of type to @c E.

  @usage
  @include test_throw.cpp
**/
#define NT2_TEST_THROW(X,E)                                             \
do {                                                                    \
  ::nt2::unit::test_count()++;                                          \
  bool caught = false;                                                  \
  try             { BOOST_DISPATCH_PP_STRIP(X); }                       \
  catch( E& ex )  {                                                     \
    ::boost::dispatch::ignore_unused(ex);                               \
    ::nt2::unit::pass(#X " throws " #E);                                \
    caught = true;                                                      \
  }                                                                     \
  catch(...)      {}                                                    \
  if(!caught) ::nt2::unit::fail( #X " throws " #E                       \
                                  , __LINE__, BOOST_CURRENT_FUNCTION);  \
} while(0)                                                              \
/**/

/*!
  @brief Check runtime assertion failing

  For any given expression @c X, consider the test successful if and only if
  @c X triggered a run-time assertion.

  @usage
  @include test_assert.cpp
**/
#define NT2_TEST_ASSERT(X)                                    \
do {                                                          \
  ::nt2::unit::test_count()++;                                \
  bool caught = false;                                        \
  try             { BOOST_DISPATCH_PP_STRIP(X); }             \
  catch( nt2::assert_exception& ex )  {                       \
    ::nt2::unit::pass(#X " asserts ");                        \
    std::cout << "with message:\n\t'" << ex.what() << "'\n";  \
    caught = true;                                            \
  }                                                           \
  catch(...)      {}                                          \
  if(!caught)                                                 \
  {                                                           \
    ::nt2::unit::fail( #X " asserts "                         \
                        , __LINE__, BOOST_CURRENT_FUNCTION);  \
  }                                                           \
} while(0)                                                    \
/**/

/*!
  @brief Check exception not being thrown

  For any given expression @c X, consider the test successful if and only if
  @c X does not throw any exception.

  @usage
  @include test_no_throw.cpp
**/
#define NT2_TEST_NO_THROW(X)                                        \
do {                                                                \
  bool nt2_test_no_throw = true;                                    \
  ::nt2::unit::test_count()++;                                      \
  try { BOOST_DISPATCH_PP_STRIP(X); }                               \
  catch(...)                                                        \
  {                                                                 \
    ::nt2::unit::fail( #X " should not throw"                       \
                        , __LINE__, BOOST_CURRENT_FUNCTION          \
                        );                                          \
    nt2_test_no_throw = false;                                      \
  }                                                                 \
  if(nt2_test_no_throw) ::nt2::unit::pass(#X " does not throw");    \
} while(0)                                                          \
/**/


/*!
  @brief Check runtime assrtion not failing

  For any given expression @c X, consider the test successful if and only if
  @c X does not trigger any runtime assertion.

  @usage
  @include test_no_assert.cpp
**/
#define NT2_TEST_NO_ASSERT(X)                                 \
do {                                                          \
  bool nt2_test_no_throw = true;                              \
  ::nt2::unit::test_count()++;                                \
  try { BOOST_DISPATCH_PP_STRIP(X); }                         \
  catch(nt2::assert_exception& ex)                            \
  {                                                           \
    ::nt2::unit::fail( #X " should not assert "               \
                        , __LINE__, BOOST_CURRENT_FUNCTION    \
                        );                                    \
    std::cout << "with message:\n\t'" << ex.what() << "'\n";  \
    nt2_test_no_throw = false;                                \
  }                                                           \
  catch(...) {}                                               \
  if(nt2_test_no_throw)                                       \
    ::nt2::unit::pass(#X " does not assert " );               \
} while(0)                                                    \
/**/

#endif
