/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define BOOST_SIMD_UNIT_MODULE "boost::simd::meta::is_result_of_supported"

#include <boost/simd/sdk/meta/is_result_of_supported.hpp>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test is_result_of_supported with nothing
////////////////////////////////////////////////////////////////////////////////
struct moo {};

BOOST_SIMD_TEST_CASE(is_result_of_supported_fail)
{
  using boost::simd::meta::is_result_of_supported;

  BOOST_SIMD_TEST( !is_result_of_supported<float(int)>::value);
  BOOST_SIMD_TEST( !is_result_of_supported<moo(int)>::value);
}

////////////////////////////////////////////////////////////////////////////////
// Test is_result_of_supported with result_type
////////////////////////////////////////////////////////////////////////////////
struct foo { typedef float result_type; };

BOOST_SIMD_TEST_CASE(is_result_of_supported_via_result_type)
{
  using boost::simd::meta::is_result_of_supported;

  BOOST_SIMD_TEST( is_result_of_supported<foo(int)>::value);
  BOOST_SIMD_TEST( is_result_of_supported<foo(int,int)>::value);
  BOOST_SIMD_TEST( is_result_of_supported<foo(int,int,int)>::value);
  BOOST_SIMD_TEST( is_result_of_supported<foo(int,int,int,int)>::value);
}

////////////////////////////////////////////////////////////////////////////////
// Test is_result_of_supported with result<>
////////////////////////////////////////////////////////////////////////////////
struct bar
{
  template<class Sig> struct result;
  template<class This,class A>
  struct result<This(A)>      { typedef A type; };
  template<class This,class A,class B>
  struct result<This(A,B)>    { typedef B type; };
  template<class This,class A,class B,class C>
  struct result<This(A,B,C)>    { typedef C type; };
  template<class This,class A,class B,class C,class D>
  struct result<This(A,B,C,D)>    { typedef D type; };
};

BOOST_SIMD_TEST_CASE(is_result_of_supported_via_result)
{
  using boost::simd::meta::is_result_of_supported;

  BOOST_SIMD_TEST( is_result_of_supported<bar(int)>::value);
  BOOST_SIMD_TEST( is_result_of_supported<bar(int,int)>::value);
  BOOST_SIMD_TEST( is_result_of_supported<bar(int,int,int)>::value);
  BOOST_SIMD_TEST( is_result_of_supported<bar(int,int,int,int)>::value);
}

////////////////////////////////////////////////////////////////////////////////
// Test is_result_of_supported with result<> with some missing cases
////////////////////////////////////////////////////////////////////////////////
struct chu
{
  template<class Sig> struct result;
  template<class This,class A,class B>
  struct result<This(A,B)>    { typedef B type; };
  template<class This,class A,class B,class C>
  struct result<This(A,B,C)>  { typedef C type; };
};

BOOST_SIMD_TEST_CASE(is_result_of_supported_via_result_missing)
{
  using boost::simd::meta::is_result_of_supported;

  BOOST_SIMD_TEST( !is_result_of_supported<chu(int)>::value);
  BOOST_SIMD_TEST( is_result_of_supported<chu(int,int)>::value);
  BOOST_SIMD_TEST( is_result_of_supported<chu(int,int,int)>::value);
  BOOST_SIMD_TEST( !is_result_of_supported<chu(int,int,int,int)>::value);
}
