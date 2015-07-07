//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/fast_sincospi.hpp>
#include <nt2/trig_derivatives/include/functions/fast_sincospi.hpp>
#include <nt2/include/functions/sinpi.hpp>
#include <nt2/include/functions/cospi.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

 #include <nt2/include/constants/oneo_7.hpp>

NT2_TEST_CASE_TPL ( fast_sincospi_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::fast_sincospi;
  using nt2::tag::fast_sincospi_;

  T a = nt2::Oneo_7<T>();
  T s, c;
  fast_sincospi<1>(a, s, c);
  NT2_TEST_ULP_EQUAL(s, nt2::sinpi<1>(a), 0.5);
  NT2_TEST_ULP_EQUAL(c, nt2::cospi<1>(a), 0.5);
  fast_sincospi<2>(a, s, c);
  NT2_TEST_ULP_EQUAL(s, nt2::sinpi<2>(a), 0.5);
  NT2_TEST_ULP_EQUAL(c, nt2::cospi<2>(a), 0.5);
  fast_sincospi<3>(a, s, c);
  NT2_TEST_ULP_EQUAL(s, nt2::sinpi<3>(a), 0.5);
  NT2_TEST_ULP_EQUAL(c, nt2::cospi<3>(a), 0.5);

}

