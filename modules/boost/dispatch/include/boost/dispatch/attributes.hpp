/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_DISPATCH_ATTRIBUTES_HPP_INCLUDED
#define BOOST_DISPATCH_ATTRIBUTES_HPP_INCLUDED

/*!
 * @file
 * @brief Defines wrapper for noinline, deprecated and restrict attributes
 **/

#include <boost/config.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>

#if defined(NT2_DOXYGEN_ONLY)
/*!
 * @brief Mark a function as candidate for no inlining
 *
 * This macro expands to a compiler specific function atttibute hinting the
 * compiler to not inline it.
 *
 **/
#define BOOST_DISPATCH_NOINLINE

/*!
 * @brief Mark a function as deprecated
 *
 * This macro expands to a compiler specific function atttibute emitting a
 * warning indicating said function is deprecated.
 *
 **/
 #define BOOST_DISPATCH_DEPRECATED

/*!
 * @brief Mark a pointer or reference as restricted
 *
 * This macro expands to a compiler specific parameters attribute indicating
 * that said attribute is non-aliasing pointer or reference.
 *
 **/
#define BOOST_DISPATCH_RESTRICT

#else
#ifndef BOOST_FORCEINLINE
#  if defined(__GNUC__)
#    define BOOST_FORCEINLINE inline __attribute__((always_inline))
#  elif defined(_MSC_VER)
#     define BOOST_FORCEINLINE __forceinline
#  else
#    define BOOST_FORCEINLINE inline
#  endif
#endif

// deprecated name
#define BOOST_DISPATCH_FORCE_INLINE BOOST_FORCEINLINE

#if defined(__GNUC__)
#define BOOST_DISPATCH_NOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)
#define BOOST_DISPATCH_NOINLINE __declspec(noinline)
#else
#define BOOST_DISPATCH_NOINLINE
#endif

#if defined(__GNUC__)
#define BOOST_DISPATCH_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#define BOOST_DISPATCH_DEPRECATED __declspec(deprecated)
#else
#define BOOST_DISPATCH_DEPRECATED
#endif

#if defined(__GNUC__)
#define BOOST_DISPATCH_RESTRICT __restrict__
#elif defined(_MSC_VER)
#define BOOST_DISPATCH_RESTRICT __restrict
#else
#define BOOST_DISPATCH_RESTRICT
#endif
#if BOOST_PP_IS_EMPTY(BOOST_DISPATCH_RESTRICT)
#define BOOST_DISPATCH_NO_RESTRICT
#endif

#if defined(BOOST_DISPATCH_NO_RESTRICT) || defined(_MSC_VER)
#define BOOST_DISPATCH_NO_RESTRICT_REFERENCES
#endif

#endif

#endif
