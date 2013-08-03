//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 euler toolbox - stirling/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of euler components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 22/02/2011
///
#include <nt2/euler/include/functions/stirling.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>
#include <nt2/include/functions/splat.hpp>

NT2_TEST_CASE_TPL ( stirling_real__1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::stirling;
  using nt2::tag::stirling_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                vT;
  typedef typename nt2::meta::call<stirling_(vT)>::type r_t;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(stirling(nt2::Inf<vT>()),  stirling(nt2::Inf<vT>() ),  0.5);
  NT2_TEST_ULP_EQUAL(stirling(nt2::Minf<vT>()), stirling(nt2::Minf<vT>()), 0.5);
  NT2_TEST_ULP_EQUAL(stirling(nt2::Nan<vT>()),  stirling(nt2::Nan<vT>() ),  0.5);
#endif
  NT2_TEST_ULP_EQUAL(stirling(nt2::Mone<vT>()), stirling(nt2::Mone<vT>()), 0.5);
  NT2_TEST_ULP_EQUAL(stirling(nt2::One<vT>()),  stirling(nt2::One<vT>() ),  0.5);
  NT2_TEST_ULP_EQUAL(stirling(nt2::Zero<vT>()), stirling(nt2::Zero<vT>()), 0.5);
  // specific values tests
} // end of test for floating_
