/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 function sum"

#include <nt2/table.hpp>
#include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL( sum, NT2_REAL_TYPES)
{
  using nt2::table;
  using nt2::of_size;
  using nt2::sum;
  using nt2::_;
  typedef std::complex<T>  cT;

  std::size_t M = 5;

  table<cT> r, r1;
  table<cT> a = cT(2, 1)*nt2::ones(2, 3, nt2::meta::as_<cT>());
  r = sum(a(nt2::_));
  NT2_TEST_EQUAL(r(1),cT(12, 6)) ;
  r = sum(a, 1);
  NT2_TEST_EQUAL(r,cT(4, 2)*nt2::ones(1, 3, nt2::meta::as_<cT>())) ;
  r = sum(a, 2);
  NT2_TEST_EQUAL(r,cT(6, 3)*nt2::ones(2, 1, nt2::meta::as_<cT>())) ;
  r = sum(a, 3);
  NT2_TEST_EQUAL(r,cT(2, 1)*nt2::ones(2,3, nt2::meta::as_<cT>())) ;
}
