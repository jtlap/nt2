//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_DECLTYPE

/*!
 * \file
 * \brief Defines a platform agnostic \c decltype macro.
 */

/*!
 * \ingroup sdk
 * \defgroup meta Meta-Programming Utilities
 * This module gathers macros, macro functions and meta-functions used in
 * Boost.Dispatch to write various meta-programms.
 */

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

//==============================================================================
// Boost.Config isn't up to date for MSVC10 so we force it to be
//==============================================================================
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1600) && defined BOOST_NO_DECLTYPE
#undef BOOST_NO_DECLTYPE
#endif

#include <boost/typeof/typeof.hpp>

#if defined(BOOST_NO_DECLTYPE) && !defined(BOOST_TYPEOF_NATIVE)
#error compiler supports neither decltype nor typeof
#endif

/*!
 * \ingroup meta
 * Defines a type equivalent to the type of the epxression passed as arguments
 * \param EXPR Expression which type has to be evaluated
 * \param TYPE Typename to create
 *
 * \par Example Usage:
 *
 * \include decltype.cpp
 */
#ifndef BOOST_NO_DECLTYPE
#define BOOST_DISPATCH_DECLTYPE(EXPR, TYPE) typedef decltype(EXPR) TYPE;
#else
#define BOOST_DISPATCH_DECLTYPE(EXPR, TYPE)                            \
BOOST_TYPEOF_NESTED_TYPEDEF_TPL(BOOST_PP_CAT(nested_, TYPE), (EXPR))   \
typedef typename BOOST_PP_CAT(nested_, TYPE)::type TYPE;
#endif

#endif
