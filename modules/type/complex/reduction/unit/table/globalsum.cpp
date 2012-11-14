/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::globalsum function"

#include <nt2/table.hpp>
#include <nt2/include/functions/globalsum.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/table.hpp>


NT2_TEST_CASE_TPL( globalsumc, NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;
  nt2::table<cT> a = nt2::reshape(nt2::ones(1, 9, nt2::meta::as_<cT>()), 3, 3);
  NT2_DISPLAY(a);
  NT2_TEST_EQUAL( nt2::globalsum(a), cT(9));
  NT2_TEST_EQUAL( nt2::globalsum(cT(0)), cT(0));
}
