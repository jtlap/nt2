//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/norm_fro.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/five.hpp>
#include <nt2/linalg/options.hpp>

#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>


NT2_TEST_CASE_TPL(norm, NT2_REAL_TYPES)
{
  using nt2::norm_fro;
  using nt2::tag::norm_fro_;
  nt2::table<T> n = nt2::ones(1, 25, nt2::meta::as_<T>());
  NT2_TEST_ULP_EQUAL(nt2::norm_fro(n)              ,  nt2::Five<T>(), 0);
  NT2_TEST_ULP_EQUAL(norm_fro(n, nt2::vector_),  nt2::Five<T>(), 0);
  NT2_TEST_ULP_EQUAL(norm_fro(n, nt2::matrix_),  nt2::Five<T>(), 0);
  nt2::table<T> a = nt2::ones(5, 5, nt2::meta::as_<T>());
  NT2_TEST_ULP_EQUAL(norm_fro(a), nt2::Five<T>(), 0);
  NT2_TEST_ULP_EQUAL(norm_fro(a,nt2::vector_), nt2::Five<T>(), 0);
  NT2_TEST_ULP_EQUAL(norm_fro(a,nt2::matrix_), nt2::Five<T>(), 0);
}
