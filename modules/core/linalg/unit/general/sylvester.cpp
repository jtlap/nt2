//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/sylvester.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/tril.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/core/container/colon/colon.hpp>
NT2_TEST_CASE_TPL(sylvester0, NT2_REAL_TYPES)
{
  NT2_TEST_EQUAL(nt2::sylvester(T(2), T(4), T(6)), T(1));
 }

NT2_TEST_CASE_TPL(sylvester1, NT2_REAL_TYPES)//distinct eigenvalues
{
  using nt2::sylvester;
  using nt2::tag::sylvester_;
  nt2::table<T> a =  nt2::triu(nt2::reshape(nt2::_(T(1), T(9)), 3, 3));
  nt2::table<T> b =  nt2::triu(nt2::ones(3, 3, nt2::meta::as_<T>()));
  nt2::table<T> x =  nt2::tril(nt2::reshape(nt2::_(T(1), T(9)), 3, 3));
  nt2::table<T> c =  nt2::mtimes(a, x)+nt2::mtimes(x, b);
  nt2::table<T> r =  sylvester(a, b, c);
  NT2_DISPLAY(x);
  NT2_DISPLAY(r);
  std::cout << nt2::globalmax(nt2::abs(r-x)) << std::endl;
  NT2_TEST_EQUAL(r, x);

 }

NT2_TEST_CASE_TPL(sylvester2, NT2_REAL_TYPES)
{
  using nt2::sylvester;
  using nt2::tag::sylvester_;
  nt2::table<T> a =  nt2::from_diag(nt2::_(T(1), T(3)));
  nt2::table<T> b =  nt2::from_diag(nt2::ones(1, 3, nt2::meta::as_<T>()));
  nt2::table<T> x =  nt2::reshape(nt2::_(T(1), T(9)), 3, 3);
  nt2::table<T> c =  nt2::mtimes(a, x)+nt2::mtimes(x, b);
  nt2::table<T> r =  sylvester(a, b, c);
  NT2_DISPLAY(x);
  NT2_DISPLAY(r);
  std::cout << nt2::globalmax(nt2::abs(r-x)) << std::endl;
  NT2_TEST_EQUAL(r, x);

 }
NT2_TEST_CASE_TPL(sylvester3, NT2_REAL_TYPES)
{
  using nt2::sylvester;
  using nt2::tag::sylvester_;
  typedef std::complex<T> cT;

  nt2::table<cT> a =  nt2::from_diag(nt2::linspace(cT(1, 1), cT(3, 1), 3));
  nt2::table<cT> b =  nt2::from_diag(nt2::ones(1, 3, nt2::meta::as_<cT>()));
  nt2::table<cT> x =  nt2::reshape(nt2::linspace(cT(1, 1), cT(9, 9), 9), 3, 3);
  nt2::table<cT> c =  nt2::mtimes(a, x)+nt2::mtimes(x, b);
  nt2::table<cT> r =  sylvester(a, b, c);
  NT2_DISPLAY(x);
  NT2_DISPLAY(r);
  std::cout << nt2::globalmax(nt2::abs(r-x)) << std::endl;
  NT2_TEST_EQUAL(r, x);

 }
NT2_TEST_CASE_TPL(sylvester4, NT2_REAL_TYPES)
{
  using nt2::sylvester;
  using nt2::tag::sylvester_;
  typedef std::complex<T> cT;

  nt2::table<cT> a =  nt2::from_diag(nt2::linspace(cT(1, 1), cT(3, 1), 3));
  nt2::table<cT> x =  nt2::reshape(nt2::linspace(cT(1, 1), cT(9, 9), 9), 3, 3);
  nt2::table<cT> c =  nt2::mtimes(a, x)+nt2::mtimes(x, a);
  nt2::table<cT> r =  sylvester(a, c);
  NT2_DISPLAY(x);
  NT2_DISPLAY(r);
  std::cout << nt2::globalmax(nt2::abs(r-x)) << std::endl;
  NT2_TEST_EQUAL(r, x);

 }
NT2_TEST_CASE_TPL(sylvester5, NT2_REAL_TYPES)
{
  using nt2::sylvester;
  using nt2::tag::sylvester_;
  typedef std::complex<T> cT;

  nt2::table<cT> a =  nt2::from_diag(nt2::linspace(cT(1, 1), cT(3, 1), 3));
  nt2::table<cT> x =  nt2::reshape(nt2::linspace(cT(1, 1), cT(9, 9), 9), 3, 3);
  nt2::table<cT> c =  nt2::mtimes(ctrans(a), x)+nt2::mtimes(x, a);
  nt2::table<cT> r =  sylvester(ctrans(a), a, c);
  NT2_DISPLAY(x);
  NT2_DISPLAY(r);
  std::cout << nt2::globalmax(nt2::abs(r-x)) << std::endl;
  NT2_TEST_EQUAL(r, x);

 }

