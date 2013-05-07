//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::meta::is_result_of_supported"

#include <nt2/sdk/meta/is_result_of_supported.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test is_result_of_supported with nothing
////////////////////////////////////////////////////////////////////////////////
struct moo {};

NT2_TEST_CASE(is_result_of_supported_fail)
{
  using nt2::meta::is_result_of_supported;

  NT2_TEST( !is_result_of_supported<float(int)>::value);
  NT2_TEST( !is_result_of_supported<moo(int)>::value);
}

////////////////////////////////////////////////////////////////////////////////
// Test is_result_of_supported with result_type
////////////////////////////////////////////////////////////////////////////////
struct foo { typedef float result_type; };

NT2_TEST_CASE(is_result_of_supported_via_result_type)
{
  using nt2::meta::is_result_of_supported;

  NT2_TEST( is_result_of_supported<foo(int)>::value);
  NT2_TEST( is_result_of_supported<foo(int,int)>::value);
  NT2_TEST( is_result_of_supported<foo(int,int,int)>::value);
  NT2_TEST( is_result_of_supported<foo(int,int,int,int)>::value);
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

NT2_TEST_CASE(is_result_of_supported_via_result)
{
  using nt2::meta::is_result_of_supported;

  NT2_TEST( is_result_of_supported<bar(int)>::value);
  NT2_TEST( is_result_of_supported<bar(int,int)>::value);
  NT2_TEST( is_result_of_supported<bar(int,int,int)>::value);
  NT2_TEST( is_result_of_supported<bar(int,int,int,int)>::value);
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

NT2_TEST_CASE(is_result_of_supported_via_result_missing)
{
  using nt2::meta::is_result_of_supported;

  NT2_TEST( !is_result_of_supported<chu(int)>::value);
  NT2_TEST( is_result_of_supported<chu(int,int)>::value);
  NT2_TEST( is_result_of_supported<chu(int,int,int)>::value);
  NT2_TEST( !is_result_of_supported<chu(int,int,int,int)>::value);
}
