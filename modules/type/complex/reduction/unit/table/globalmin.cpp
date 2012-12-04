/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::globalmin function"

#include <nt2/table.hpp>
#include <nt2/include/functions/globalmin.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/complexify.hpp>
#include <nt2/include/constants/true.hpp>
#include <nt2/include/constants/false.hpp>
#include <nt2/include/constants/i.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL( globalmin, NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;
  nt2::table<cT> a = nt2::reshape(nt2::complexify(nt2::_(T(101), T(109))), 3, 3);
  a = a+nt2::I<cT>()*a;
  NT2_TEST_EQUAL( nt2::globalmin(a), cT(101, 101));
  NT2_TEST_EQUAL( nt2::globalmin(T(1)), cT(1));
  a(3, 1) = cT(27);
  NT2_TEST_EQUAL( nt2::globalmin(a), cT(27));
  int32_t i;
  NT2_TEST_EQUAL( nt2::globalmin(a, i), cT(27));
  NT2_TEST( i == 3);
}

