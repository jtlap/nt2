/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_ERRORS_ASSERT_HPP_INCLUDED
#define NT2_SDK_ERRORS_ASSERT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Define macro for asserting preconditions
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/errors/trap.hpp>
#include <nt2/sdk/errors/debug.hpp>

#if !defined(NT2_DISABLE_ASSERTS)
#if defined(NT2_DEBUG) && !defined(NT2_RELEASE)
////////////////////////////////////////////////////////////////////////////////
// If in DEBUG mode, fire an assertion then a Debug Trap
////////////////////////////////////////////////////////////////////////////////
#define BOOST_ENABLE_ASSERT_HANDLER
#include <boost/assert.hpp>
namespace boost
{
  void assertion_failed(char const*,char const*,char const*,long)
  {
    ::nt2::sys::trap();
  }
}
#define NT2_ASSERT(XPR) BOOST_ASSERT(XPR)
#define NT2_VERIFY(XPR) BOOST_VERIFY(XPR)
#undef BOOST_ENABLE_ASSERT_HANDLER
#else
////////////////////////////////////////////////////////////////////////////////
// If not in DEBUG mode, we just fire an assertion
////////////////////////////////////////////////////////////////////////////////
#include <boost/assert.hpp>
#define NT2_ASSERT(XPR) BOOST_ASSERT(XPR)
#define NT2_VERIFY(XPR) BOOST_VERIFYXPR)
#endif
#else
////////////////////////////////////////////////////////////////////////////////
// If assertions are disabled, we disable the macros
////////////////////////////////////////////////////////////////////////////////
#define NT2_ASSERT(XPR)
#define NT2_VERIFY(XPR)
#endif

#endif
