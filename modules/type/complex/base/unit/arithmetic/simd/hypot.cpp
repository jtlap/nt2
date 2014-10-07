//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/hypot.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/sqrt_2.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>

NT2_TEST_CASE_TPL ( hypot_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::hypot;
  using nt2::tag::hypot_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native<cT,ext_t>                vcT;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(hypot(nt2::Inf<vcT>(), nt2::Inf<vcT>()), (nt2::Inf<vcT>()));
#endif
  NT2_TEST_EQUAL(hypot(nt2::One<vcT>(), nt2::Zero<vcT>()), nt2::One<vcT>());
  NT2_TEST_EQUAL(hypot(nt2::Zero<vcT>(), nt2::Zero<vcT>()),nt2::Zero<vcT>());
  NT2_TEST_ULP_EQUAL(hypot(nt2::splat<vcT>(cT(0, 1)), nt2::splat<vcT>(cT(1, 0))),
                     nt2::Sqrt_2<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(hypot(nt2::splat<vcT>(cT(1, 0)), nt2::splat<vcT>(cT(1, 0))),
                     nt2::Sqrt_2<vT>(), 0.5);
}
