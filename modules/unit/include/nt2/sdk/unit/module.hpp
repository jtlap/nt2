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

/**
* @file
* @brief Define macro for building a Unit Test
**/

#include <nt2/sdk/meta/type_id.hpp>
#include <nt2/sdk/meta/display_type.hpp>
#include <boost/preprocessor/cat.hpp>
#include <nt2/sdk/unit/details/suite.hpp>
#include <nt2/sdk/unit/details/stats.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/dispatch/preprocessor/strip.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/throw_exception.hpp>
#include <nt2/sdk/error/exception.hpp>
#include <nt2/sdk/error/assert_as_exceptions.hpp>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifndef NT2_UNIT_MAIN
#define NT2_UNIT_MAIN main
#define NT2_UNIT_MAIN_SPEC
#else
#define NT2_UNIT_MAIN_SPEC extern "C"
#endif

#define NT2_UNIT_PREFIX BOOST_PP_CAT(BOOST_PP_CAT(test_, NT2_UNIT_MAIN), _)

/// INTERNAL ONLY
/// Embedded main for testing purpose
#ifndef BOOST_NO_EXCEPTIONS
NT2_UNIT_MAIN_SPEC int NT2_UNIT_MAIN(int argc, char* argv[])
{
  if(argc > 1 && !strcmp(argv[1], "--no-catch"))
  {
    nt2::details::main_suite.process();
    return nt2::details::error_count() ? -1: 0;
  }

  try
  {
    nt2::details::main_suite.process();
    return nt2::details::error_count() ? -1: 0;
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
  return nt2::details::error_count() ? -1: 0;
}

namespace boost
{
  /// INTERNAL ONLY
  /// Add an uncaught exception handler
  extern inline BOOST_ATTRIBUTE_NORETURN
  void throw_exception(std::exception const& e)
  {
    std::cout << "uncaught exception: " << e.what() << std::endl;
    std::abort();
  }
}
#endif

/**
* This macro declares a new test case function containing user-defined tests
* sequences.
*
* \param Name Name of the Test Case to generate
**/
#define NT2_TEST_CASE(Name)                                                              \
void BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)();                                               \
nt2::details::test const                                                                 \
BOOST_PP_CAT(Name,NT2_UNIT_PREFIX) = { BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)                \
                                     , BOOST_PP_STRINGIZE(BOOST_PP_CAT(Name,_test))      \
                                     , nt2::details                                      \
                               ::main_suite.link(&BOOST_PP_CAT(Name,NT2_UNIT_PREFIX)) }; \
void BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)()                                                \
/**/

/// INTERNAL ONLY
/// Helper for template test cases generation
#define NT2_PP_TPL_CASES(r,name,type)                                                    \
printf("With T = [%s]\n",nt2::type_id<BOOST_DISPATCH_PP_STRIP(type)>().c_str());         \
BOOST_PP_CAT(tpl_, BOOST_PP_CAT(NT2_UNIT_PREFIX,name))<BOOST_DISPATCH_PP_STRIP(type)>(); \
/**/

/**
* This macro declares a new set of test case functions containing user-defined
* test sequences working on a list of type passed as template parameters to the
* test function.
*
* \param Name Name of the Test Case to generate
* \param Types a Preprocessor sequences of type to be used for generating the
* Test Cases.
**/
#define NT2_TEST_CASE_TPL(Name, Types)                                                   \
template<class T> void BOOST_PP_CAT(tpl_, BOOST_PP_CAT(NT2_UNIT_PREFIX,Name))();         \
void BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)();                                               \
nt2::details::test const                                                                 \
BOOST_PP_CAT(Name,NT2_UNIT_PREFIX) = { BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)                \
                                     , BOOST_PP_STRINGIZE(BOOST_PP_CAT(Name,_test))      \
                                     , nt2::details                                      \
                               ::main_suite.link(&BOOST_PP_CAT(Name,NT2_UNIT_PREFIX)) }; \
void BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)()                                                \
{                                                                                        \
  BOOST_PP_SEQ_FOR_EACH(NT2_PP_TPL_CASES,Name,Types);                                    \
}                                                                                        \
template<class T> void BOOST_PP_CAT(tpl_, BOOST_PP_CAT(NT2_UNIT_PREFIX,Name))()          \
/**/

/**
* This macro declares a new set of test case functions containing user-defined
* test sequences working on a list of type passed as template parameters to the
* test function, and only enables those tests if a compile-time condition is veried
*
* @param Name   Name of the Test Case to generate
* @param Types  a Preprocessor sequences of type to be used for generating the
*               Test Cases.
* @param Cond   Meta-function enabling the test if @c Cond<T>::value evaluates
*               to @c true.
**/
#define NT2_TEST_CASE_TPL_IF(Name, Types, Cond)                                          \
template<class T>                                                                        \
typename boost::enable_if<BOOST_DISPATCH_PP_STRIP(Cond)>::type                           \
BOOST_PP_CAT(tpl_, BOOST_PP_CAT(NT2_UNIT_PREFIX,Name))();                                \
                                                                                         \
template<class T>                                                                        \
typename boost::disable_if<BOOST_DISPATCH_PP_STRIP(Cond)>::type                          \
BOOST_PP_CAT(tpl_, BOOST_PP_CAT(NT2_UNIT_PREFIX,Name))() {}                              \
                                                                                         \
void BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)();                                               \
nt2::details::test const                                                                 \
BOOST_PP_CAT(Name,NT2_UNIT_PREFIX) = { BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)                \
                                     , BOOST_PP_STRINGIZE(BOOST_PP_CAT(Name,_test))      \
                                     , nt2::details                                      \
                               ::main_suite.link(&BOOST_PP_CAT(Name,NT2_UNIT_PREFIX)) }; \
void BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)()                                                \
{                                                                                        \
  BOOST_PP_SEQ_FOR_EACH(NT2_PP_TPL_CASES,Name,Types);                                    \
}                                                                                        \
                                                                                         \
template<class T>                                                                        \
typename boost::enable_if<BOOST_DISPATCH_PP_STRIP(Cond)>::type                           \
BOOST_PP_CAT(tpl_, BOOST_PP_CAT(NT2_UNIT_PREFIX,Name))()                                 \
/**/

#endif
