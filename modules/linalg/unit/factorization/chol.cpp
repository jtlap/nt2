//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - cholesky factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/chol.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(chol_factorization, NT2_REAL_TYPES)
{
  using nt2::tag::factorization::chol_;

  typedef nt2::table<T> t_t;
  t_t b =       nt2::ones (4, 4, nt2::meta::as_<T>())
        + T(10)*nt2::eye  (4, 4, nt2::meta::as_<T>());

  typedef typename nt2::meta::call<chol_(t_t const&,char)>::type result_type;

  result_type res = nt2::factorization::chol(b,'U');

  NT2_DISPLAY(res.result());
  NT2_DISPLAY(res.upper_result());
  NT2_TEST_EQUAL(res.status(), 0u);

  b = nt2::zeros(4, 4, nt2::meta::as_<T>());
  b(1,1) = 1;
  res = nt2::factorization::chol(b,'U');

  NT2_DISPLAY(res.result());
  NT2_DISPLAY(res.upper_result());
  NT2_TEST_EQUAL(res.status(), 2u);

  NT2_TEST_ASSERT( nt2::factorization::chol(nt2::ones(4, 2),'U') );
}

NT2_TEST_CASE_TPL ( chol_factorization_inplace, NT2_REAL_TYPES)
{
  using nt2::tag::factorization::chol_;
  using nt2::meta::as_;

  typedef nt2::table<T> t_t;
  t_t b =       nt2::ones (4, 4, nt2::meta::as_<T>())
        + T(10)*nt2::eye  (4, 4, nt2::meta::as_<T>());

  typedef typename nt2::meta::call
          <chol_(t_t&, char, as_<nt2::details::in_place_> const&)>::type ip_t;

  ip_t ires = nt2::factorization::chol(b,'L',nt2::in_place_);

  NT2_DISPLAY(ires.result());
  NT2_DISPLAY(ires.lower_result());
  NT2_TEST_EQUAL(ires.status(), 0u);

  b = nt2::zeros(4, 4, nt2::meta::as_<T>());
  b(1,1) = 1;
  ires = nt2::factorization::chol(b,'U',nt2::in_place_);

  NT2_DISPLAY(ires.result());
  NT2_DISPLAY(ires.upper_result());
  NT2_TEST_EQUAL(ires.status(), 2u);

  b = nt2::ones(4, 2, nt2::meta::as_<T>());
  NT2_TEST_ASSERT( nt2::factorization::chol(b,'U',nt2::in_place_) );
}
