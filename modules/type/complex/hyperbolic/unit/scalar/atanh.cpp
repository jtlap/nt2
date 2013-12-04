//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/atanh.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/i.hpp>
#include <boost/math/complex/atanh.hpp>


NT2_TEST_CASE_TPL ( atanh_real, (double))
{
  using nt2::atanh;
  using nt2::tag::atanh_;
  typedef typename std::complex<T> cT;
  typedef typename nt2::meta::call<atanh_(cT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, cT);

  // specific values tests
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::One  <T>(), nt2::Inf <T>())), boost::math::atanh(cT(1.0, nt2::Inf <T>())), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::Inf  <T>(), nt2::One <T>())), boost::math::atanh(cT(nt2::Inf <T>(), 1)), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::Nan  <T>(), nt2::Inf<T>())),  boost::math::atanh(cT(nt2::Nan  <T>(), nt2::Inf<T>())), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::Nan <T>(),  nt2::Zero<T>())), boost::math::atanh(cT(nt2::Nan <T>(),  nt2::Zero<T>())), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::Inf  <T>(), nt2::Nan<T>())),  boost::math::atanh(cT(nt2::Inf  <T>(), nt2::Nan<T>())) , 0.75);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::Nan  <T>(), nt2::One<T>())),  boost::math::atanh(cT(nt2::Nan  <T>(), nt2::One<T>())), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::Nan  <T>(), nt2::Nan<T>())),  boost::math::atanh(cT(nt2::Nan  <T>(), nt2::Nan<T>())), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::Zero <T>(), nt2::Nan <T>())), boost::math::atanh(cT(nt2::Zero  <T>(), nt2::Nan<T>())), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::One  <T>(), nt2::Nan <T>())), boost::math::atanh(cT(nt2::One  <T>(), nt2::Nan <T>())), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::Inf  <T>(), nt2::Inf<T>())),  boost::math::atanh(cT(nt2::Inf  <T>(), nt2::Inf<T>())), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::One  <T>(), -nt2::Inf <T>())), boost::math::atanh(cT(1.0, -nt2::Inf <T>())), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::Inf  <T>(), -nt2::One <T>())), boost::math::atanh(cT(nt2::Inf <T>(), -1)), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::Nan  <T>(), -nt2::Inf<T>())),  boost::math::atanh(cT(nt2::Nan  <T>(), -nt2::Inf<T>())), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::Nan <T>(),  -nt2::Zero<T>())), boost::math::atanh(cT(nt2::Nan <T>(),  -nt2::Zero<T>())), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::Inf  <T>(), -nt2::Nan<T>())),  boost::math::atanh(cT(nt2::Inf  <T>(), -nt2::Nan<T>())) , 0.75);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::Nan  <T>(), -nt2::One<T>())),  boost::math::atanh(cT(nt2::Nan  <T>(), -nt2::One<T>())), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::Nan  <T>(), -nt2::Nan<T>())),  boost::math::atanh(cT(nt2::Nan  <T>(), -nt2::Nan<T>())), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::Zero <T>(), -nt2::Nan <T>())), boost::math::atanh(cT(nt2::Zero  <T>(), -nt2::Nan<T>())), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::One  <T>(), -nt2::Nan <T>())), boost::math::atanh(cT(nt2::One  <T>(), -nt2::Nan <T>())), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::Inf  <T>(), -nt2::Inf<T>())),  boost::math::atanh(cT(nt2::Inf  <T>(), -nt2::Inf<T>())), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(0.0, nt2::Minf<T>())),  boost::math::atanh(cT(0.0, nt2::Minf<T>())), 0);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::Nan<T>(), nt2::Minf<T>())), boost::math::atanh(cT(nt2::Nan<T>(), nt2::Minf<T>())), 0);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::Zero <T>(),  nt2::Zero<T>())), cT(nt2::Zero <T>(), nt2::Zero<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::One  <T>(), nt2::One <T>())),   cT(0.402359478108525,  1.017221967897851), 2);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::One  <T>(), nt2::Mone <T>())),  cT(0.402359478108525,  -1.017221967897851), 2);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::Mone  <T>(), nt2::One <T>())),  cT(-0.402359478108525,  1.017221967897851), 2);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::Mone  <T>(), nt2::Mone <T>())), cT(-0.402359478108525,  -1.017221967897851), 2);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::One  <T>(), 100)),   boost::math::atanh(cT(1.0, 100.0)), 2);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::One  <T>(), 100)),  cT(0.0000999800053317338451627251604797, 1.56079765980832135270094509319), 2);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(nt2::One  <T>(), 2)),     boost::math::atanh(cT(1.0, 2.0)), 2);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(2, 1)),                   boost::math::atanh(cT(2.0, 1.0)), 2);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(20, -71)),                   boost::math::atanh(cT(20, -71)), 2);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(1.0e160, 1.0e160)),                   boost::math::atanh(cT(1.0e160, 1.0e160)), 2);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(1.0e300, 1.0e160)),                   boost::math::atanh(cT(1.0e300, 1.0e160)), 2);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(1.0e160, 1.0e300)),                   boost::math::atanh(cT(1.0e160, 1.0e300)), 2);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(2, 1.0e300)),                   boost::math::atanh(cT(2, 1.0e300)), 2);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(1.0e160, 2)),                   boost::math::atanh(cT(1.0e160, 2)), 2);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(1.0e-160, 1.0e-160)),                   boost::math::atanh(cT(1.0e-160, 1.0e-160)), 2);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(1.0e-300, 1.0e-160)),                   boost::math::atanh(cT(1.0e-300, 1.0e-160)), 2);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(1.0e-160, 1.0e-300)),                   boost::math::atanh(cT(1.0e-160, 1.0e-300)), 2);   std::cout << nt2::atanh(cT(1.0e-160, 1.0e-300)) << " --- " << boost::math::atanh(cT(1.0e-160, 1.0e-300)) << std::endl;
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(1.0, 1.0e160)),                   boost::math::atanh(cT(1.0, 1.0e160)), 2);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(1.0e-160, 1.0e160)),                   boost::math::atanh(cT(1.0e-160, 1.0e160)), 2);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(1.0, 1.0e-160)),                   cT(184.55338102980363146,0.785398163397448279), 2);
  NT2_TEST_ULP_EQUAL(nt2::atanh(cT(1.0e-160, 1.0e-160)),                   boost::math::atanh(cT(1.0e-160, 1.0e-160)), 2);
}
