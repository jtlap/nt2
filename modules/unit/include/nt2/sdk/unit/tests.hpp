//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_TESTS_HPP_INCLUDED
#define NT2_SDK_UNIT_TESTS_HPP_INCLUDED

/*!
 * \ingroup units
 * \defgroup utests Unit Test Checking
 * Define macro for building a Unit Test Case implementation
 */

#include <iomanip>
#include <vector>
#include <nt2/include/functions/random.hpp>
#include <nt2/include/constants/false.hpp>
#include <nt2/include/constants/true.hpp>
#include <nt2/include/constants/allbits.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/unit/details/stats.hpp>
#include <nt2/sdk/unit/details/tests.hpp>
#include <boost/simd/sdk/memory/allocator.hpp>

#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/nb_rand_tests.hpp>

#include <nt2/sdk/meta/primitive_of.hpp>

namespace nt2 { namespace details
{
  template< class T, class U
          , class pT = typename meta::primitive_of<T>::type
          , class pU = typename meta::primitive_of<U>::type
          >
  struct smallest_a_impl
  {
    typedef T type;
  };

  template<class T, class U>
  typename smallest_a_impl<T, U>::type
  smallest_a(T const& a, U const&)
  {
    return typename smallest_a_impl<T, U>::type(a);
  }

  template<class T, class U>
  struct smallest_a_impl<T, U, double, float>
  {
    typedef U type;
  };

  template< class T, class U
          , class pT = typename meta::primitive_of<T>::type
          , class pU = typename meta::primitive_of<U>::type
          >
  struct smallest_b_impl
  {
    typedef U type;
  };

  template<class T, class U>
  typename smallest_b_impl<T, U>::type
  smallest_b(T const&, U const& b)
  {
    return typename smallest_a_impl<T, U>::type(b);
  }

  template<class T, class U>
  struct smallest_b_impl<T, U, float, double>
  {
    typedef T type;
  };
} }

#define NT2_TEST_ULP_EQUAL(A, B, N)                                            \
{                                                                              \
  double ulpd = nt2::ulpdist( nt2::details::smallest_a(A, B)                   \
                            , nt2::details::smallest_b(A, B)                   \
                            );                                                 \
  bool b = nt2::details::                                                      \
           test_ulp_eq( #A, #B, #N, __LINE__                                   \
                      , BOOST_CURRENT_FUNCTION                                 \
                      , nt2::details::smallest_a(A, B)                         \
                      , nt2::details::smallest_b(A, B)                         \
                      , N                                                      \
                      );                                                       \
  if (!b)                                                                      \
  {                                                                            \
    std::cout << std::setprecision(20) << "   because " << #A << " = "         \
              << nt2::details::smallest_a(A, B)                                \
              << " and " << #B << " = "                                        \
              << nt2::details::smallest_b(A, B)                                \
              <<  std::endl;                                                   \
    std::cout << "   and ulp distance is " << ulpd << std::endl;               \
  }                                                                            \
}                                                                              \
/**/

#define NT2_TEST_TUPLE_ULP_EQUAL(A, B, N)                                      \
{                                                                              \
  bool b = ::nt2::details::test_ulp_eq(#A, #B, #N, __LINE__,                   \
            BOOST_CURRENT_FUNCTION,                                            \
            A, B, N);                                                          \
  double ulpd = nt2::ulpdist(A, B);                                            \
  if (!b)                                                                      \
  {                                                                            \
    std::cout << "   because " << #A << " = " << A                             \
        << " and " << #B << " = " << B <<  std::endl;                          \
    std::cout << "   and ulp distance is "                                     \
        << ulpd << std::endl;                                                  \
  }                                                                            \
}                                                                              \
/**/

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

#define NT2_CREATE_BUF(NAME, TYPE, SIZE, MIN, MAX)    \
  std::vector<TYPE,          \
          boost::simd::memory::allocator<TYPE> >    \
  NAME(SIZE);            \
  {\
    for(int k = 0; k < (int)SIZE; ++k){        \
    NAME[k] = nt2::random(MIN, MAX);        \
    }}                \
  /**/
#define NT2_CREATE_LOGICAL_BUF(NAME, TYPE, SIZE)\
  std::vector<TYPE,\
          boost::simd::memory::allocator<TYPE> >\
  NAME(SIZE);            \
  for(int k = 0; k < int(SIZE); ++k){          \
    NAME[k] = nt2::random(0, 1) ? nt2::True<TYPE>() : nt2::False<TYPE>(); \
  }                \
/**/
#define NT2_CREATE_BUFFER(NAME, TYPE, SIZE, MIN, MAX)  \
  std::vector<TYPE,        \
          boost::simd::memory::allocator<TYPE> >    \
          tab_##NAME(SIZE);    \
  {\
    for(int k = 0; k < (int)SIZE; ++k){      \
      NAME[k] = nt2::random(MIN, MAX);             \
   }}              \
/**/

#define NT2_CREATE_SCALAR_BUFFER(NAME, TYPE, SIZE, MIN, MAX)  \
  std::vector<TYPE,          \
          boost::simd::memory::allocator<TYPE> >    \
  tab_##NAME(SIZE);            \
  for(int k = 0; k < (int)SIZE; ++k){        \
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
