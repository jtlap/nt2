/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_UNIT_NO_ULP_TESTS_HPP_INCLUDED
#define NT2_SDK_UNIT_NO_ULP_TESTS_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Unit test predicates macros
// Documentation: http://nt2.lri.fr/sdk/unit/tests.html
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/details/preprocessor.hpp>
#include <nt2/include/functions/random.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/sdk/unit/details/stats.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/nb_rand_tests.hpp>
#include <nt2/sdk/meta/upgrade.hpp>

////////////////////////////////////////////////////////////////////////////////
// Show details for comparisons tests
////////////////////////////////////////////////////////////////////////////////
#define NT2_COMPARISONS_DETAILS(A, B)          \
    if (!b)                \
      {                  \
  std::cout << "   because " << #A << " = " << r1 << " and " << #B << " = " << r2 <<  std::endl; \
  std::cout << "   and ulp distance is " << nt2::ulpdist(A, B) << std::endl; \
      }                  \
/**/
#define NT2_SHOW_ARG1(ARG)        \
  std::cout << "   for a0 = " << ARG << std::endl;  \
/**/

#define NT2_CREATE_BUF(NAME, TYPE, SIZE, MIN, MAX)	\
  nt2::memory::buffer<TYPE,        \
          boost::simd::memory::allocator�<TYPE> >    \
  NAME(0, SIZE);            \
  for(int k = 0; k < SIZE; ++k){        \
    NAME[k] = nt2::random(MIN, MAX);      \
  }                \
/**/

#define NT2_CREATE_LOGICAL_BUF(NAME, TYPE, SIZE)	\
  nt2::memory::buffer<TYPE,        \
          boost::simd::memory::allocator�<TYPE> >    \
  NAME(0, SIZE);            \
  for(int k = 0; k < int(SIZE); ++k){					\
    NAME[k] = nt2::random(0, 1) ? nt2::True<TYPE>() : False<TYPE>();	\
  }                \
/**/
#define NT2_CREATE_BUFFER(NAME, TYPE, SIZE, MIN, MAX)	\
  nt2::memory::buffer<TYPE,        \
          boost::simd::memory::allocator�<TYPE> >    \
  tab_##NAME(0, SIZE);            \
  for(int k = 0; k < SIZE; ++k){        \
    tab_##NAME[k] = nt2::random(MIN, MAX);      \
  }                \
/**/
#define NT2_CREATE_SCALAR_BUFFER(NAME, TYPE, SIZE, MIN, MAX)  \
  nt2::memory::buffer<TYPE,          \
          boost::simd::memory::allocator<TYPE> >    \
  tab_##NAME(0, SIZE);            \
  for(int k = 0; k < SIZE; ++k){        \
    tab_##NAME[k] = nt2::random(MIN, MAX);      \
  }                \
/**/
#define NT2_CREATE_SIMD_BUFFER(NAME, TYPE, SIZE, MIN, MAX)  \
  nt2::memory::buffer<TYPE,          \
          boost::simd::memory::allocator<TYPE> >    \
  tab_##NAME(0, SIZE);            \
  for(int k = 0; k < SIZE; ++k){        \
    tab_##NAME[k] = nt2::random(MIN, MAX);      \
  }                \
/**/

////////////////////////////////////////////////////////////////////////////////
// Verbose predicate based tests
////////////////////////////////////////////////////////////////////////////////
#define NT2_TEST_EQUAL_V1(ARG, A,B)  \
  NT2_SHOW_ARG1(ARG)      \
  NT2_COMPARISONS_TEST_DETAILS(A, B)  \
  NT2_TEST_EQUAL(A,B)      \
/**/

#define NT2_TEST_NOT_EQUAL_V1(ARG,A,B)  \
  NT2_SHOW_ARG1(ARG)      \
  NT2_COMPARISONS_TEST_DETAILS(A, B)  \
  NT2_TEST_NOT_EQUAL(A,B)    \
/**/

#define NT2_TEST_LESSER_V1(ARG,A,B)  \
  NT2_SHOW_ARG1(ARG)      \
  NT2_COMPARISONS_TEST_DETAILS(A, B)  \
  NT2_TEST_LESSER(A,B)             \
/**/

#define NT2_TEST_GREATER_V1(ARG,A,B)  \
  NT2_SHOW_ARG1(ARG)      \
  NT2_COMPARISONS_TEST_DETAILS(A, B)  \
  NT2_TEST_GREATER(A,B)      \
/**/

#define NT2_TEST_LESSER_EQUAL_V1(ARG,A,B)\
  NT2_SHOW_ARG1(ARG)      \
  NT2_COMPARISONS_TEST_DETAILS(A, B)  \
  NT2_TEST_LESSER_EQUAL(A,B)    \
/**/

#define NT2_TEST_GREATER_EQUAL_V1(ARG,A,B)\
  NT2_SHOW_ARG1(ARG)      \
  NT2_COMPARISONS_TEST_DETAILS(A, B)  \
  NT2_TEST_GREATER_EQUAL(A,B)    \
/**/

#endif
