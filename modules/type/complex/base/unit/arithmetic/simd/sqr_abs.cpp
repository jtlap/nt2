//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/sqr_abs.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/five.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( sqr_abs_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::sqr_abs;
  using nt2::tag::sqr_abs_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native<cT,ext_t>                vcT;
  typedef typename nt2::dry<T>             dT;
  typedef native<dT,ext_t>                vcT;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(sqr_abs(nt2::Inf<vcT>()), nt2::Inf<vT>());
  NT2_TEST_EQUAL(sqr_abs(nt2::Minf<vcT>()), nt2::Inf<vT>());
  NT2_TEST_EQUAL(sqr_abs(nt2::Nan<vcT>()), nt2::Nan<vT>());
  NT2_TEST_EQUAL(sqr_abs(nt2::Valmax<vcT>()), nt2::Inf<vT>());
  NT2_TEST_EQUAL(sqr_abs(nt2::Valmin<vcT>()), nt2::Inf<vT>());
#endif
  NT2_TEST_EQUAL(sqr_abs(nt2::Mone<vcT>()), nt2::One<vT>());
  NT2_TEST_EQUAL(sqr_abs(nt2::One<vcT>()), nt2::One<vT>());
  NT2_TEST_EQUAL(sqr_abs(nt2::Zero<vcT>()), nt2::Zero<vT>());
  NT2_TEST_EQUAL(sqr_abs(vcT(nt2::One<vT>(),nt2::One<vT>()), nt2::TwoT>());
  NT2_TEST_EQUAL(sqr_abs(vcT(nt2::Three<vT>(),nt2::Four<vT>()) ), nt2::sqr(nt2::Five<vcT>()));
  NT2_TEST_EQUAL(sqr_abs(nt2::Mone<vdT>()), nt2::One<vT>());
  NT2_TEST_EQUAL(sqr_abs(nt2::One<vdT>()), nt2::One<vT>());
  NT2_TEST_EQUAL(sqr_abs(nt2::Zero<vdT>()), nt2::Zero<vT>());
}
