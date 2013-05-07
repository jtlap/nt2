//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_MODULE_HPP_INCLUDED
#define NT2_SDK_UNIT_MODULE_HPP_INCLUDED

/*!
  @file
  @brief Main Unit test module header
**/

#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/unit/test_case.hpp>
#include <nt2/sdk/unit/details/suite.hpp>
#include <nt2/sdk/unit/details/unit_test.hpp>
#include <nt2/sdk/unit/details/main.hpp>
#include <nt2/sdk/error/exception.hpp>
#include <nt2/sdk/error/assert_as_exceptions.hpp>
#include <boost/preprocessor/cat.hpp>

#if !defined(NT2_UNIT_MAIN_SUITE)
/// INTERNAL ONLY
#define NT2_UNIT_MAIN_SUITE nt2::details::unit_tests
#endif

/*!
  @brief Embedded main for testing purpose.

  This function is used as an entry point for the current test.
  In normal mode, it's basically a @c main(). In driver mode, it is a unique
  symbol callable from the driver @c main().
**/
NT2_UNIT_MAIN_SPEC int NT2_UNIT_MAIN(int argc, char* argv[])
{
  return nt2::details::unit_main(argc,argv,NT2_UNIT_MAIN_SUITE);
}

#endif
