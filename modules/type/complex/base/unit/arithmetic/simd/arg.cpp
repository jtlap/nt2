//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/arg.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/mtwo.hpp>
#include <nt2/include/constants/mzero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( arg_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::arg;
  using nt2::tag::arg_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native<cT,ext_t>                vcT;
  typedef typename nt2::dry<T>             dT;
  typedef native<dT,ext_t>                vdT;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(nt2::arg(vcT(nt2::Inf<vT>(), nt2::Zero<vT>())), nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::arg(vcT(nt2::Minf<vT>(), nt2::Zero<vT>())),nt2::Pi<vT>());
  NT2_TEST_EQUAL(nt2::arg(vcT(nt2::Nan<vT>(), nt2::Zero<vT>())), nt2::Nan<vT>());
  NT2_TEST_EQUAL(nt2::arg(vdT(nt2::Inf<vdT>()))  , nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::arg(vdT(nt2::Minf<vdT>())) , nt2::Pi<vT>());
  NT2_TEST_EQUAL(nt2::arg(vdT(nt2::Nan<vdT>()))  , nt2::Nan<vT>());
#endif
  NT2_TEST_EQUAL(nt2::arg(vcT(nt2::One<vT>(), nt2::Zero<vT>())), nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::arg(vcT(nt2::Zero<vT>(), nt2::Zero<vT>())),nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::arg(vcT(nt2::Zero<vT>(), nt2::One<vT>())),  nt2::Pio_2<vT>());
  NT2_TEST_EQUAL(nt2::arg(vcT(nt2::One<vT>(), nt2::Zero<vT>())),  nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::arg(vcT(nt2::Two<vT>(), nt2::Two<vT>())),   nt2::Pio_2<vT>()/nt2::Two<vT>());
  NT2_TEST_EQUAL(nt2::arg(vcT(nt2::Two<vT>(),nt2::Mtwo<vT>())),  -nt2::Pio_2<vT>()/nt2::Two<vT>());
  NT2_TEST_EQUAL(nt2::arg(vdT(nt2::One<vdT>()))  , nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::arg(vdT(nt2::Zero<vdT>())) , nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::arg(vdT(nt2::Two<vdT>()))  , nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::arg(vdT(nt2::Mone<vdT>())) ,nt2::Pi<vT>());
  NT2_TEST_EQUAL(nt2::arg(vdT(nt2::Mzero<vdT>())),nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::arg(vdT(nt2::Mtwo<vdT>())) ,nt2::Pi<vT>());
}
