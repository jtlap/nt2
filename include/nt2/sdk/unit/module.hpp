/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_UNIT_MODULE_HPP_INCLUDED
#define NT2_SDK_UNIT_MODULE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Unit test framework
// Documentation: http://nt2.lri.fr/sdk/unit/module.html
////////////////////////////////////////////////////////////////////////////////
#include <cstdio>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <nt2/sdk/unit/details/suite.hpp>
#include <nt2/sdk/unit/details/stats.hpp>

////////////////////////////////////////////////////////////////////////////////
// Embedded main for testing purpose
////////////////////////////////////////////////////////////////////////////////
int main(int,char const**)
{
  nt2::details::main_suite.process();
  return nt2::details::error_count() ? -1: 0;
}

////////////////////////////////////////////////////////////////////////////////
// Macro for starting a test module
////////////////////////////////////////////////////////////////////////////////
#define NT2_TEST_CASE(FUNC)                                                   \
void BOOST_PP_CAT(test,FUNC)();                                               \
nt2::details::test const                                                      \
BOOST_PP_CAT(FUNC,test) = { BOOST_PP_CAT(test,FUNC)                           \
                          , BOOST_PP_STRINGIZE(BOOST_PP_CAT(FUNC,_test))      \
                          , nt2::details                                      \
                               ::main_suite.link(&BOOST_PP_CAT(FUNC,test)) }; \
void BOOST_PP_CAT(test,FUNC)()                                                \
/**/

#endif
