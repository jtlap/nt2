//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 polynom toolbox - ratfracder/table Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of polynomials components in scalar mode
//////////////////////////////////////////////////////////////////////////////

#include <nt2/table.hpp>
#include <nt2/include/functions/ratfracder.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/of_size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL ( ratfracder_real__1_0, NT2_REAL_TYPES)
{

  using nt2::ratfracder;
  using nt2::tag::ratfracder_;
  nt2::table<T> a =  nt2::_(T(1), T(4));
  nt2::table<T> b =  nt2::_(T(1), T(3));
  nt2::table<T> c(nt2::of_size(1, 0));
  nt2::table<T> n, d;
  T rn[]  = { 1, 4, 10,  4, 1 };
  T rd [] = { 1, 4, 10, 12, 9 };
  T dab[] = { 1, 4, 10,  4, 1 };
  T da [] = { 3, 4, 3 };
  nt2::table<T> rdab(nt2::of_size(1, 5), &dab[0], &dab[5]);
  nt2::table<T> rda (nt2::of_size(1, 3), &da[0], &da[3]);
  nt2::table<T> rnn (nt2::of_size(1, 5), &rn[0], &rn[5]);
  nt2::table<T> rdd (nt2::of_size(1, 5), &rd[0], &rd[5]);

  NT2_TEST_EQUAL(rda, ratfracder(a));
  NT2_TEST_EQUAL(rdab, ratfracder(a, b));

  nt2::tie(n, d) = ratfracder(a, b);
  NT2_TEST_EQUAL(rnn, n);
  NT2_TEST_EQUAL(rdd, d);
}


