/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::dominant"

#include <nt2/sdk/meta/unknown.hpp>
#include <nt2/sdk/meta/category.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/dominant.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Define some arbitrary types and their respective category
////////////////////////////////////////////////////////////////////////////////
struct foo_tag {};
struct bar_tag {};
struct chu_tag {};
struct moo_tag {};

struct  foo_category
      : nt2::tag::category<foo_category,0,1> { typedef foo_tag tag; };

struct  bar_category
      : nt2::tag::category<bar_category,0,2> { typedef bar_tag tag; };

struct  chu_category
      : nt2::tag::category<chu_category,1,1> { typedef chu_tag tag; };

struct  moo_category
      : nt2::tag::category<moo_category,1,2> { typedef moo_tag tag; };

struct foo_ { typedef foo_category nt2_category_tag; };
struct bar_ { typedef bar_category nt2_category_tag; };
struct chu_ { typedef chu_category nt2_category_tag; };
struct moo_ { typedef moo_category nt2_category_tag; };

struct unk {};

////////////////////////////////////////////////////////////////////////////////
// Test dominant type of f(A0)
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(unary_dominant)
{
  using nt2::meta::dominant;
  using boost::is_same;

  NT2_TEST( (is_same<dominant<foo_>::type, foo_category >::value) );
  NT2_TEST( (is_same<dominant<bar_>::type, bar_category >::value) );
  NT2_TEST( (is_same<dominant<chu_>::type, chu_category >::value) );
  NT2_TEST( (is_same<dominant<moo_>::type, moo_category >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test dominant type of f(A0,A1)
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(binary_dominant)
{
  using boost::is_same;
  using nt2::tag::unknown;
  using nt2::meta::dominant;

  // Same type, trivial categorization
  NT2_TEST( (is_same<dominant<foo_,foo_>::type, foo_category >::value) );

  // unknown wins everytime
  NT2_TEST( (is_same<dominant<foo_,unk>::type, unknown >::value) );
  NT2_TEST( (is_same<dominant<unk,foo_>::type, unknown >::value) );

  // Same familly, bigger grain wins
  NT2_TEST( (is_same<dominant<foo_,bar_>::type, bar_category >::value) );
  NT2_TEST( (is_same<dominant<bar_,foo_>::type, bar_category >::value) );

  // Biggest familly wins whatever grain
  NT2_TEST( (is_same<dominant<foo_,chu_>::type, chu_category >::value) );
  NT2_TEST( (is_same<dominant<chu_,foo_>::type, chu_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,moo_>::type, moo_category >::value) );
  NT2_TEST( (is_same<dominant<moo_,foo_>::type, moo_category >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test dominant type of f(A0,A1,A2)
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(ternary_dominant)
{
  using boost::is_same;
  using nt2::tag::unknown;
  using nt2::meta::dominant;

  // Same type, trivial categorization
  NT2_TEST( (is_same<dominant<foo_,foo_,foo_>::type, foo_category >::value) );

  // unknown wins everytime (evenwith bigger boys)
  NT2_TEST( (is_same<dominant<unk,foo_,bar_>::type, unknown >::value) );
  NT2_TEST( (is_same<dominant<foo_,unk,chu_>::type, unknown >::value) );
  NT2_TEST( (is_same<dominant<moo_,foo_,unk>::type, unknown >::value) );

  // Same familly, bigger grain wins
  NT2_TEST( (is_same<dominant<bar_,foo_,foo_>::type, bar_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,bar_,foo_>::type, bar_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,foo_,bar_>::type, bar_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,bar_,bar_>::type, bar_category >::value) );
  NT2_TEST( (is_same<dominant<bar_,foo_,bar_>::type, bar_category >::value) );
  NT2_TEST( (is_same<dominant<bar_,bar_,foo_>::type, bar_category >::value) );

  // Biggest familly wins whatever grain
  NT2_TEST( (is_same<dominant<chu_,foo_,foo_>::type, chu_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,chu_,foo_>::type, chu_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,foo_,chu_>::type, chu_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,chu_,chu_>::type, chu_category >::value) );
  NT2_TEST( (is_same<dominant<chu_,foo_,chu_>::type, chu_category >::value) );
  NT2_TEST( (is_same<dominant<chu_,chu_,foo_>::type, chu_category >::value) );

  NT2_TEST( (is_same<dominant<moo_,foo_,foo_>::type, moo_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,moo_,foo_>::type, moo_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,foo_,moo_>::type, moo_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,moo_,moo_>::type, moo_category >::value) );
  NT2_TEST( (is_same<dominant<moo_,foo_,moo_>::type, moo_category >::value) );
  NT2_TEST( (is_same<dominant<moo_,moo_,foo_>::type, moo_category >::value) );

  NT2_TEST( (is_same<dominant<foo_,moo_,chu_>::type, moo_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,chu_,moo_>::type, moo_category >::value) );
  NT2_TEST( (is_same<dominant<moo_,foo_,chu_>::type, moo_category >::value) );
  NT2_TEST( (is_same<dominant<chu_,foo_,moo_>::type, moo_category >::value) );
  NT2_TEST( (is_same<dominant<chu_,moo_,foo_>::type, moo_category >::value) );
  NT2_TEST( (is_same<dominant<moo_,chu_,foo_>::type, moo_category >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test dominant type of f(A0,A1,A2,A3)
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(quaternary_dominant)
{
  using boost::is_same;
  using boost::result_of;
  using nt2::tag::unknown;
  using nt2::meta::dominant;

  // Same type, trivial categorization
  NT2_TEST( (is_same<dominant<foo_,foo_,foo_,foo_>::type, foo_category >::value) );

  // unknown wins everytime (evenwith bigger boys)
  NT2_TEST( (is_same<dominant<unk,foo_,bar_,chu_>::type, unknown >::value) );
  NT2_TEST( (is_same<dominant<foo_,unk,moo_,chu_>::type, unknown >::value) );
  NT2_TEST( (is_same<dominant<moo_,foo_,unk,bar_>::type, unknown >::value) );
  NT2_TEST( (is_same<dominant<moo_,foo_,chu_,unk>::type, unknown >::value) );

  // Same familly, bigger grain wins
  NT2_TEST( (is_same<dominant<bar_,foo_,foo_,foo_>::type, bar_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,bar_,foo_,foo_>::type, bar_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,foo_,bar_,foo_>::type, bar_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,foo_,foo_,bar_>::type, bar_category >::value) );
  NT2_TEST( (is_same<dominant<bar_,bar_,foo_,foo_>::type, bar_category >::value) );
  NT2_TEST( (is_same<dominant<bar_,foo_,bar_,foo_>::type, bar_category >::value) );
  NT2_TEST( (is_same<dominant<bar_,foo_,foo_,bar_>::type, bar_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,bar_,bar_,foo_>::type, bar_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,bar_,foo_,bar_>::type, bar_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,foo_,bar_,bar_>::type, bar_category >::value) );

  // Biggest familly wins whatever grain
  NT2_TEST( (is_same<dominant<chu_,foo_,foo_,foo_>::type, chu_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,chu_,foo_,foo_>::type, chu_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,foo_,chu_,foo_>::type, chu_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,foo_,foo_,chu_>::type, chu_category >::value) );
  NT2_TEST( (is_same<dominant<chu_,chu_,foo_,foo_>::type, chu_category >::value) );
  NT2_TEST( (is_same<dominant<chu_,foo_,chu_,foo_>::type, chu_category >::value) );
  NT2_TEST( (is_same<dominant<chu_,foo_,foo_,chu_>::type, chu_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,chu_,chu_,foo_>::type, chu_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,chu_,foo_,chu_>::type, chu_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,foo_,chu_,chu_>::type, chu_category >::value) );

  NT2_TEST( (is_same<dominant<moo_,foo_,foo_,foo_>::type, moo_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,moo_,foo_,foo_>::type, moo_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,foo_,moo_,foo_>::type, moo_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,foo_,foo_,moo_>::type, moo_category >::value) );
  NT2_TEST( (is_same<dominant<moo_,moo_,foo_,foo_>::type, moo_category >::value) );
  NT2_TEST( (is_same<dominant<moo_,foo_,moo_,foo_>::type, moo_category >::value) );
  NT2_TEST( (is_same<dominant<moo_,foo_,foo_,moo_>::type, moo_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,moo_,moo_,foo_>::type, moo_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,moo_,foo_,moo_>::type, moo_category >::value) );
  NT2_TEST( (is_same<dominant<foo_,foo_,moo_,moo_>::type, moo_category >::value) );
}

