//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/acos.hpp>
#include <nt2/exponential/constants.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <complex>
#include <boost/math/complex/acos.hpp>

NT2_TEST_CASE_TPL ( acos_real__1_0,  NT2_REAL_TYPES)
{
  using nt2::acos;
  using nt2::tag::acos_;
  typedef std::complex<T> cT;
  typedef typename nt2::meta::call<acos_(cT)>::type r_t;
  typedef typename nt2:: meta::as_complex<T>::type wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Zero<T>(),  nt2::Zero<T>())), cT(nt2::Pio_2<T>(), nt2::Zero<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Nan <T>(),  nt2::Zero<T>())), cT(nt2::Nan <T>(), nt2::Nan<T>()), 0.75);

  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Nan  <T>(), nt2::One<T>())),  cT(nt2::Nan <T>(), nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Nan  <T>(), nt2::Inf<T>())),  cT(nt2::Nan <T>(), -nt2::Inf<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Nan  <T>(), nt2::Nan<T>())),  cT(nt2::Nan <T>(), nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Zero <T>(), nt2::Nan <T>())), cT(nt2::Pio_2<T>(), nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::One  <T>(), nt2::Nan <T>())), cT(nt2::Nan<T>(),  nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Inf  <T>(), nt2::Nan<T>())),  cT(nt2::Nan <T>(), nt2::Minf<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::One  <T>(), nt2::Inf <T>())), cT(nt2::Pio_2<T>(), -nt2::Inf<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Inf  <T>(), nt2::One <T>())), cT(nt2::Zero<T>(), nt2::Minf <T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Inf  <T>(), nt2::Inf<T>())),  cT(nt2::Pi<T>()/nt2::Four<T>(), nt2::Minf <T>()), 0.75);

  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Nan  <T>(), nt2::One<T>())),  cT(nt2::Nan <T>(), nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Nan  <T>(), nt2::Inf<T>())),  cT(nt2::Nan <T>(), -nt2::Inf<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Nan  <T>(), nt2::Nan<T>())),  cT(nt2::Nan <T>(), nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Zero <T>(), nt2::Nan <T>())), cT(nt2::Pio_2<T>(), nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::One  <T>(), nt2::Nan <T>())), cT(nt2::Nan<T>(),  nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Inf  <T>(), nt2::Nan<T>())),  cT(nt2::Nan <T>(), nt2::Minf<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::One  <T>(), nt2::Inf <T>())), cT(nt2::Pio_2<T>(), nt2::Minf<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Inf  <T>(), nt2::One <T>())), cT(nt2::Pi<T>(), -nt2::Inf <T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Inf  <T>(), nt2::Inf<T>())),  cT(nt2::Three<T>()*nt2::Pi<T>()/nt2::Four<T>(), nt2::Minf <T>()), 0.75);

  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Nan  <T>(), nt2::One<T>())), boost::math::acos(cT(nt2::Nan  <T>(), nt2::One<T>())),  0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Nan  <T>(), nt2::Inf<T>())), boost::math::acos(cT(nt2::Nan  <T>(), nt2::Inf<T>())),  0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Nan  <T>(), nt2::Nan<T>())), boost::math::acos(cT(nt2::Nan  <T>(), nt2::Nan<T>())),  0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Zero <T>(), nt2::Nan <T>())),boost::math::acos(cT(nt2::Zero <T>(), nt2::Nan <T>())), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::One  <T>(), nt2::Nan <T>())),boost::math::acos(cT(nt2::One  <T>(), nt2::Nan <T>())), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Inf  <T>(), nt2::Nan<T>())), boost::math::acos(cT(nt2::Inf  <T>(), nt2::Nan<T>())),  0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::One  <T>(), nt2::Inf <T>())),boost::math::acos(cT(nt2::One  <T>(), nt2::Inf <T>())), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Inf  <T>(), nt2::One <T>())),boost::math::acos(cT(nt2::Inf  <T>(), nt2::One <T>())), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Inf  <T>(), nt2::Inf<T>())), boost::math::acos(cT(nt2::Inf  <T>(), nt2::Inf<T>())),  0.75);

  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Nan  <T>(), nt2::One<T>())), boost::math::acos(cT(-nt2::Nan  <T>(), nt2::One<T>())),    0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Nan  <T>(), nt2::Inf<T>())), boost::math::acos(cT(-nt2::Nan  <T>(), nt2::Inf<T>())),    0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Nan  <T>(), nt2::Nan<T>())), boost::math::acos(cT(-nt2::Nan  <T>(), nt2::Nan<T>())),    0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Zero <T>(), nt2::Nan <T>())),boost::math::acos(cT(-nt2::Zero <T>(), nt2::Nan <T>())),   0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::One  <T>(), nt2::Nan <T>())),boost::math::acos(cT(-nt2::One  <T>(), nt2::Nan <T>())),   0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Inf  <T>(), nt2::Nan<T>())), boost::math::acos(cT(-nt2::Inf  <T>(), nt2::Nan<T>())),    0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::One  <T>(), nt2::Inf <T>())),boost::math::acos(cT(-nt2::One  <T>(), nt2::Inf <T>())),   0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Inf  <T>(), nt2::One <T>())),boost::math::acos(cT(-nt2::Inf  <T>(), nt2::One <T>())),   0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(-nt2::Inf  <T>(), nt2::Inf<T>())), boost::math::acos(cT(-nt2::Inf  <T>(), nt2::Inf<T>())),    0.75);

  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::One  <T>(), nt2::One <T>())),   cT(0.904556894302381, -1.061275061905036), 2);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::One  <T>(), nt2::Mone <T>())),  cT(0.904556894302381,  1.061275061905036), 2);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Mone  <T>(), nt2::One <T>())),  cT(2.237035759287412, -1.061275061905036), 2);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(nt2::Mone  <T>(), nt2::Mone <T>())), cT(2.237035759287412,  1.061275061905036), 2);

  NT2_TEST_ULP_EQUAL(nt2::acos(cT(0.5, -0.5)),  boost::math::acos(cT(0.5, -0.5)), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(1, 1)),  boost::math::acos(cT(1, 1)), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(1, 10)),  boost::math::acos(cT(1, 10)), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(10, 10)),  boost::math::acos(cT(10, 10)), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acos(cT(10, 1)),  boost::math::acos(cT(10, 1)), 0.75);
} // end of test for floating_
