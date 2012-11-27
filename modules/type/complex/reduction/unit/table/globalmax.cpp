/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::globalmax function"

#include <nt2/table.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/complexify.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( globalmax, (float))//NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;
  nt2::table<cT> a = nt2::reshape(nt2::complexify(nt2::_(T(1), T(9))), 3, 3);
  NT2_TEST_EQUAL(nt2::globalmax(a), cT(9));
  NT2_TEST_EQUAL(nt2::globalmax(cT(1)), cT(1));
  a(3, 1) = cT(27);
  NT2_TEST_EQUAL(nt2::globalmax(a), cT(27));
  std::size_t i;
  NT2_TEST_EQUAL(nt2::globalmax(a, i), cT(27));
  NT2_TEST_EQUAL(i, 3u);
}
