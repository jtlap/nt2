//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_DETAILS_TYPEOF_HPP_INCLUDED
#define BOOST_DISPATCH_DETAILS_TYPEOF_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/preprocessor/cat.hpp>

/// INTERNAL ONLY
/// Boost.Config isn't up to date for MSVC10 so we force it to be
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1600) && defined(BOOST_NO_DECLTYPE)
#undef BOOST_NO_DECLTYPE
#endif

/// INTERNAL ONLY
/// decltype in GCC 4.4 is FUBAR
#if defined(__GNUC__) && __GNUC__ == 4 && __GNUC_MINOR__ == 4 && !defined(BOOST_NO_DECLTYPE)
#define BOOST_NO_DECLTYPE
#endif

#include <boost/typeof/typeof.hpp>

#if defined(BOOST_NO_DECLTYPE) && !defined(BOOST_TYPEOF_NATIVE)
#error compiler supports neither decltype nor typeof
#endif

/// INTERNAL ONLY
#ifndef BOOST_NO_DECLTYPE
#  define BOOST_DISPATCH_TYPEOF_(EXPR, TYPE) typedef decltype(EXPR) TYPE;
#  define BOOST_DISPATCH_TYPEOF(EXPR) decltype(EXPR)
#else
#  define BOOST_DISPATCH_TYPEOF_(EXPR, TYPE)                                                       \
    BOOST_TYPEOF_NESTED_TYPEDEF_TPL(BOOST_PP_CAT(nested_, TYPE), (EXPR))                           \
    typedef typename BOOST_PP_CAT(nested_, TYPE)::type TYPE;                                       \
   /**/
#  define BOOST_DISPATCH_TYPEOF(EXPR) BOOST_TYPEOF_TPL(EXPR)
#endif

#endif
