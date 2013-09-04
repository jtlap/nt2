//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/simd/sinc.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/mindenormal.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/functor/meta/call.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( sinc_real,  NT2_SIMD_REAL_TYPES)
{
  using nt2::sinc;
  using nt2::tag::sinc_;
  using boost::simd::native;

  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        vT;

  NT2_TEST_TYPE_IS( typename nt2::meta::call<sinc_(vT)>::type, vT);

  // specific values tests
  NT2_TEST_ULP_EQUAL(sinc(-nt2::Pi<vT>()/nt2::splat<vT>(2)), T(2)/(nt2::Pi<vT>()), 0.5);
  NT2_TEST_ULP_EQUAL(sinc(-nt2::Pi<vT>()/nt2::splat<T>(4)), nt2::sin(nt2::Pi<vT>()/T(4))*T(4)/(nt2::Pi<vT>()), 1.0);
  NT2_TEST_ULP_EQUAL(sinc(nt2::Inf<vT>()), nt2::Zero<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(sinc(nt2::Minf<vT>()), nt2::Zero<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(sinc(nt2::Nan<vT>()), nt2::Nan<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(sinc(nt2::Pi<vT>()/nt2::splat<T>(2)),  T(2)/(nt2::Pi<vT>()), 0.5);
  NT2_TEST_ULP_EQUAL(sinc(nt2::Pi<vT>()/nt2::splat<T>(4)), nt2::sin(nt2::Pi<vT>()/T(4))*T(4)/(nt2::Pi<vT>()), 1.0);
  NT2_TEST_ULP_EQUAL(sinc(nt2::Eps<vT>()), nt2::One<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(sinc(nt2::Mindenormal<vT>()), nt2::One<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(sinc(nt2::Zero<vT>()), nt2::One<vT>(), 0.5);
}
