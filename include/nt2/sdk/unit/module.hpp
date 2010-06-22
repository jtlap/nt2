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

#include <cstdio>
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
#define NT2_UNIT_TEST_CASE(FUNC)                                              \
void FUNC();                                                                  \
nt2::details::test const                                                      \
FUNC ## test = { FUNC, #FUNC, nt2::details::main_suite.link(&FUNC ## test) }; \
void FUNC()                                                                   \
/**/

#endif
