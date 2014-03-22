//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/euler/include/functions/digamma.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/math/special_functions/digamma.hpp>

#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/mzero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( digamma_real,  NT2_SIMD_REAL_TYPES)
{
  using nt2::digamma;
  using nt2::tag::digamma_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;


  // specific values tests
  NT2_TEST_ULP_EQUAL(digamma(nt2::Zero<vT>()), nt2::Inf<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(digamma(nt2::Mzero<vT>()), nt2::Minf<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(digamma(nt2::One<vT>()), nt2::splat<vT>(-0.57721566490153286555), 0.5);
  NT2_TEST_ULP_EQUAL(digamma(nt2::splat<vT>(1.4669020846486091614)),nt2::splat<vT>(boost::math::digamma(double(T(1.4669020846486091614)))), 0.5);
  NT2_TEST_ULP_EQUAL(digamma(nt2::splat<vT>(1.461632133e+00)),      nt2::splat<vT>(boost::math::digamma(double(T(1.461632133e+00)))), 7.5);
  NT2_TEST_ULP_EQUAL(digamma(nt2::splat<vT>(-3.5)),                 nt2::splat<vT>(boost::math::digamma(double(T(-3.5)))), 0.5);
  NT2_TEST_ULP_EQUAL(digamma(nt2::splat<vT>(-3.51)),                nt2::splat<vT>(boost::math::digamma(double(T(-3.51)))), 0.5);
  NT2_TEST_ULP_EQUAL(digamma(nt2::splat<vT>(-3.51)),                nt2::splat<vT>(boost::math::digamma(       T(-3.51))) , 0.5);
  NT2_TEST_ULP_EQUAL(digamma(nt2::splat<vT>(-6)),  nt2::Nan<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(digamma(nt2::splat<vT>(6)) ,   nt2::splat<vT>(1.706117668431801e+00), 1);

}
