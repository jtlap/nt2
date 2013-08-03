//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/euler/include/functions/erf.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>
#include <nt2/include/functions/splat.hpp>

NT2_TEST_CASE_TPL ( erf_real__1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::erf;
  using nt2::tag::erf_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                vT;
  typedef typename nt2::meta::call<erf_(vT)>::type r_t;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(erf(nt2::Inf<vT>()), nt2::One<r_t>(), 10);
  NT2_TEST_ULP_EQUAL(erf(nt2::Nan<vT>()), nt2::Nan<r_t>(), 10);
#endif
  NT2_TEST_ULP_EQUAL(erf(nt2::Mzero<vT>()), nt2::Zero<r_t>(), 10);
  NT2_TEST_ULP_EQUAL(erf(nt2::One<vT>()), nt2::splat<vT>(0.842700792949715), 10);
  NT2_TEST_ULP_EQUAL(erf(nt2::Half<vT>()), nt2::splat<vT>(0.520499877813047), 10);
  NT2_TEST_ULP_EQUAL(erf(nt2::Two<vT>()), nt2::splat<vT>(0.995322265018953), 10);
  NT2_TEST_ULP_EQUAL(erf(nt2::Ten<vT>()),  nt2::One <r_t>(), 10);
  NT2_TEST_ULP_EQUAL(erf(nt2::Zero<vT>()), nt2::Zero<r_t>(), 10);
} // end of test for floating_
