/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_ERRORS_STATIC_ASSERT_HPP_INCLUDED
#define NT2_SDK_ERRORS_STATIC_ASSERT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Static assertion macro definitions.
// Documentation: http://nt2.lri.fr/sdk/error/static_assert.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>

////////////////////////////////////////////////////////////////////////////////
// Mapping over MPL_ASSERT_MSG
////////////////////////////////////////////////////////////////////////////////
#define NT2_STATIC_ASSERT(EXPR,MSG,T) \
BOOST_MPL_ASSERT_MSG(EXPR,MSG,T)      \
/**/

////////////////////////////////////////////////////////////////////////////////
// Mapping over MPL_ASSERT_MSG and negating assertion
////////////////////////////////////////////////////////////////////////////////
#define NT2_STATIC_ASSERT_NOT(EXPR,MSG,T)                         \
BOOST_MPL_ASSERT_MSG( (boost::mpl::bool_<!(EXPR)>::value) ,MSG,T) \
/**/

#endif
