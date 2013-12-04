//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/atan.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <boost/math/complex/atan.hpp>
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
#include <boost/math/complex/atan.hpp>

NT2_TEST_CASE_TPL ( atan_real,  NT2_REAL_TYPES)
{
  using nt2::atan;
  using nt2::tag::atan_;
  typedef typename std::complex<T> cT;
  typedef typename nt2::meta::call<atan_(cT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, cT);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
 NT2_TEST_ULP_EQUAL(nt2::atan(cT(nt2::Nan <T>(),  nt2::Zero<T>())) , boost::math::atan(cT(nt2::Nan <T>(),  nt2::Zero<T>())), 0.75);
 NT2_TEST_ULP_EQUAL(nt2::atan(cT(nt2::Nan  <T>(), nt2::One<T>()))  , boost::math::atan(cT(nt2::Nan  <T>(), nt2::One<T>())), 0.75);
 NT2_TEST_ULP_EQUAL(nt2::atan(cT(nt2::Nan  <T>(), nt2::Inf<T>()))  , boost::math::atan(cT(nt2::Nan  <T>(), nt2::Inf<T>())), 0.75);
 NT2_TEST_ULP_EQUAL(nt2::atan(cT(nt2::Nan  <T>(), nt2::Nan<T>()))  , boost::math::atan(cT(nt2::Nan  <T>(), nt2::Nan<T>())) , 0.75);
 NT2_TEST_ULP_EQUAL(nt2::atan(cT(nt2::Zero <T>(), nt2::Nan <T>())) , boost::math::atan(cT(nt2::Zero <T>(), nt2::Nan <T>())), 0.75);
 NT2_TEST_ULP_EQUAL(nt2::atan(cT(nt2::One  <T>(), nt2::Nan <T>())) , boost::math::atan(cT(nt2::One  <T>(), nt2::Nan <T>())), 0.75);
 NT2_TEST_ULP_EQUAL(nt2::atan(cT(nt2::Inf  <T>(), nt2::Nan<T>()))  , boost::math::atan(cT(nt2::Inf  <T>(), nt2::Nan<T>())) , 0.75);
 NT2_TEST_ULP_EQUAL(nt2::atan(cT(nt2::One  <T>(), nt2::Inf <T>())) , boost::math::atan(cT(nt2::One  <T>(), nt2::Inf <T>())), 0.75);
 NT2_TEST_ULP_EQUAL(nt2::atan(cT(nt2::Inf  <T>(), nt2::One <T>())) , boost::math::atan(cT(nt2::Inf  <T>(), nt2::One <T>())), 0.75);
 NT2_TEST_ULP_EQUAL(nt2::atan(cT(nt2::Inf  <T>(), nt2::Inf<T>()))  , boost::math::atan(cT(nt2::Inf  <T>(), nt2::Inf<T>())) , 0.75);
 NT2_TEST_ULP_EQUAL(nt2::atan(cT(-nt2::Nan  <T>(), nt2::One<T>())) , boost::math::atan(cT(-nt2::Nan  <T>(), nt2::One<T>())), 0.75);
 NT2_TEST_ULP_EQUAL(nt2::atan(cT(-nt2::Nan  <T>(), nt2::Inf<T>())) , boost::math::atan(cT(-nt2::Nan  <T>(), nt2::Inf<T>())), 0.75);
 NT2_TEST_ULP_EQUAL(nt2::atan(cT(-nt2::Nan  <T>(), nt2::Nan<T>())) , boost::math::atan(cT(-nt2::Nan  <T>(), nt2::Nan<T>())), 0.75);
 NT2_TEST_ULP_EQUAL(nt2::atan(cT(-nt2::Zero <T>(), nt2::Nan <T>())), boost::math::atan(cT(-nt2::Zero <T>(), nt2::Nan <T>())), 0.75);
 NT2_TEST_ULP_EQUAL(nt2::atan(cT(-nt2::One  <T>(), nt2::Nan <T>())), boost::math::atan(cT(-nt2::One  <T>(), nt2::Nan <T>())), 0.75);
 NT2_TEST_ULP_EQUAL(nt2::atan(cT(-nt2::Inf  <T>(), nt2::Nan<T>())) , boost::math::atan(cT(-nt2::Inf  <T>(), nt2::Nan<T>())), 0.75);
 NT2_TEST_ULP_EQUAL(nt2::atan(cT(-nt2::One  <T>(), nt2::Inf <T>())), boost::math::atan(cT(-nt2::One  <T>(), nt2::Inf <T>())), 0.75);
 NT2_TEST_ULP_EQUAL(nt2::atan(cT(-nt2::Inf  <T>(), nt2::One <T>())), boost::math::atan(cT(-nt2::Inf  <T>(), nt2::One <T>())), 0.75);
 NT2_TEST_ULP_EQUAL(nt2::atan(cT(-nt2::Inf  <T>(), nt2::Inf<T>())) , boost::math::atan(cT(-nt2::Inf  <T>(), nt2::Inf<T>())), 0.75);
#endif
  NT2_TEST_ULP_EQUAL(nt2::atan(cT(nt2::Zero<T>(),  nt2::Zero<T>())), nt2::Zero<cT>(), 0);
  NT2_TEST_ULP_EQUAL(nt2::atan(cT(nt2::One  <T>(), nt2::One <T>())),   cT(1.0172219678978513535,0.40235947810852507045), 2);
  NT2_TEST_ULP_EQUAL(nt2::atan(cT(nt2::One  <T>(), nt2::Mone <T>())),  cT(1.0172219678978513535,-0.40235947810852507045), 2);
  NT2_TEST_ULP_EQUAL(nt2::atan(cT(nt2::Mone  <T>(), nt2::One <T>())),  cT(-1.0172219678978513535,0.40235947810852507045), 2);
  NT2_TEST_ULP_EQUAL(nt2::atan(cT(nt2::Mone  <T>(), nt2::Mone <T>())), cT(-1.0172219678978513535,-0.40235947810852507045), 2);
  NT2_TEST_ULP_EQUAL(nt2::atan(cT(1, 1)),  boost::math::atan(cT(1, 1)), 1);
  NT2_TEST_ULP_EQUAL(nt2::atan(cT(1, 10)),  boost::math::atan(cT(1, 10)), 1);
  NT2_TEST_ULP_EQUAL(nt2::atan(cT(10, 10)),  boost::math::atan(cT(10, 10)), 1);
  NT2_TEST_ULP_EQUAL(nt2::atan(cT(10, 1)),  boost::math::atan(cT(10, 1)), 1);
  NT2_TEST_ULP_EQUAL(nt2::atan(cT(0, 1)),  boost::math::atan(cT(0, 1)), 1);
  NT2_TEST_ULP_EQUAL(nt2::atan(cT(1, 0)),  boost::math::atan(cT(1, 0)), 1);
  NT2_TEST_ULP_EQUAL(nt2::atan(cT(0, 0)),  boost::math::atan(cT(0, 0)), 1);
}
