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
#include <nt2/sdk/details/type_id.hpp>
#include <nt2/sdk/unit/details/stats.hpp>
#include <nt2/sdk/unit/details/tests.hpp>
#include <nt2/sdk/details/preprocessor.hpp>
#include <nt2/include/functions/random.hpp>

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
#define NT2_TEST_EQUAL(A,B)						\
  /*r1 =  A;  r2 =  B;*/						\
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

#define NT2_TEST_ULP_EQUAL(A,B,N)					\
  {									\
    r_t r1 = A;								\
    r_t r2 = B;								\
    double ulp = nt2::ulpdist(r1, r2);						\
    bool b; 								\
    b = ::nt2::details::test_ulp_eq(#A, #B, #N, __LINE__,		\
				      BOOST_CURRENT_FUNCTION,		\
				      r1, r2, N); 			\
      if (!b)								\
	{								\
	  std::cout << "   because " << #A << " = " << r1		\
		    << " and " << #B << " = " << r2 <<  std::endl;	\
	  std::cout << "   and ulp distance is "			\
		    << ulp << std::endl;				\
	}								\
  }									\
/**/
#define NT2_TEST_TUPLE_ULP_EQUAL(A,B,N)					\
  {									\
    bool b; 								\
    b = ::nt2::details::test_ulp_eq(#A, #B, #N, __LINE__,		\
				      BOOST_CURRENT_FUNCTION,		\
				      A, B, N); 			\
      if (!b)								\
	{								\
	  std::cout << "   because " << #A << " = " << A		\
		    << " and " << #B << " = " << B <<  std::endl;	\
	  std::cout << "   and ulp distance is "			\
		    << nt2::ulpdist(A, B) << std::endl;			\
	}								\
  }									\
/**/

////////////////////////////////////////////////////////////////////////////////
// Show details for comparisons tests
////////////////////////////////////////////////////////////////////////////////
#define NT2_COMPARISONS_DETAILS(A, B)					\
    if (!b)								\
      {									\
	std::cout << "   because " << #A << " = " << r1 << " and " << #B << " = " << r2 <<  std::endl; \
	std::cout << "   and ulp distance is " << nt2::ulpdist(A, B) << std::endl; \
      }									\
/**/
#define NT2_SHOW_ARG1(ARG)				\
  std::cout << "   for a0 = " << ARG << std::endl;	\
/**/
#define NT2_CREATE_BUFFER(NAME, TYPE, SIZE, MIN, MAX)		\
  nt2::memory::buffer<TYPE,int,int,				\
		      nt2::memory::allocator<TYPE> >		\
  tab_##NAME(0, SIZE);						\
  TYPE NAME;							\
  for(int k = 0; k < SIZE; ++k){				\
    tab_##NAME[k] = nt2::random(MIN, MAX);			\
  }								\
/**/

////////////////////////////////////////////////////////////////////////////////
// Verbose predicate based tests
////////////////////////////////////////////////////////////////////////////////
#define NT2_TEST_EQUAL_V1(ARG, A,B)	\
  NT2_SHOW_ARG1(ARG)			\
  NT2_COMPARISONS_TEST_DETAILS(A, B)	\
  NT2_TEST_EQUAL(A,B)			\
/**/

#define NT2_TEST_NOT_EQUAL_V1(ARG,A,B)	\
  NT2_SHOW_ARG1(ARG)			\
  NT2_COMPARISONS_TEST_DETAILS(A, B)	\
  NT2_TEST_NOT_EQUAL(A,B)		\
/**/

#define NT2_TEST_LESSER_V1(ARG,A,B)	\
  NT2_SHOW_ARG1(ARG)			\
  NT2_COMPARISONS_TEST_DETAILS(A, B)	\
  NT2_TEST_LESSER(A,B) 		        \
/**/

#define NT2_TEST_GREATER_V1(ARG,A,B)	\
  NT2_SHOW_ARG1(ARG)			\
  NT2_COMPARISONS_TEST_DETAILS(A, B)	\
  NT2_TEST_GREATER(A,B)			\
/**/

#define NT2_TEST_LESSER_EQUAL_V1(ARG,A,B)\
  NT2_SHOW_ARG1(ARG)			\
  NT2_COMPARISONS_TEST_DETAILS(A, B)	\
  NT2_TEST_LESSER_EQUAL(A,B)		\
/**/

#define NT2_TEST_GREATER_EQUAL_V1(ARG,A,B)\
  NT2_SHOW_ARG1(ARG)			\
  NT2_COMPARISONS_TEST_DETAILS(A, B)	\
  NT2_TEST_GREATER_EQUAL(A,B)		\
/**/

////////////////////////////////////////////////////////////////////////////////
// Generate a test case using template type list
////////////////////////////////////////////////////////////////////////////////
#include <boost/preprocessor/seq/for_each.hpp>

#define NT2_PP_TPL_CASES(r,name,type)                                     \
printf("With type: %s\n\n",nt2::type_id<NT2_PP_STRIP(type)>().c_str());   \
BOOST_PP_CAT(tpl_test,name)<NT2_PP_STRIP(type)>();                        \
/**/

#define NT2_TEST_CASE_TPL(Name, Types)                                        \
template<class T> void BOOST_PP_CAT(tpl_test,Name)();                         \
void BOOST_PP_CAT(test,Name)();                                               \
nt2::details::test const                                                      \
BOOST_PP_CAT(Name,test) = { BOOST_PP_CAT(test,Name)                           \
                          , BOOST_PP_STRINGIZE(BOOST_PP_CAT(Name,_test))      \
                          , nt2::details                                      \
                               ::main_suite.link(&BOOST_PP_CAT(Name,test)) }; \
void BOOST_PP_CAT(test,Name)()                                                \
{                                                                             \
  BOOST_PP_SEQ_FOR_EACH(NT2_PP_TPL_CASES,Name,Types);                         \
}                                                                             \
template<class T> void BOOST_PP_CAT(tpl_test,Name)()                          \
/**/

#endif
