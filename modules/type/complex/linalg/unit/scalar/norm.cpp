//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/norm.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>

NT2_TEST_CASE_TPL(norm, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_complex<T>::type  cT;
  using nt2::norm;
  using nt2::tag::norm_;
  nt2::table<cT> n = nt2::ones(10, 1, nt2::meta::as_<cT>());
  NT2_TEST_ULP_EQUAL(norm(n, 1), nt2::Ten<T>(), 0);
  NT2_TEST_ULP_EQUAL(norm(n, 2), nt2::sqrt(nt2::Ten<T>()), 0);
  NT2_TEST_ULP_EQUAL(norm(n)   , nt2::sqrt(nt2::Ten<T>()), 0);
  NT2_TEST_ULP_EQUAL(norm(n, 3), nt2::pow(nt2::Ten<T>(), 1/T(3)), 0);
  NT2_TEST_ULP_EQUAL(norm(n, nt2::Inf<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(norm(n, nt2::Minf<T>()), nt2::One<T>(), 0);

  nt2::table<cT> a = nt2::ones(10, 10, nt2::meta::as_<cT>());
  NT2_TEST_ULP_EQUAL(norm(a, 1), nt2::Ten<T>(), 0);
  NT2_TEST_ULP_EQUAL(norm(a, 2), norm(a), 0);
  NT2_TEST_ULP_EQUAL(norm(a, nt2::Inf<T>()), nt2::Ten<T>(), 0);
  NT2_TEST_ULP_EQUAL(norm(a, nt2::fro_), nt2::Ten<T>(), 0);

  NT2_TEST_ULP_EQUAL(norm(a+a, 1), 2*nt2::Ten<T>(), 0);
  NT2_TEST_ULP_EQUAL(norm(a+a, 2), norm(a+a), 0);
  NT2_TEST_ULP_EQUAL(norm(a+a, nt2::Inf<T>()), 2*nt2::Ten<T>(), 0);
  NT2_TEST_ULP_EQUAL(norm(a+a, nt2::fro_), 2*nt2::Ten<T>(), 0);
}
