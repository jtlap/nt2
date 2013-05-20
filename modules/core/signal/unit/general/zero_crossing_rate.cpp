//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 polynom toolbox - zero_crossing_rate/scalar Mode"

#include <nt2/signal/include/functions/zero_crossing_rate.hpp>
#include <nt2/include/functions/cospi.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/round.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/table.hpp>



NT2_TEST_CASE_TPL ( zero_crossing_rate_real__1_0,  NT2_REAL_TYPES)
{
  using nt2::zero_crossing_rate;
  using nt2::tag::zero_crossing_rate_;
  nt2::table<T> s = nt2::cospi(nt2::_(T(0), T(10)));

  T e = T(0.1);
  NT2_TEST_ULP_EQUAL(zero_crossing_rate(s)(1), T(1), 0.5);
  NT2_TEST_ULP_EQUAL(zero_crossing_rate(nt2::_(T(0), T(10))), T(0), 0.5);
  NT2_TEST_ULP_EQUAL(zero_crossing_rate(nt2::cospi(nt2::_(T(e), T(0.5), T(e+10)))), T(0.5), 0.5);
  NT2_TEST_ULP_EQUAL(zero_crossing_rate(nt2::round(T(2)*nt2::cospi(nt2::_(T(0), T(0.5), T(10))))/T(2)), T(0.5), 0.5);

}
