//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_TESTS_RELATION_HPP_INCLUDED
#define NT2_SDK_UNIT_TESTS_RELATION_HPP_INCLUDED

/*!
 * \file
 * \brief Macros for checking relation between values in Unit Tests
 */

#include <nt2/sdk/unit/details/suite.hpp>
#include <nt2/sdk/unit/details/test_func.hpp>
#include <nt2/include/functions/compare_equal.hpp>
#include <nt2/include/functions/compare_not_equal.hpp>
#include <nt2/include/functions/compare_less.hpp>
#include <nt2/include/functions/compare_less_equal.hpp>
#include <nt2/include/functions/compare_greater.hpp>
#include <nt2/include/functions/compare_greater_equal.hpp>

//==============================================================================
/*!
 * \ingroup utests
 * Test if two expression evaluates to the same value and raise the failure
 * count if not.
 */
//==============================================================================
#define NT2_TEST_EQUAL(A,B)                                                   \
( ::nt2::details::test_eq(#A, #B , __LINE__, BOOST_CURRENT_FUNCTION, A, B) )  \
/**/

//==============================================================================
/*!
 * \ingroup utests
 * Test if two expression evaluates to different values and raise the failure
 * count if not.
 */
//==============================================================================
#define NT2_TEST_NOT_EQUAL(A,B)                                               \
( ::nt2::details::test_neq(#A, #B , __LINE__, BOOST_CURRENT_FUNCTION, A, B) ) \
/**/

//==============================================================================
/*!
 * \ingroup utests
 * Test if an expression evaluates to a smaller value than the second one and
 * raise the failure count if not.
 */
//==============================================================================
#define NT2_TEST_LESSER(A,B)                                                  \
( ::nt2::details::test_lt(#A, #B , __LINE__, BOOST_CURRENT_FUNCTION, A, B) )  \
/**/

//==============================================================================
/*!
 * \ingroup utests
 * Test if an expression evaluates to a greater value than the second one and
 * raise the failure count if not.
 */
//==============================================================================
#define NT2_TEST_GREATER(A,B)                                                 \
( ::nt2::details::test_gt(#A, #B , __LINE__, BOOST_CURRENT_FUNCTION, A, B) )  \
/**/

//==============================================================================
/*!
 * \ingroup utests
 * Test if an expression evaluates to a smaller or equal value than the second
 * one and raise the failure count if not.
 */
//==============================================================================
#define NT2_TEST_LESSER_EQUAL(A,B)                                           \
( ::nt2::details::test_le(#A, #B , __LINE__, BOOST_CURRENT_FUNCTION, A, B) ) \
/**/

//==============================================================================
/*!
 * \ingroup utests
 * Test if an expression evaluates to a greater or equal value than the second
 * one and raise the failure count if not.
 */
//==============================================================================
#define NT2_TEST_GREATER_EQUAL(A,B)                                           \
( ::nt2::details::test_ge(#A, #B , __LINE__, BOOST_CURRENT_FUNCTION, A, B) )  \
/**/

#endif
