//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 function cummax"

#include <nt2/table.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/cummax.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/isequal.hpp>

#include <nt2/include/functions/ones.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL( cummax,  BOOST_SIMD_SIMD_REAL_TYPES )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::cummax;
  using nt2::reshape;
  using nt2::_;

  table<T> a = nt2::_(T(1), T(25));
  table<T> rb =  nt2::ones(1, 25, nt2::meta::as_<T>())*T(25);
  table<T> b = cummax(a);
  NT2_TEST_EQUAL(b, a);
  a =  nt2::_(T(25), T(-1), T(1));
  b = cummax(a);
  NT2_TEST_EQUAL(b, rb);
}

