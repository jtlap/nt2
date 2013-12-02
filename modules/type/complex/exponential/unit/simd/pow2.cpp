//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/pow2.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/i.hpp>

NT2_TEST_CASE_TPL ( pow2_real,  NT2_REAL_TYPES)
{
  using nt2::pow2;
  using nt2::tag::pow2_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native<cT,ext_t>                vcT;
  typedef typename nt2::dry<T>             dT;
  typedef native<dT,ext_t>                vdT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<pow2_(vcT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, vcT);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(pow2(nt2::Inf<vcT>()), nt2::Inf<vcT>(), 0);
  NT2_TEST_EQUAL(pow2(nt2::Minf<vcT>()),    nt2::Zero<vcT>());
  NT2_TEST_EQUAL(pow2(nt2::Nan<vcT>()),     nt2::Nan<vcT>());
#endif
  NT2_TEST_EQUAL(pow2(nt2::Mone<vcT>()), nt2::Half<vcT>());
  NT2_TEST_EQUAL(pow2(nt2::One<vcT>()),  nt2::Two<vcT>());
  NT2_TEST_EQUAL(pow2(nt2::Zero<vcT>()), nt2::One<vcT>());
  NT2_TEST_EQUAL(pow2(vcT(nt2::One<vT>(), nt2::One<vT>()), iT(1)), nt2::Two<vdT>());
}
