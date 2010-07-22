/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_UNIT_TESTS_HPP_INCLUDED
#define NT2_SDK_UNIT_TESTS_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Unit test predicates macros
// Documentation: http://nt2.lri.fr/sdk/unit/tests.html
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/unit/details/stats.hpp>
#include <nt2/sdk/unit/details/tests.hpp>

////////////////////////////////////////////////////////////////////////////////
// Evaluates an expression and checks if it evaluates to true or not
////////////////////////////////////////////////////////////////////////////////
#define NT2_TEST(X)                                                 \
( ::nt2::details::test_count()++                                    \
, (X) ? ::nt2::details::pass(#X)                                    \
      : ::nt2::details::fail(#X, __LINE__, BOOST_CURRENT_FUNCTION)  \
)                                                                   \
/**/

////////////////////////////////////////////////////////////////////////////////
// Emit a strong error message
////////////////////////////////////////////////////////////////////////////////
#define NT2_TEST_ERROR(X)                                   \
::nt2::details::error(X, __LINE__, BOOST_CURRENT_FUNCTION)  \
/**/

////////////////////////////////////////////////////////////////////////////////
// Predicate based tests
////////////////////////////////////////////////////////////////////////////////
#define NT2_TEST_EQUAL(A,B)                                                   \
( ::nt2::details::test_eq(#A, #B , __LINE__, BOOST_CURRENT_FUNCTION, A, B) )  \
/**/

#define NT2_TEST_NOT_EQUAL(A,B)                                               \
( ::nt2::details::test_neq(#A, #B , __LINE__, BOOST_CURRENT_FUNCTION, A, B) ) \
/**/

#define NT2_TEST_LESSER(A,B)                                                  \
( ::nt2::details::test_lt(#A, #B , __LINE__, BOOST_CURRENT_FUNCTION, A, B) )  \
/**/

#define NT2_TEST_GREATER(A,B)                                                 \
( ::nt2::details::test_gt(#A, #B , __LINE__, BOOST_CURRENT_FUNCTION, A, B) )  \
/**/

#define NT2_TEST_LESSER_EQUAL(A,B)                                           \
( ::nt2::details::test_le(#A, #B , __LINE__, BOOST_CURRENT_FUNCTION, A, B) ) \
/**/

#define NT2_TEST_GREATER_EQUAL(A,B)                                           \
( ::nt2::details::test_ge(#A, #B , __LINE__, BOOST_CURRENT_FUNCTION, A, B) )  \
/**/

#endif
