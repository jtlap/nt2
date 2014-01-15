//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/sincpi.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/mhalf.hpp>
#include <nt2/include/constants/mindenormal.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/pio_4.hpp>
#include <nt2/include/constants/quarter.hpp>
#include <nt2/include/constants/sqrt_2.hpp>
#include <nt2/include/constants/sqrt_2o_2.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/functions/simd/divides.hpp>

NT2_TEST_CASE_TPL ( sincpi_real,  NT2_SIMD_REAL_TYPES)
{
  using nt2::sincpi;
  using nt2::tag::sincpi_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  typedef typename nt2::meta::call<sincpi_(vT)>::type r_t;
  typedef vT wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);


  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(sincpi(nt2::Inf<vT>()), nt2::Zero<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(sincpi(nt2::Minf<vT>()), nt2::Zero<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(sincpi(nt2::Nan<vT>()), nt2::Nan<vT>(), 0.5);
#endif
  NT2_TEST_ULP_EQUAL(sincpi(-nt2::Quarter<vT>()), nt2::Sqrt_2o_2<vT>()/nt2::Pio_4<vT>(), 1);
  NT2_TEST_ULP_EQUAL(sincpi(nt2::Half<vT>()), nt2::Two<vT>()/nt2::Pi<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(sincpi(nt2::Mhalf<vT>()), nt2::Two<vT>()/nt2::Pi<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(sincpi(nt2::One<vT>()), nt2::Zero<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(sincpi(nt2::Quarter<vT>()), nt2::Sqrt_2o_2<vT>()/nt2::Pio_4<vT>(), 1);
  NT2_TEST_ULP_EQUAL(sincpi(nt2::Eps<vT>()), nt2::One<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(sincpi(nt2::Mindenormal<vT>()), nt2::One<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(sincpi(nt2::Zero<vT>()), nt2::One<vT>(), 0.5);
}
