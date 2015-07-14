//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/hyperbolic/include/functions/sinhcosh.hpp>
#include <nt2/hyp_derivatives/include/functions/sinhcosh.hpp>
#include <nt2/include/functions/sinh.hpp>
#include <nt2/include/functions/cosh.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

 #include <nt2/include/constants/one.hpp>

NT2_TEST_CASE_TPL ( sinhcosh_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::sinhcosh;
  using nt2::tag::sinhcosh_;

  T a = nt2::One<T>();
  T s, c;
  nt2::sinhcosh<1>(a, s, c);
  NT2_TEST_ULP_EQUAL(s, nt2::sinh<1>(a), 0.5);
  NT2_TEST_ULP_EQUAL(c, nt2::cosh<1>(a), 0.5);
  sinhcosh<2>(a, s, c);
  NT2_TEST_ULP_EQUAL(s, nt2::sinh<2>(a), 0.5);
  NT2_TEST_ULP_EQUAL(c, nt2::cosh<2>(a), 0.5);
  sinhcosh<3>(a, s, c);
  NT2_TEST_ULP_EQUAL(s, nt2::sinh<3>(a), 0.5);
  NT2_TEST_ULP_EQUAL(c, nt2::cosh<3>(a), 0.5);

}

