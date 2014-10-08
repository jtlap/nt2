//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/rsqrt.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/cnan.hpp>

NT2_TEST_CASE_TPL ( abs_cplx,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::rsqrt;
  using nt2::tag::rsqrt_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<cT,ext_t>                vcT;
  typedef typename nt2::dry<T>             dT;
  typedef native<dT,ext_t>                vdT;

#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(nt2::rsqrt(nt2::Inf<vcT>()), nt2::Zero<vcT>(),0);
  NT2_TEST_ULP_EQUAL(nt2::rsqrt(nt2::Minf<vcT>()), nt2::Zero<vcT>(),0);
  NT2_TEST_ULP_EQUAL(nt2::rsqrt(nt2::Nan<vcT>()), nt2::splat<vcT>(nt2::Cnan<vcT>()),0);
  NT2_TEST_ULP_EQUAL(nt2::rsqrt(nt2::Inf<vdT>()), nt2::Zero<vcT>(),0);
  NT2_TEST_ULP_EQUAL(nt2::rsqrt(nt2::Minf<vdT>()),  nt2::Zero<vcT>(),0);
  NT2_TEST_ULP_EQUAL(nt2::rsqrt(nt2::Nan<vdT>()), nt2::Nan<vcT>(),0);
#endif
  NT2_TEST_ULP_EQUAL(nt2::rsqrt(nt2::Mone<vcT>()), nt2::splat<vcT>(cT(0, -1)),0);
  NT2_TEST_ULP_EQUAL(nt2::rsqrt(nt2::One<vcT>()), nt2::One<vcT>(),0);
  NT2_TEST_ULP_EQUAL(nt2::rsqrt(nt2::Zero<vcT>()), nt2::Inf<vcT>(),0);
  NT2_TEST_ULP_EQUAL(nt2::rsqrt(nt2::Mone<vdT>()), nt2::splat<vcT>(cT(nt2::Zero<T>(), nt2::Mone<T>())),0);
  NT2_TEST_ULP_EQUAL(nt2::rsqrt(nt2::One<vdT>()), nt2::One<vcT>(),0);
  NT2_TEST_ULP_EQUAL(nt2::rsqrt(nt2::Zero<vdT>()), nt2::Inf<vcT>(),0);
}

