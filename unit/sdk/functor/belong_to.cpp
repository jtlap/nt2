/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::functors::belong_to"

#include <nt2/sdk/functor/meta/belong_to.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/meta/set.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

struct foo {};
struct bar {};
struct chu {};
struct moo {};

////////////////////////////////////////////////////////////////////////////////
// Test that T belong to T but not to U
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(belong_to_type)
{
  using nt2::meta::belong_to;
  using boost::is_same;

  NT2_TEST(  (belong_to<foo, foo>::value) );
  NT2_TEST( !(belong_to<foo, bar>::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test that T belong_to a singletong set
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(belong_to_set1)
{
  using nt2::meta::set;
  using nt2::meta::belong_to;
  using boost::is_same;

  NT2_TEST(  (belong_to<foo, set<foo> >::value) );
  NT2_TEST( !(belong_to<foo, set<bar> >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test that T belong_to a set
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(belong_to_setn)
{
  using nt2::meta::set;
  using nt2::meta::belong_to;
  using boost::is_same;

  NT2_TEST(  (belong_to<foo, set<foo,bar,chu> >::value) );
  NT2_TEST(  (belong_to<foo, set<bar,foo,chu> >::value) );
  NT2_TEST(  (belong_to<foo, set<bar,chu,foo> >::value) );
  NT2_TEST( !(belong_to<foo, set<moo,bar,chu> >::value) );
  NT2_TEST( !(belong_to<foo, set<bar,moo,chu> >::value) );
  NT2_TEST( !(belong_to<foo, set<bar,chu,moo> >::value) );
}
