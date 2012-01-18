//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::dispatch::meta combine test"

#include <boost/dispatch/meta/combine.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

struct a0 {};
struct a1 {};
template<class T> struct b0 {};
template<class T> struct b1 {};
template<class T> struct c0 {};
template<class T> struct c1 {};

NT2_TEST_CASE(combine)
{
  using boost::dispatch::meta::combine;
  using boost::mpl::_;
  
  NT2_TEST_EXPR_TYPE((combine<a0, a0>::type()), _, a0);
  NT2_TEST_EXPR_TYPE((combine<a0, a1>::type()), _, a1);
  NT2_TEST_EXPR_TYPE((combine<a0, b0<a0> >::type()), _, b0<a0> );
  NT2_TEST_EXPR_TYPE((combine<a0, b0<a1> >::type()), _, b0<a0> );
  NT2_TEST_EXPR_TYPE((combine<a0, b1<a0> >::type()), _, b1<a0> );
  NT2_TEST_EXPR_TYPE((combine<a0, b1<a1> >::type()), _, b1<a0> );
  NT2_TEST_EXPR_TYPE((combine<a0, c0< b0<a0> > >::type()), _, c0<b0<a0> > );
  NT2_TEST_EXPR_TYPE((combine<a0, c0< b1<a0> > >::type()), _, c0<b1<a0> > );
  NT2_TEST_EXPR_TYPE((combine<a0, c1< b0<a0> > >::type()), _, c1<b0<a0> > );
  NT2_TEST_EXPR_TYPE((combine<a0, c1< b1<a0> > >::type()), _, c1<b1<a0> > );
  
  NT2_TEST_EXPR_TYPE((combine<b0<a0>, a0>::type()), _, b0<a0>);
  NT2_TEST_EXPR_TYPE((combine<b0<a0>, a1>::type()), _, b0<a1>);
  NT2_TEST_EXPR_TYPE((combine<b0<a0>, b0<a0> >::type()), _, b0<a0> );
  NT2_TEST_EXPR_TYPE((combine<b0<a0>, b0<a1> >::type()), _, b0<a0> );
  NT2_TEST_EXPR_TYPE((combine<b0<a0>, b1<a0> >::type()), _, b1<a0> );
  NT2_TEST_EXPR_TYPE((combine<b0<a0>, b1<a1> >::type()), _, b1<a0> );
  NT2_TEST_EXPR_TYPE((combine<b0<a0>, c0< b0<a0> > >::type()), _, c0<b0<a0> > );
  NT2_TEST_EXPR_TYPE((combine<b0<a0>, c0< b1<a0> > >::type()), _, c0<b0<a0> > );
  NT2_TEST_EXPR_TYPE((combine<b0<a0>, c1< b0<a0> > >::type()), _, c1<b0<a0> > );
  NT2_TEST_EXPR_TYPE((combine<b0<a0>, c1< b1<a0> > >::type()), _, c1<b0<a0> > );
  
  NT2_TEST_EXPR_TYPE((combine<c0<b0<a0> >, a0>::type()), _, c0<b0<a0> >);
  NT2_TEST_EXPR_TYPE((combine<c0<b0<a0> >, a1>::type()), _, c0<b0<a1> >);
  NT2_TEST_EXPR_TYPE((combine<c0<b0<a0> >, b0<a0> >::type()), _, c0<b0<a0> > );
  NT2_TEST_EXPR_TYPE((combine<c0<b0<a0> >, b0<a1> >::type()), _, c0<b0<a0> > );
  NT2_TEST_EXPR_TYPE((combine<c0<b0<a0> >, b1<a0> >::type()), _, c0<b1<a0> > );
  NT2_TEST_EXPR_TYPE((combine<c0<b0<a0> >, b1<a1> >::type()), _, c0<b1<a0> > );
  NT2_TEST_EXPR_TYPE((combine<c0<b0<a0> >, c0< b0<a0> > >::type()), _, c0<b0<a0> > );
  NT2_TEST_EXPR_TYPE((combine<c0<b0<a0> >, c0< b1<a0> > >::type()), _, c0<b0<a0> > );
  NT2_TEST_EXPR_TYPE((combine<c0<b0<a0> >, c1< b0<a0> > >::type()), _, c1<b0<a0> > );
  NT2_TEST_EXPR_TYPE((combine<c0<b0<a0> >, c1< b1<a0> > >::type()), _, c1<b0<a0> > );
}
