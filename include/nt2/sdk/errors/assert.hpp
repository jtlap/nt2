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
#include <nt2/sdk/errors/error.hpp>
#include <nt2/sdk/errors/warning.hpp>

////////////////////////////////////////////////////////////////////////////////
// Prepare the cases where we need a special handler
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Make assertion into exceptions
////////////////////////////////////////////////////////////////////////////////
#if defined(NT2_ASSERTS_AS_EXCEPTIONS) && !defined(NT2_DISABLE_ERROR)

NT2_WARNING(Assertion Failures throw exceptions)

namespace nt2 { namespace details { NT2_ERROR_INFO(assert_info,char const*); } }

namespace nt2
{
  struct assert_exception : virtual nt2::exception
  {
    virtual void display(std::ostream& os) const throw()
    {
      os  << "Assertion: "
          << *boost::get_error_info<nt2::details::assert_info>(*this)
          << " failed.\n";
    }
  };
}

#define BOOST_ENABLE_ASSERT_HANDLER
#endif

////////////////////////////////////////////////////////////////////////////////
// Debug mode has SIGTRAP to the assertion
////////////////////////////////////////////////////////////////////////////////
#if defined(NT2_DEBUG) && !defined(NT2_ASSERTS_AS_EXCEPTIONS)

NT2_WARNING(Assertion Failures emit Debug Traps)

#define BOOST_ENABLE_ASSERT_HANDLER
#endif

////////////////////////////////////////////////////////////////////////////////
// Include assert and forward the macro
////////////////////////////////////////////////////////////////////////////////
#include <boost/assert.hpp>
#define NT2_ASSERT(XPR) BOOST_ASSERT(XPR)
#define NT2_VERIFY(XPR) BOOST_VERIFY(XPR)

////////////////////////////////////////////////////////////////////////////////
// Define the handler
////////////////////////////////////////////////////////////////////////////////
namespace boost
{
  void assertion_failed(char const* expr,char const*,char const*,long)
  {
    #if defined(NT2_ASSERTS_AS_EXCEPTIONS) && !defined(NT2_DISABLE_ERROR)
    NT2_THROW( (nt2::assert_exception() << nt2::details::assert_info(expr) ) );
    #elif defined(NT2_DEBUG)
    ::nt2::sys::trap();
    #endif
  }
}

#undef BOOST_ENABLE_ASSERT_HANDLER

#endif
