//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_MODULE_HPP_INCLUDED
#define NT2_SDK_UNIT_MODULE_HPP_INCLUDED

/*!
 * \file
 * \brief Define macro for building a Unit Test source file
 */

/*!
 * \ingroup units
 * \defgroup umodules Unit Test Case Generation
 * Define macro for building a Unit Test source file
 */

#include <cstdio>
#include <boost/preprocessor/cat.hpp>
#include <nt2/sdk/unit/details/suite.hpp>
#include <nt2/sdk/unit/details/stats.hpp>
#include <boost/dispatch/details/preprocessor.hpp>
#include <nt2/sdk/details/type_id.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

#if defined(DOXYGEN_ONLY)
//==============================================================================
/*!
 * \ingroup umodules
 * This macro has to be declared to notify the system that current translation
 * unti is a \nt2 Unit Tests.
 */
//==============================================================================
#define NT2_UNIT_MODULE
#endif

//==============================================================================
// Embedded main for testing purpose
//==============================================================================
int main(int,char const**)
{
  nt2::details::main_suite.process();
  return nt2::details::error_count() ? -1: 0;
}

//==============================================================================
/*!
 * \ingroup umodules
 * This macro declares a new test case function containing user-defined tests
 * sequences.
 *
 * \param Name Name of the Test Case to generate
 */
//==============================================================================
#define NT2_TEST_CASE(Name)                                                   \
void BOOST_PP_CAT(test,Name)();                                               \
nt2::details::test const                                                      \
BOOST_PP_CAT(Name,test) = { BOOST_PP_CAT(test,Name)                           \
                          , BOOST_PP_STRINGIZE(BOOST_PP_CAT(Name,_test))      \
                          , nt2::details                                      \
                               ::main_suite.link(&BOOST_PP_CAT(Name,test)) }; \
void BOOST_PP_CAT(test,Name)()                                                \
/**/

//==============================================================================
// Helper for template tets cases generation
//==============================================================================
#define NT2_PP_TPL_CASES(r,name,type)                                 \
printf("With T = [%s]\n",nt2::type_id<BOOST_DISPATCH_PP_STRIP(type)>().c_str()); \
BOOST_PP_CAT(tpl_test,name)<BOOST_DISPATCH_PP_STRIP(type)>();                    \
/**/

//==============================================================================
/*!
 * \ingroup umodules
 * This macro declares a new set of test case functions containing user-defined
 * test sequences working on a list of type passed as template parameters to the
 * test function.
 *
 * \param Name Name of the Test Case to generate
 * \param Types a Preprocessor sequences of type to be used for generating the
 * Test Cases.
 */
//==============================================================================
#define NT2_TEST_CASE_TPL(Name, Types)                                        \
template<class T> void BOOST_PP_CAT(tpl_test,Name)();                         \
void BOOST_PP_CAT(test,Name)();                                               \
nt2::details::test const                                                      \
BOOST_PP_CAT(Name,test) = { BOOST_PP_CAT(test,Name)                           \
                          , BOOST_PP_STRINGIZE(BOOST_PP_CAT(Name,_test))      \
                          , nt2::details                                      \
                               ::main_suite.link(&BOOST_PP_CAT(Name,test)) }; \
void BOOST_PP_CAT(test,Name)()                                                \
{                                                                             \
  BOOST_PP_SEQ_FOR_EACH(NT2_PP_TPL_CASES,Name,Types);                         \
}                                                                             \
template<class T> void BOOST_PP_CAT(tpl_test,Name)()                          \
/**/

#endif
