//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_MODULE_HPP_INCLUDED
#define NT2_SDK_UNIT_MODULE_HPP_INCLUDED

/*!
  @file
  @brief Main Unit Tests entry point file
**/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <nt2/sdk/unit/stats.hpp>
#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/type_id.hpp>
#include <nt2/sdk/error/exception.hpp>
#include <nt2/sdk/config/type_lists.hpp>
#include <nt2/sdk/unit/details/suite.hpp>
#include <nt2/sdk/error/assert_as_exceptions.hpp>
#include <boost/throw_exception.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/dispatch/preprocessor/strip.hpp>

/// INTERNAL ONLY
/// Number of test runs to perform in cover mode
/// TODO: Make this runtime
#define NT2_NB_RANDOM_TEST 128

/// Depending on the mode (normal or driver), the entry point of the test suite
/// is either a regular main() function  of some special symbol.
#ifndef NT2_UNIT_MAIN

/// INTERNAL ONLY
/// Define the name of the test entry point.
#define NT2_UNIT_MAIN main

/// INTERNAL ONLY
/// Define if the test case has to be exported as C or C++ symbol
/// depending on the test is compiled in normal or driver mode.
#define NT2_UNIT_MAIN_SPEC
#else
#define NT2_UNIT_MAIN_SPEC extern "C"
#endif

/// INTERNAL ONLY
/// Define a file specific prefix for test functions that works in both
/// normal and driver mode.
#define NT2_UNIT_PREFIX BOOST_PP_CAT(BOOST_PP_CAT(test_, NT2_UNIT_MAIN), _)

/// INTERNAL ONLY
/// Embedded main for testing purpose. This function is used as an entry point
/// for the current test. In normal mode, it's basically a main(). In driver
/// mode, it is a unique symbol callable from the driver main().
#ifndef BOOST_NO_EXCEPTIONS
NT2_UNIT_MAIN_SPEC int NT2_UNIT_MAIN(int argc, char* argv[])
{
  if(argc > 1 && !strcmp(argv[1], "--no-catch"))
  {
    nt2::details::main_suite.process();
    return nt2::unit::error_count() ? -1: 0;
  }

  try
  {
    nt2::details::main_suite.process();
    return nt2::unit::error_count() ? -1: 0;
  }
  catch(std::exception const& e)
  {
    std::cout << "uncaught exception: " << e.what() << std::endl;
    return 1;
  }
  catch(...)
  {
    std::cout << "uncaught exception" << std::endl;
    return 1;
  }
}
#else
NT2_UNIT_MAIN_SPEC int NT2_UNIT_MAIN(int, char**)
{
  nt2::details::main_suite.process();
  return nt2::unit::error_count() ? -1: 0;
}

namespace boost
{
  /// INTERNAL ONLY
  /// This is a custom Boost.Exception handler that catch exceptions that were
  /// not caught by any tests inside the test function. This is usually the sign
  /// of something wrong in the test.
  extern inline
  void throw_exception(std::exception const& e)
  {
    std::cout << "uncaught exception: " << e.what() << std::endl;
    std::abort();
  }
}
#endif

/*!
  @brief Test case registration macro.

  This macro declares a new test case function containing user-defined tests
  sequences. Each test case has a unique name passed as a parameter that
  identify the set of tests inside the whole test suite.

  @usage
  @include test_case.cpp
**/
#define NT2_TEST_CASE(Name)                                               \
void BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)();                                \
nt2::details::test_registration const                                     \
BOOST_PP_CAT(Name,NT2_UNIT_PREFIX)                                        \
                        = { BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)            \
                          , BOOST_PP_STRINGIZE(BOOST_PP_CAT(Name,_test))  \
                          , nt2::details                                  \
                            ::main_suite                                  \
                              .link(&BOOST_PP_CAT(Name,NT2_UNIT_PREFIX))  \
                          };                                              \
void BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)()                                 \
/**/

/// INTERNAL ONLY
/// Generate one given instanciation of a template test case
#define NT2_PP_TPL_CASES(r,name,type)                           \
printf( "With T = [%s]\n"                                       \
      , nt2::type_id<BOOST_DISPATCH_PP_STRIP(type)>().c_str()); \
BOOST_PP_CAT(tpl_, BOOST_PP_CAT(NT2_UNIT_PREFIX,name))          \
                  <BOOST_DISPATCH_PP_STRIP(type)>();            \
/**/

/*!
  @brief Type-dependant test case registration macro

  This macro declares a new set of test cases functions containing user
  defined tests sequences parametrized by a list of types. The test functions
  is then instantiated for each type in the preprocessor sequence. Each test
  case has a unique name passed as a parameter that identify the set of tests
  inside the whole test suite.

  @usage
  @include test_case_tpl.cpp
**/
#define NT2_TEST_CASE_TPL(Name, Types)                                    \
template<class T> void BOOST_PP_CAT ( tpl_                                \
                                    , BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)  \
                                    )();                                  \
void BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)();                                \
                                                                          \
nt2::details::test_registration const                                     \
BOOST_PP_CAT(Name,NT2_UNIT_PREFIX)                                        \
            = { BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)                        \
              , BOOST_PP_STRINGIZE(BOOST_PP_CAT(Name,_test))              \
              , nt2::details                                              \
                ::main_suite.link(&BOOST_PP_CAT(Name,NT2_UNIT_PREFIX))    \
              };                                                          \
void BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)()                                 \
{                                                                         \
  BOOST_PP_SEQ_FOR_EACH(NT2_PP_TPL_CASES,Name,Types);                     \
}                                                                         \
                                                                          \
template<class T> void BOOST_PP_CAT ( tpl_                                \
                                    , BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)  \
                                    )()                                   \
/**/

#endif
