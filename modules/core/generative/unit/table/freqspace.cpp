/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::freqspace function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/log10.hpp>
#include <nt2/include/functions/exp10.hpp>
#include <nt2/include/functions/freqspace.hpp>
#include <nt2/include/functions/isulpequal.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests.hpp>

NT2_TEST_CASE_TPL( freqspace, (double) )
{
  using nt2::freqspace;
  nt2::table<T> f1, f2;
  nt2::table<int, nt2::settings(nt2::_2D)> a(nt2::of_size(1, 4));
  a(1) = 8; a(2) = 24;
  nt2::tie(f1) = freqspace(10);
 NT2_TEST(isulpequal(f1, nt2::_(T(0), T(0.2), T(1))));
  std::cout << " f1 " << f1 << std::endl;
  nt2::tie(f1,f2) = freqspace(10);
  std::cout << " f1 " << f1 << std::endl;
  std::cout << " f2 " << f2 << std::endl;
  NT2_TEST(isulpequal(f1, nt2::_(T(-1), T(0.2), T(0.8))));
}
