//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_ERROR_STATIC_ASSERT_HPP_INCLUDED
#define NT2_SDK_ERROR_STATIC_ASSERT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Static assertion macro definitions.
// Documentation: http://nt2.lri.fr/sdk/error/static_assert.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/preprocessor/stringize.hpp>

#if defined(BOOST_HAS_STATIC_ASSERT)
////////////////////////////////////////////////////////////////////////////////
// C++0x maps over static_assert and display ID: REASON
////////////////////////////////////////////////////////////////////////////////
#define NT2_STATIC_ASSERT(COND,ID,REASON)                 \
static_assert(COND, BOOST_PP_STRINGIZE(ID) ": " REASON )  \
/**/
#define NT2_STATIC_ASSERT_NOT(COND,ID,REASON)                   \
static_assert( (!(COND)), BOOST_PP_STRINGIZE(ID) ": " REASON )  \
/**/
#else
////////////////////////////////////////////////////////////////////////////////
// C++03 maps over MPL_ASSERT_MSG and display the assert ID
////////////////////////////////////////////////////////////////////////////////
#define NT2_STATIC_ASSERT(COND,ID,REASON) \
BOOST_MPL_ASSERT_MSG((COND),ID,())        \
/**/
#define NT2_STATIC_ASSERT_NOT(COND,ID,REASON) \
BOOST_MPL_ASSERT_MSG( (!(COND)),ID,())        \
/**/
#endif

#endif
