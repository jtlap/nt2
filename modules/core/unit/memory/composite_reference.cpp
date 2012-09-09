//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory composite container"

#include <nt2/sdk/memory/composite_reference.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

struct foo
{
  double d; float f; short c;
};

BOOST_FUSION_ADAPT_STRUCT(foo,(double,d)(float,f)(short,c))

//==============================================================================
// Test for container const reference
//==============================================================================
NT2_TEST_CASE( composite_const_reference )
{
  foo f = {3.12,4.f,456};
  nt2::memory::composite_reference<foo const> cref_f(f);

  NT2_TEST_EQUAL( boost::fusion::at_c<0>(cref_f), f.d);
  NT2_TEST_EQUAL( boost::fusion::at_c<1>(cref_f), f.f);
  NT2_TEST_EQUAL( boost::fusion::at_c<2>(cref_f), f.c);
}

//==============================================================================
// Test for container reference
//==============================================================================
NT2_TEST_CASE( composite_reference )
{
  foo f = {3.12,4.f,456};
  nt2::memory::composite_reference<foo>ref_f(f);

  NT2_TEST_EQUAL( boost::fusion::at_c<0>(ref_f), f.d);
  NT2_TEST_EQUAL( boost::fusion::at_c<1>(ref_f), f.f);
  NT2_TEST_EQUAL( boost::fusion::at_c<2>(ref_f), f.c);

  boost::fusion::at_c<0>(ref_f) = 9.87;
  boost::fusion::at_c<1>(ref_f) = 1.234f;
  boost::fusion::at_c<2>(ref_f) = 7;

  NT2_TEST_EQUAL( 9.87, f.d);
  NT2_TEST_EQUAL( 1.234f, f.f);
  NT2_TEST_EQUAL( 7, f.c);
}
