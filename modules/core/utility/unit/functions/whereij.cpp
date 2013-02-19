/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::whereij function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/whereij.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/band.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <boost/lambda/lambda.hpp>

NT2_TEST_CASE_TPL( whereij_1, NT2_TYPES)
{
  nt2::table<T> a = nt2::rif(nt2::of_size(3, 3), nt2::meta::as_<T>()),
                b = nt2::zeros(nt2::of_size(3, 3), nt2::meta::as_<T>()),
                e, f, g, h;

  e = nt2::whereij(nt2::functor<nt2::tag::is_less_equal_>(),  a, b);
  NT2_DISPLAY(e);
  NT2_DISPLAY(nt2::triu(a));
  NT2_TEST_EQUAL(e, nt2::triu(a));
  f = whereij(nt2::functor<nt2::tag::is_equal_>(),  a, b);
  NT2_TEST_EQUAL(f, nt2::from_diag(nt2::diag_of(a)));
  NT2_TEST_EQUAL( nt2::whereij(nt2::functor<nt2::tag::is_equal_>(),  a, b), f);
  g = nt2::whereij(nt2::functor<nt2::tag::is_equal_>(),  a, nt2::zeros(3, nt2::meta::as_<T>()));
  NT2_TEST_EQUAL(g, nt2::from_diag(nt2::diag_of(a)));
  h = nt2::whereij(nt2::functor<nt2::tag::is_equal_>(),  a, nt2::Zero<T>());
  NT2_TEST_EQUAL(h, nt2::from_diag(nt2::diag_of(a)));
  NT2_DISPLAY(nt2::from_diag(nt2::diag_of(a)));
  NT2_DISPLAY(h);
}


// NT2_TEST_CASE_TPL( whereij_lambda, NT2_TYPES)
// {
//   namespace bl = boost::lambda;
//   nt2::table<T> a = nt2::rif(nt2::of_size(3, 3), nt2::meta::as_<T>()),
//     b = nt2::zeros(nt2::of_size(3, 3), nt2::meta::as_<T>()),
//     e, f;

//   e = nt2::whereij(        (bl::_1 <= bl::_2),  a, b);
//   NT2_DISPLAY(e);
//   NT2_DISPLAY(nt2::triu(a));
//   NT2_TEST_EQUAL(e, nt2::triu(a));
//   f = nt2::whereij((bl::_1 == bl::_2),  a, b);
//   NT2_TEST_EQUAL(f, nt2::from_diag(nt2::diag_of(a)));
// }

struct fct1
{

  template < class A0, class A1>
  typename nt2::meta::as_logical<A0>::type
  operator ()(const A0& i, const A1& j) const
  {
    return nt2::logical_and(nt2::le(i, nt2::oneplus(j)),
                            nt2::le(j, nt2::oneplus(i))
                           );
  }

};

struct fct2
{

  template < class A0, class A1>
  typename nt2::meta::as_logical<A0>::type
  operator ()(const A0& i, const A1& j) const
  {
    return nt2::eq(i, j);
  }

};


NT2_TEST_CASE_TPL( whereij_func, NT2_TYPES)
{
  namespace bl = boost::lambda;
  nt2::table<T> a = nt2::rif(nt2::of_size(3, 3), nt2::meta::as_<T>()),
    b = nt2::zeros(nt2::of_size(3, 3), nt2::meta::as_<T>()),
    e, f;

  e = whereij(fct1(),  a, b);
  NT2_DISPLAY(e);
  NT2_DISPLAY(nt2::band(a, 1, 1));
  NT2_TEST_EQUAL(e, nt2::band(a, 1, 1));
  f = whereij(fct2(),  a, b);
  NT2_TEST_EQUAL(f, nt2::from_diag(nt2::diag_of(a)));
  NT2_TEST_EQUAL(f, nt2::diagonal(a));
}
