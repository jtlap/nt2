//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::deltac function"
#include <nt2/table.hpp>
#include <nt2/include/functions/deltac.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/zeros.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <boost/dispatch/meta/nth_hierarchy.hpp>
#include <nt2/sdk/meta/type_id.hpp>

NT2_TEST_CASE( untyped )
{
  using boost::mpl::_;
  using nt2::meta::value_type_;

  nt2::table<float> ref =  nt2::zeros(3, 3);
  ref(2, 3) = 1.0;
  NT2_DISPLAY(ref);
  nt2::table<int> p(nt2::of_size(1, 2)); p(1) = p(2) = 3;
  nt2::table<float> x0 = nt2::deltac(0, 2, nt2::of_size(3, 3), nt2::meta::as_<float>());
  nt2::table<float> x1 = nt2::deltac(1, 2, 3, nt2::meta::as_<float>());
  NT2_DISPLAY(x0);
  NT2_TEST_EQUAL(ref, nt2::deltac(1, 2, 3, nt2::meta::as_<float>()));
  NT2_TEST_EQUAL(ref, nt2::deltac(1, 2, 3, 3, nt2::meta::as_<float>()));
  NT2_TEST_EQUAL(ref, nt2::deltac(1, 2, p, nt2::meta::as_<float>()));
}
