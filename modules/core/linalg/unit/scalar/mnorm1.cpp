//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/mnorm1.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/hundred.hpp>
#include <nt2/linalg/options.hpp>

#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>


NT2_TEST_CASE_TPL(norm, NT2_REAL_TYPES)
{
  using nt2::mnorm1;
  using nt2::tag::mnorm1_;
  NT2_TEST_ULP_EQUAL(mnorm1(T(-3)),  nt2::Three<T>(), 0);
  nt2::table<T> n = nt2::ones(1, 10, nt2::meta::as_<T>());
  NT2_TEST_ULP_EQUAL(mnorm1(n),  nt2::One<T>(), 0);
  nt2::table<T> n1 = nt2::ones(10, 1, nt2::meta::as_<T>());
  NT2_TEST_ULP_EQUAL(mnorm1(n1),  nt2::Ten<T>(), 0);
  nt2::table<T> a = nt2::ones(10, 10, nt2::meta::as_<T>());
  NT2_TEST_ULP_EQUAL(mnorm1(a), nt2::Ten<T>(), 0);
  nt2::table<T, nt2::of_size_<1,10> > ns=  n;
  NT2_TEST_ULP_EQUAL(mnorm1(ns),  nt2::One<T>(), 0);
  nt2::table<T, nt2::of_size_<10,1> > ns1 = n1;
  NT2_TEST_ULP_EQUAL(mnorm1(ns1),  nt2::Ten<T>(), 0);
  nt2::table<T, nt2::of_size_<10,10> > as = a;
  NT2_TEST_ULP_EQUAL(mnorm1(as), nt2::Ten<T>(), 0);
}

NT2_TEST_CASE_TPL(norm_c, NT2_REAL_TYPES)
{
  using nt2::mnorm1;
  using nt2::tag::mnorm1_;
  typedef std::complex<T> cT;
  NT2_TEST_ULP_EQUAL(mnorm1(cT(-3)),  nt2::Three<T>(), 0);
  nt2::table<cT> n = nt2::ones(1, 10, nt2::meta::as_<T>());
  NT2_TEST_ULP_EQUAL(mnorm1(n),  nt2::One<T>(), 0);
  nt2::table<cT> n1 = nt2::ones(10, 1, nt2::meta::as_<T>());
  NT2_TEST_ULP_EQUAL(mnorm1(n1),  nt2::Ten<T>(), 0);
  nt2::table<cT> a = nt2::ones(10, 10, nt2::meta::as_<T>());
  NT2_TEST_ULP_EQUAL(mnorm1(a), nt2::Ten<T>(), 0);
  nt2::table<cT, nt2::of_size_<1,10> > ns=  n;
  NT2_TEST_ULP_EQUAL(mnorm1(ns),  nt2::One<T>(), 0);
  nt2::table<cT, nt2::of_size_<10,1> > ns1 = n1;
  NT2_TEST_ULP_EQUAL(mnorm1(ns1),  nt2::Ten<T>(), 0);
  nt2::table<cT, nt2::of_size_<10,10> > as = a;
  NT2_TEST_ULP_EQUAL(mnorm1(as), nt2::Ten<T>(), 0);
}
