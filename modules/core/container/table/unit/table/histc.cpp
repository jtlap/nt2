//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/histc.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/table.hpp>
#include <boost/simd/sdk/simd/io.hpp>

NT2_TEST_CASE_TPL( histc, NT2_REAL_TYPES )
{
  using nt2::table;
  using nt2::histc;

  table<T> x = nt2::linspace(T(-10), T(10), 10000);
  table<std::size_t> h =  histc(x, 20);
  NT2_DISPLAY(h);
  NT2_TEST_EQUAL(h, nt2::repnum(std::size_t(500), 20));
}
