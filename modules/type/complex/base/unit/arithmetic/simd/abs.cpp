//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/abs.hpp>

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

#include <nt2/include/constants/five.hpp>
#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/sqrt_2.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( abs_cplx,   BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::abs;
  using nt2::tag::abs_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native<cT,ext_t>                vcT;
  typedef typename nt2::dry<T>             dT;
  typedef native<dT,ext_t>                vdT;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(nt2::abs(vcT(nt2::Inf<vT>(),nt2::Nan<vT>())), nt2::Inf<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::abs(vcT(nt2::Inf<vT>(), nt2::Zero<vT>())), nt2::Inf<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::abs(vcT(nt2::Minf<vT>(), nt2::Zero<vT>())), nt2::Inf<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::abs(vcT(nt2::Nan<vT>(), nt2::Zero<vT>())), nt2::Nan<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::abs(vdT(nt2::Inf<vdT>())   ), nt2::Inf<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::abs(vdT(nt2::Inf<vdT>())   ), nt2::Inf<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::abs(vdT(nt2::Minf<vdT>())  ), nt2::Inf<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::abs(vdT(nt2::Nan<vdT>())   ), nt2::Nan<vT>(), 0.5);
#endif
  NT2_TEST_ULP_EQUAL(nt2::abs(vcT(nt2::Mone<vT>(), nt2::Zero<vT>())), nt2::One<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::abs(vcT(nt2::One<vT>(), nt2::Zero<vT>())), nt2::One<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::abs(vcT(nt2::Valmax<vT>(), nt2::Zero<vT>())), nt2::Valmax<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::abs(vcT(nt2::Valmin<vT>(), nt2::Zero<vT>())), nt2::Valmax<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::abs(vcT(nt2::Zero<vT>(), nt2::Zero<vT>())), nt2::Zero<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::abs(vcT(nt2::One<vT>(), nt2::One<vT>())), nt2::Sqrt_2<vT>(), 1);
  NT2_TEST_ULP_EQUAL(nt2::abs(vcT(nt2::Four<vT>(), nt2::Three<vT>())), nt2::Five<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::abs(vdT(nt2::Mone<vdT>())  ), nt2::One<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::abs(vdT(nt2::One<vdT>())   ), nt2::One<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::abs(vdT(nt2::Valmax<vdT>())), nt2::Valmax<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::abs(vdT(nt2::Valmin<vdT>())), nt2::Valmax<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::abs(vdT(nt2::Zero<vdT>())  ), nt2::Zero<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::abs(vdT(nt2::One<vdT>())   ), nt2::One<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::abs(vdT(nt2::Four<vdT>())  ), nt2::Four<vT>(), 0.5);
}
