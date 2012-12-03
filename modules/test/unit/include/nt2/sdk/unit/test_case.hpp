//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_TEST_CASE_HPP_INCLUDED
#define NT2_SDK_UNIT_TEST_CASE_HPP_INCLUDED

/*!
  @file
  @brief Test case macro definition
**/

#include <cstdio>
#include <nt2/sdk/unit/stats.hpp>
#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/type_id.hpp>
#include <nt2/sdk/config/type_lists.hpp>
#include <nt2/sdk/error/assert_as_exceptions.hpp>

#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/dispatch/preprocessor/strip.hpp>

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
nt2::details::unit_test const                                             \
BOOST_PP_CAT(Name,NT2_UNIT_PREFIX)                                        \
                        ( &nt2::details::unit_tests                       \
                        , BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)              \
                        , BOOST_PP_STRINGIZE(BOOST_PP_CAT(Name,_test))    \
                        );                                                \
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
nt2::details::unit_test const                                             \
BOOST_PP_CAT(Name,NT2_UNIT_PREFIX)                                        \
            ( &nt2::details::unit_tests                                   \
            , BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)                          \
            , BOOST_PP_STRINGIZE(BOOST_PP_CAT(Name,_test))                \
            );                                                            \
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
