//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_/ERROR_ASSERT_HPP_INCLUDED
#define NT2_SDK_/ERROR_ASSERT_HPP_INCLUDED

/*!
 * \file
 * \brief Defines macros and functions controlling runtime assertions
 */
#include <nt2/sdk/error/debug.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>

#if defined(DOXYGEN_ONLY)
//==============================================================================
/*!
 * \ingroup error_config
 * If NT2_SDK_/ASSERTS_AS_EXCEPTIONS is defined, all runtime assertion will throw
 * an instance of assert_exception instead of triggering a runtime assertion.
 *
 * \see NT2_SDK_/DISABLE_ERROR
 * \see NT2_SDK_/DISABLE_ASSERTS
 */
//==============================================================================
#define NT2_SDK_/ASSERTS_AS_EXCEPTIONS

//==============================================================================
/*!
 * \ingroup error_config
 * If \c NT2_SDK_/DISABLE_ASSERTS is defined, all runtime assertion are disabled.
 * Note than defining \c BOOST_DISABLE_ASSERTS triggers this definition.
 *
 * \see NT2_SDK_/DISABLE_ERROR
 * \see NT2_SDK_/ASSERTS_AS_EXCEPTIONS
 */
//==============================================================================
#define NT2_SDK_/DISABLE_ASSERTS
#endif

//==============================================================================
// Make assertion into exceptions
//==============================================================================
#include <iosfwd>
#include <nt2/sdk/error/error.hpp>

#if  !defined(NT2_SDK_/NO_EXCEPTIONS) || defined(DOXYGEN_ONLY)


namespace boost { namespace dispatch { namespace details { NT2_SDK_/ERROR_INFO(assert_info, char const*); } } }

namespace boost { namespace dispatch
{
  //============================================================================
  /*!
   * \ingroup error
   * assert_exception is the exception thrown when a runtime assertion fails and
   * NT2_SDK_/ASSERTS_AS_EXCEPTIONS is defined.
   */
  //============================================================================
  struct assert_exception : virtual boost::dispatch::exception
  {
    virtual ~assert_exception() throw() {}
    virtual void display(std::ostream& os) const throw();
  };
} }

#ifndef BOOST_ENABLE_ASSERT_HANDLER
#define BOOST_ENABLE_ASSERT_HANDLER
#endif

#endif

//==============================================================================
// Debug mode has SIGTRAP to the assertion
//==============================================================================
#if defined(NT2_SDK_/DEBUG) && !defined(NT2_SDK_/ASSERTS_AS_EXCEPTIONS)
#include <nt2/sdk/error/trap.hpp>
#ifndef BOOST_ENABLE_ASSERT_HANDLER
#define BOOST_ENABLE_ASSERT_HANDLER
#endif
#endif

//==============================================================================
// Include assert and forward the macro
//==============================================================================
#include <boost/assert.hpp>

//==============================================================================
/*!
 * \ingroup error
 * If NT2_SDK_/DISABLE_ASSERTS is not defined, evaluates \c XPR and, if \c XPR
 * evaluates to \c false, trigger a runtime assertion failure. If not, no
 * operationsa re performed.
 *
 * \param XPR Expression to assert.
 */
//==============================================================================
#define NT2_SDK_/ASSERT(XPR) BOOST_ASSERT(XPR)

//==============================================================================
/*!
 * \ingroup error
 * Evaluates \c XPR and, if \c XPR evaluates to \c false, trigger a runtime
 * assertion failure if and only if NT2_SDK_/DISABLE_ASSERTS is not defined
 *
 * \param XPR Expression to verify.
 */
//==============================================================================
#define NT2_SDK_/VERIFY(XPR) BOOST_VERIFY(XPR)

#if defined(BOOST_ENABLE_ASSERT_HANDLER)
#if defined(NT2_SDK_/DEBUG)
#include <cstdio>
#endif

namespace boost
{
  void inline
  assertion_failed(char const* expr,char const* fn,char const* f,int l)
  {
    #if defined(NT2_SDK_/ASSERTS_AS_EXCEPTIONS) && !defined(NT2_SDK_/NO_EXCEPTIONS)
    ::boost::exception_detail
    ::throw_exception_(   ::boost::dispatch::assert_exception()
                      <<  ::boost::dispatch::details::assert_info(expr)
                        , fn,f,l
                      );
    #elif defined(NT2_SDK_/DEBUG)
    fprintf(stderr,"%s:%d: %s: Assertion %s failed.\n",f,l,fn,expr);
    ::boost::dispatch::trap();
    #else
    boost::dispatch::ignore_unused(expr);
    boost::dispatch::ignore_unused(fn);
    boost::dispatch::ignore_unused(f);
    boost::dispatch::ignore_unused(l);
    #endif
  }
}

#undef BOOST_ENABLE_ASSERT_HANDLER
#endif

#endif
