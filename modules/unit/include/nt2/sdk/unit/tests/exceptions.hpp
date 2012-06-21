//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_TESTS_EXCEPTIONS_HPP_INCLUDED
#define NT2_SDK_UNIT_TESTS_EXCEPTIONS_HPP_INCLUDED

/*!
 * \file
 * \brief Unit Test macros for exception conformance checks
 */

#include <nt2/sdk/unit/details/stats.hpp>
#include <boost/dispatch/preprocessor/strip.hpp>
#include <boost/dispatch/details/ignore_unused.hpp>

//==============================================================================
/*!
 * \ingroup utests
 * Checks if an expression throws a given exception at evaluation and raise the
 * failure count if not.
 * \param X Expression to check
 * \param E Exception expected to be caught
 */
//==============================================================================
#define NT2_TEST_THROW(X,E)                                               \
  do {                                                                    \
    ::nt2::details::test_count()++;                                       \
    bool caught = false;                                                  \
    try             { BOOST_DISPATCH_PP_STRIP(X); }                       \
    catch( E& ex )  {                                                     \
      ::boost::dispatch::ignore_unused(ex);                               \
      ::nt2::details::pass(#X " throws " #E);                             \
      caught = true;                                                      \
    }                                                                     \
    catch(...)      {}                                                    \
    if(!caught) ::nt2::details::fail( #X " throws " #E                    \
                                    , __LINE__, BOOST_CURRENT_FUNCTION);  \
  } while(0)                                                              \
/**/

//==============================================================================
/*!
 * \ingroup utests
 * Checks if an expression is triggering any runtime assertion at evaluation and
 * raise the failure count if not.
 * \param X Expression to check
 */
//==============================================================================
#define NT2_TEST_ASSERT(X) NT2_TEST_THROW(X, nt2::assert_exception)

//==============================================================================
/*!
 * \ingroup utests
 * Checks if an expression evaluates without throwing any exception and raise
 * the failure count if not.
 * \param X Expression to check
 */
//==============================================================================
#define NT2_TEST_NO_THROW(X)                                    \
do {                                                            \
  bool nt2_test_no_throw = true;                                \
  ::nt2::details::test_count()++;                               \
  try { BOOST_DISPATCH_PP_STRIP(X); }                           \
  catch(...)                                                    \
  {                                                             \
    ::nt2::details::fail( #X " does not throw"                  \
                        , __LINE__, BOOST_CURRENT_FUNCTION);    \
    nt2_test_no_throw = false;                                  \
  }                                                             \
  if(nt2_test_no_throw)                                         \
    ::nt2::details::pass(#X " does not throw");                 \
} while(0)                                                      \
/**/

//==============================================================================
/*!
 * \ingroup utests
 * Checks if an expression evaluates without throwing a given exception and
 * raise the failure count if not.
 * \param X Expression to check
 * \param E Exception expected to not be caught
 */
//==============================================================================
#define NT2_TEST_NO_THROW_EXCEPTION(X,E)                        \
do {                                                            \
  bool nt2_test_no_throw = true;                                \
  ::nt2::details::test_count()++;                               \
  try { BOOST_DISPATCH_PP_STRIP(X); }                           \
  catch(E& e)                                                   \
  {                                                             \
    ::nt2::details::fail( #X " does not throw " #E              \
                        , __LINE__, BOOST_CURRENT_FUNCTION);    \
    nt2_test_no_throw = false;                                  \
  }                                                             \
  catch(...) {}                                                 \
  if(nt2_test_no_throw)                                         \
    ::nt2::details::pass(#X " does not throw " #E);             \
} while(0)                                                      \
/**/

//==============================================================================
/*!
 * \ingroup utests
 * Checks if an expression is triggering no runtime assertion at evaluation and
 * raise the failure count if not.
 * \param X Expression to check
 */
//==============================================================================
#define NT2_TEST_NO_ASSERT(X) NT2_TEST_NO_THROW_EXCEPTION(X,nt2::assert_exception)

#endif
