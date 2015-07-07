//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/fast_sincosd.hpp>
#include <nt2/trig_derivatives/include/functions/fast_sincosd.hpp>
#include <nt2/include/functions/sind.hpp>
#include <nt2/include/functions/cosd.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

 #include <nt2/include/constants/_30.hpp>

NT2_TEST_CASE_TPL ( fast_sincosd_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::fast_sincosd;
  using nt2::tag::fast_sincosd_;

  T a = nt2::_30<T>();
  T s, c;
  fast_sincosd<1>(a, s, c);
  NT2_TEST_ULP_EQUAL(s, nt2::sind<1>(a), 0.5);
  NT2_TEST_ULP_EQUAL(c, nt2::cosd<1>(a), 0.5);
  fast_sincosd<2>(a, s, c);
  NT2_TEST_ULP_EQUAL(s, nt2::sind<2>(a), 0.5);
  NT2_TEST_ULP_EQUAL(c, nt2::cosd<2>(a), 0.5);
  fast_sincosd<3>(a, s, c);
  NT2_TEST_ULP_EQUAL(s, nt2::sind<3>(a), 0.5);
  NT2_TEST_ULP_EQUAL(c, nt2::cosd<3>(a), 0.5);

}

