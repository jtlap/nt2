//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/sincos.hpp>
#include <nt2/trig_derivatives/include/functions/sincos.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

 #include <nt2/include/constants/pio_3.hpp>

NT2_TEST_CASE_TPL ( sincos_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::sincos;
  using nt2::tag::sincos_;

  T a = nt2::Pio_3<T>();
  T s, c;
  sincos<1>(a, s, c);
  NT2_TEST_ULP_EQUAL(s, nt2::sin<1>(a), 0.5);
  NT2_TEST_ULP_EQUAL(c, nt2::cos<1>(a), 0.5);
  sincos<2>(a, s, c);
  NT2_TEST_ULP_EQUAL(s, nt2::sin<2>(a), 0.5);
  NT2_TEST_ULP_EQUAL(c, nt2::cos<2>(a), 0.5);
  sincos<3>(a, s, c);
  NT2_TEST_ULP_EQUAL(s, nt2::sin<3>(a), 0.5);
  NT2_TEST_ULP_EQUAL(c, nt2::cos<3>(a), 0.5);

}

