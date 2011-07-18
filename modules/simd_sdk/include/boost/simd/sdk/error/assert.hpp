//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_ERROR_ASSERT_HPP_INCLUDED
#define BOOST_SIMD_SDK_ERROR_ASSERT_HPP_INCLUDED

/*!
 * \file
 * \brief Defines macros and functions controlling runtime assertions
 */
#include <boost/simd/sdk/error/debug.hpp>
#include <boost/dispatch/details/ignore_unused.hpp>

#if defined(DOXYGEN_ONLY)
//==============================================================================
/*!
 * \ingroup error_config
 * If BOOST_SIMD_SDK_ASSERTS_AS_EXCEPTIONS is defined, all runtime assertion will throw
 * an instance of assert_exception instead of triggering a runtime assertion.
 *
 * \see BOOST_SIMD_SDK_DISABLE_ERROR
 * \see BOOST_SIMD_SDK_DISABLE_ASSERTS
 */
//==============================================================================
#define BOOST_SIMD_SDK_ASSERTS_AS_EXCEPTIONS

//==============================================================================
/*!
 * \ingroup error_config
 * If \c BOOST_SIMD_SDK_DISABLE_ASSERTS is defined, all runtime assertion are disabled.
 * Note than defining \c BOOST_DISABLE_ASSERTS triggers this definition.
 *
 * \see BOOST_SIMD_SDK_DISABLE_ERROR
 * \see BOOST_SIMD_SDK_ASSERTS_AS_EXCEPTIONS
 */
//==============================================================================
#define BOOST_SIMD_SDK_DISABLE_ASSERTS
#endif

//==============================================================================
// Make assertion into exceptions
//==============================================================================
#include <iosfwd>
#include <boost/simd/sdk/error/error.hpp>

#if  !defined(BOOST_SIMD_SDK_NO_EXCEPTIONS) || defined(DOXYGEN_ONLY)


namespace boost { namespace simd { namespace details { BOOST_SIMD_SDK_ERROR_INFO(assert_info, char const*); } } }

namespace boost { namespace simd
{
  //============================================================================
  /*!
   * \ingroup error
   * assert_exception is the exception thrown when a runtime assertion fails and
   * BOOST_SIMD_SDK_ASSERTS_AS_EXCEPTIONS is defined.
   */
  //============================================================================
  struct assert_exception : virtual boost::simd::exception
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
#if defined(BOOST_SIMD_SDK_DEBUG) && !defined(BOOST_SIMD_SDK_ASSERTS_AS_EXCEPTIONS)
#include <boost/simd/sdk/error/trap.hpp>
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
 * If BOOST_SIMD_SDK_DISABLE_ASSERTS is not defined, evaluates \c XPR and, if \c XPR
 * evaluates to \c false, trigger a runtime assertion failure. If not, no
 * operationsa re performed.
 *
 * \param XPR Expression to assert.
 */
//==============================================================================
#define BOOST_SIMD_SDK_ASSERT(XPR) BOOST_ASSERT(XPR)

//==============================================================================
/*!
 * \ingroup error
 * Evaluates \c XPR and, if \c XPR evaluates to \c false, trigger a runtime
 * assertion failure if and only if BOOST_SIMD_SDK_DISABLE_ASSERTS is not defined
 *
 * \param XPR Expression to verify.
 */
//==============================================================================
#define BOOST_SIMD_SDK_VERIFY(XPR) BOOST_VERIFY(XPR)

#if defined(BOOST_ENABLE_ASSERT_HANDLER)
#if defined(BOOST_SIMD_SDK_DEBUG)
#include <cstdio>
#endif

namespace boost
{
  void inline
  assertion_failed(char const* expr,char const* fn,char const* f,int l)
  {
    #if defined(BOOST_SIMD_SDK_ASSERTS_AS_EXCEPTIONS) && !defined(BOOST_SIMD_SDK_NO_EXCEPTIONS)
    ::boost::exception_detail
    ::throw_exception_(   ::boost::simd::assert_exception()
                      <<  ::boost::simd::details::assert_info(expr)
                        , fn,f,l
                      );
    #elif defined(BOOST_SIMD_SDK_DEBUG)
    fprintf(stderr,"%s:%d: %s: Assertion %s failed.\n",f,l,fn,expr);
    ::boost::simd::trap();
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
