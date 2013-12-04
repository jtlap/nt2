//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/acos.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/math/complex/acos.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/i.hpp>


NT2_TEST_CASE_TPL ( acos,  NT2_REAL_TYPES)
{
  using nt2::acos;
  using nt2::tag::acos_;
  typedef typename std::complex<T> cT;
  typedef typename nt2::meta::call<acos_(cT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, cT);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Nan <T>(),  nt2::Zero<T>())), cT(nt2::Nan <T>(), nt2::Nan<T>()), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Nan  <T>(), nt2::One<T>())),  cT(nt2::Nan <T>(), nt2::Nan<T>()), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Nan  <T>(), nt2::Inf<T>())),  cT(nt2::Nan <T>(), -nt2::Inf<T>()), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Nan  <T>(), nt2::Nan<T>())),  cT(nt2::Nan <T>(), nt2::Nan<T>()), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Zero <T>(), nt2::Nan <T>())), cT(nt2::Pio_2<T>(), nt2::Nan<T>()), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::One  <T>(), nt2::Nan <T>())), cT(nt2::Nan<T>(),  nt2::Nan<T>()), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Inf  <T>(), nt2::Nan<T>())),  cT(nt2::Nan <T>(), nt2::Minf<T>()), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::One  <T>(), nt2::Inf <T>())), cT(nt2::Pio_2<T>(), -nt2::Inf<T>()), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Inf  <T>(), nt2::One <T>())), cT(nt2::Zero<T>(), nt2::Minf <T>()), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Inf  <T>(), nt2::Inf<T>())),  cT(nt2::Pi<T>()/nt2::Four<T>(), nt2::Minf <T>()), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Nan  <T>(), nt2::One<T>())),  cT(nt2::Nan <T>(), nt2::Nan<T>()), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Nan  <T>(), nt2::Inf<T>())),  cT(nt2::Nan <T>(), -nt2::Inf<T>()), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Nan  <T>(), nt2::Nan<T>())),  cT(nt2::Nan <T>(), nt2::Nan<T>()), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Zero <T>(), nt2::Nan <T>())), cT(nt2::Pio_2<T>(), nt2::Nan<T>()), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::One  <T>(), nt2::Nan <T>())), cT(nt2::Nan<T>(),  nt2::Nan<T>()), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Inf  <T>(), nt2::Nan<T>())),  cT(nt2::Nan <T>(), nt2::Minf<T>()), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::One  <T>(), nt2::Inf <T>())), cT(nt2::Pio_2<T>(), nt2::Minf<T>()), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Inf  <T>(), nt2::One <T>())), cT(nt2::Pi<T>(), -nt2::Inf <T>()), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Inf  <T>(), nt2::Inf<T>())),  cT(nt2::Three<T>()*nt2::Pi<T>()/nt2::Four<T>(), nt2::Minf <T>()), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Nan  <T>(), nt2::One<T>())), boost::math::acos(cT(nt2::Nan  <T>(), nt2::One<T>())),  1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Nan  <T>(), nt2::Inf<T>())), boost::math::acos(cT(nt2::Nan  <T>(), nt2::Inf<T>())),  1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Nan  <T>(), nt2::Nan<T>())), boost::math::acos(cT(nt2::Nan  <T>(), nt2::Nan<T>())),  1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Zero <T>(), nt2::Nan <T>())),boost::math::acos(cT(nt2::Zero <T>(), nt2::Nan <T>())), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::One  <T>(), nt2::Nan <T>())),boost::math::acos(cT(nt2::One  <T>(), nt2::Nan <T>())), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Inf  <T>(), nt2::Nan<T>())), boost::math::acos(cT(nt2::Inf  <T>(), nt2::Nan<T>())),  1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::One  <T>(), nt2::Inf <T>())),boost::math::acos(cT(nt2::One  <T>(), nt2::Inf <T>())), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Inf  <T>(), nt2::One <T>())),boost::math::acos(cT(nt2::Inf  <T>(), nt2::One <T>())), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Inf  <T>(), nt2::Inf<T>())), boost::math::acos(cT(nt2::Inf  <T>(), nt2::Inf<T>())),  1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Nan  <T>(), nt2::One<T>())), boost::math::acos(cT(-nt2::Nan  <T>(), nt2::One<T>())),    1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Nan  <T>(), nt2::Inf<T>())), boost::math::acos(cT(-nt2::Nan  <T>(), nt2::Inf<T>())),    1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Nan  <T>(), nt2::Nan<T>())), boost::math::acos(cT(-nt2::Nan  <T>(), nt2::Nan<T>())),    1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Zero <T>(), nt2::Nan <T>())),boost::math::acos(cT(-nt2::Zero <T>(), nt2::Nan <T>())),   1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::One  <T>(), nt2::Nan <T>())),boost::math::acos(cT(-nt2::One  <T>(), nt2::Nan <T>())),   1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Inf  <T>(), nt2::Nan<T>())), boost::math::acos(cT(-nt2::Inf  <T>(), nt2::Nan<T>())),    1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::One  <T>(), nt2::Inf <T>())),boost::math::acos(cT(-nt2::One  <T>(), nt2::Inf <T>())),   1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Inf  <T>(), nt2::One <T>())),boost::math::acos(cT(-nt2::Inf  <T>(), nt2::One <T>())),   1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Inf  <T>(), nt2::Inf<T>())), boost::math::acos(cT(-nt2::Inf  <T>(), nt2::Inf<T>())),    1.0);
#endif
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Zero<T>(),  nt2::Zero<T>())), cT(nt2::Pio_2<T>(), nt2::Zero<T>()), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::One  <T>(), nt2::One <T>())),   cT(0.904556894302381, -1.061275061905036), 2);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::One  <T>(), nt2::Mone <T>())),  cT(0.904556894302381,  1.061275061905036), 2);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Mone  <T>(), nt2::One <T>())),  cT(2.237035759287412, -1.061275061905036), 2);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Mone  <T>(), nt2::Mone <T>())), cT(2.237035759287412,  1.061275061905036), 2);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(0.5, -0.5)),  boost::math::acos(cT(0.5, -0.5)), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(1, 1)),  boost::math::acos(cT(1, 1)), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(1, 10)),  boost::math::acos(cT(1, 10)), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(10, 10)),  boost::math::acos(cT(10, 10)), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(10, 1)),  boost::math::acos(cT(10, 1)), 1.0);
}
