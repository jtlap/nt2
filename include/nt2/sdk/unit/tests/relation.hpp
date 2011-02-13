/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_UNIT_TESTS_RELATION_HPP_INCLUDED
#define NT2_SDK_UNIT_TESTS_RELATION_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Comparison tests
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/unit/details/suite.hpp>
#include <nt2/sdk/unit/details/test_func.hpp>

////////////////////////////////////////////////////////////////////////////////
// Predicate based tests
////////////////////////////////////////////////////////////////////////////////
#define NT2_TEST_EQUAL(A,B)           \
  /*r1 =  A;  r2 =  B;*/            \
  ( ::nt2::details::test_eq(#A, #B , __LINE__, BOOST_CURRENT_FUNCTION, A, B) ) \
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
