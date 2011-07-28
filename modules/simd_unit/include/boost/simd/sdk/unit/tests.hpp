//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_UNIT_TESTS_HPP_INCLUDED
#define BOOST_SIMD_SDK_UNIT_TESTS_HPP_INCLUDED

/*!
 * \ingroup units
 * \defgroup utests Unit Test Checking
 * Define macro for building a Unit Test Case implementation
 */


#include <boost/dispatch/details/preprocessor.hpp>
#include <boost/simd/include/functions/random.hpp>
#include <boost/simd/sdk/unit/details/stats.hpp>
#include <boost/simd/sdk/unit/details/tests.hpp>

#include <boost/simd/sdk/unit/tests/basic.hpp>
#include <boost/simd/sdk/unit/tests/relation.hpp>
#include <boost/simd/sdk/unit/tests/exceptions.hpp>
#include <boost/simd/sdk/unit/nb_rand_tests.hpp>

#define BOOST_SIMD_TEST_ULP_EQUAL(A,B,N)          \
  {                  \
    typedef typename boost::dispatch::meta::scalar_of<r_t>::type sr_t;    \
    sr_t r1 = A;              \
    sr_t r2 = B;              \
    ulpd = boost::simd::ulpdist(r1, r2);		\
    bool b;                 \
    b = ::boost::simd::details::test_ulp_eq(#A, #B, #N, __LINE__,    \
              BOOST_CURRENT_FUNCTION,    \
              r1, r2, N);       \
      if (!b)                \
  {                \
    std::cout <<	std::setprecision(20) << "   because " << #A << " = " << r1    \
        << " and " << #B << " = " << r2 <<  std::endl;  \
    std::cout << "   and ulp distance is "      \
        << ulpd << std::endl;        \
  }                \
  }                  \
/**/
#define BOOST_SIMD_TEST_TUPLE_ULP_EQUAL(A,B,N)          \
  {                  \
    bool b;                 \
    b = ::boost::simd::details::test_ulp_eq(#A, #B, #N, __LINE__,    \
              BOOST_CURRENT_FUNCTION,    \
              A, B, N);       \
    ulpd = boost::simd::ulpdist(A, B);          \
      if (!b)                \
  {                \
    std::cout << "   because " << #A << " = " << A    \
        << " and " << #B << " = " << B <<  std::endl;  \
    std::cout << "   and ulp distance is "      \
        << ulpd << std::endl;      \
  }                \
  }                  \
/**/

////////////////////////////////////////////////////////////////////////////////
// Show details for comparisons tests
////////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_COMPARISONS_DETAILS(A, B)          \
    if (!b)                \
      {                  \
  std::cout << "   because " << #A << " = " << r1 << " and " << #B << " = " << r2 <<  std::endl; \
  std::cout << "   and ulp distance is " << boost::simd::ulpdist(A, B) << std::endl; \
      }                  \
/**/
#define BOOST_SIMD_SHOW_ARG1(ARG)        \
  std::cout << "   for a0 = " << ARG << std::endl;  \
/**/

#define BOOST_SIMD_CREATE_BUF(NAME, TYPE, SIZE, MIN, MAX)		\
  boost::simd::memory::buffer<TYPE,					\
		      boost::simd::memory::allocator<TYPE> >		\
  NAME(0, SIZE);						\
  {/*TYPE fac = double((MAX-MIN))/(SIZE+2);*/			\
    for(int k = 0; k < (int)SIZE; ++k){				\
    /*NAME[k] = MIN+(k+1)*fac;*/				\
    NAME[k] = boost::simd::random(MIN, MAX);				\
    }}								\
  /**/

#define BOOST_SIMD_CREATE_BUFFER(NAME, TYPE, SIZE, MIN, MAX)	\
  boost::simd::memory::buffer<TYPE,				\
		      boost::simd::memory::allocator<TYPE> >    \
		      tab_##NAME(0, SIZE);		\
  {/*TYPE fac = double((MAX-MIN))/(SIZE+2);*/   	\
    for(int k = 0; k < (int)SIZE; ++k){			\
      /*tab_##NAME[k] = MIN+(k+1)*fac;*/	      	\
      NAME[k] = boost::simd::random(MIN, MAX);	       		\
   }}							\
/**/

#define BOOST_SIMD_CREATE_SCALAR_BUFFER(NAME, TYPE, SIZE, MIN, MAX)  \
  boost::simd::memory::buffer<TYPE,          \
          boost::simd::memory::allocator<TYPE> >    \
  tab_##NAME(0, SIZE);            \
  for(int k = 0; k < (int)SIZE; ++k){        \
    tab_##NAME[k] = boost::simd::random(MIN, MAX);      \
  }                \
/**/

////////////////////////////////////////////////////////////////////////////////
// Verbose predicate based tests
////////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_TEST_EQUAL_V1(ARG, A,B)  \
  BOOST_SIMD_SHOW_ARG1(ARG)      \
  BOOST_SIMD_COMPARISONS_TEST_DETAILS(A, B)  \
  BOOST_SIMD_TEST_EQUAL(A,B)      \
/**/

#define BOOST_SIMD_TEST_NOT_EQUAL_V1(ARG,A,B)  \
  BOOST_SIMD_SHOW_ARG1(ARG)      \
  BOOST_SIMD_COMPARISONS_TEST_DETAILS(A, B)  \
  BOOST_SIMD_TEST_NOT_EQUAL(A,B)    \
/**/

#define BOOST_SIMD_TEST_LESSER_V1(ARG,A,B)  \
  BOOST_SIMD_SHOW_ARG1(ARG)      \
  BOOST_SIMD_COMPARISONS_TEST_DETAILS(A, B)  \
  BOOST_SIMD_TEST_LESSER(A,B)             \
/**/

#define BOOST_SIMD_TEST_GREATER_V1(ARG,A,B)  \
  BOOST_SIMD_SHOW_ARG1(ARG)      \
  BOOST_SIMD_COMPARISONS_TEST_DETAILS(A, B)  \
  BOOST_SIMD_TEST_GREATER(A,B)      \
/**/

#define BOOST_SIMD_TEST_LESSER_EQUAL_V1(ARG,A,B)\
  BOOST_SIMD_SHOW_ARG1(ARG)      \
  BOOST_SIMD_COMPARISONS_TEST_DETAILS(A, B)  \
  BOOST_SIMD_TEST_LESSER_EQUAL(A,B)    \
/**/

#define BOOST_SIMD_TEST_GREATER_EQUAL_V1(ARG,A,B)\
  BOOST_SIMD_SHOW_ARG1(ARG)      \
  BOOST_SIMD_COMPARISONS_TEST_DETAILS(A, B)  \
  BOOST_SIMD_TEST_GREATER_EQUAL(A,B)    \
/**/

#endif
