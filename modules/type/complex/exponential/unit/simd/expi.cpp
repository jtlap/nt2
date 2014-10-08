//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/expi.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/i.hpp>
#include <nt2/include/functions/mul_i.hpp>
#include <nt2/include/functions/exp.hpp>

NT2_TEST_CASE_TPL ( expi_real,  NT2_SIMD_REAL_TYPES)
{
  using nt2::expi;
  using nt2::tag::expi_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native<cT,ext_t>                vcT;
  NT2_TEST_TYPE_IS( typename nt2::meta::call<expi_(vcT)>::type, vcT );

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(nt2::expi(nt2::Inf<vcT>())   , nt2::exp(nt2::mul_i(nt2::Inf<vcT>()))  , 1);
  NT2_TEST_ULP_EQUAL(nt2::expi(nt2::Minf<vcT>())  , nt2::exp(nt2::mul_i(nt2::Minf<vcT>()) ), 1);
  NT2_TEST_ULP_EQUAL(nt2::expi(nt2::Nan<vcT>())   , nt2::exp(nt2::mul_i(nt2::Nan<vcT>())  ), 1);
  NT2_TEST_ULP_EQUAL(nt2::expi(nt2::Inf<vT>())    , nt2::exp(nt2::mul_i(nt2::Inf<vcT>()))  , 1);
  NT2_TEST_ULP_EQUAL(nt2::expi((nt2::Minf<vT>())) , nt2::exp(nt2::mul_i(nt2::Minf<vcT>()) ), 1);
  NT2_TEST_ULP_EQUAL(nt2::expi((nt2::Nan<vT>()))  , nt2::exp(nt2::mul_i(nt2::Nan<vcT>())  ), 1);
  NT2_TEST_ULP_EQUAL(nt2::expi(nt2::mul_i(nt2::Inf<vT>()))  , nt2::Zero<vcT>()  , 1);
  NT2_TEST_ULP_EQUAL(nt2::expi(nt2::mul_i(nt2::Minf<vT>())) , nt2::Inf<vcT>() , 1);
  NT2_TEST_ULP_EQUAL(nt2::expi(nt2::mul_i(nt2::Nan<vT>()))  , nt2::Nan<vcT>(), 1);
#endif
  NT2_TEST_ULP_EQUAL(nt2::expi(nt2::Mone<vcT>()) , nt2::exp(nt2::mul_i(vcT(nt2::Mone<vT>())) ), 1);
  NT2_TEST_ULP_EQUAL(nt2::expi(nt2::One<vcT>())  , nt2::exp(nt2::mul_i(vcT(nt2::One<vT>()))  ), 1);
  NT2_TEST_ULP_EQUAL(nt2::expi(nt2::Zero<vcT>()) , nt2::exp(nt2::mul_i(vcT(nt2::Zero<vT>())) ), 1);
  NT2_TEST_ULP_EQUAL(nt2::expi(nt2::Pi<vT>())    , nt2::exp(nt2::mul_i(nt2::Pi<vcT>())), 1);
  NT2_TEST_ULP_EQUAL(nt2::expi(nt2::Mone<vT>())  , nt2::exp(nt2::mul_i(vcT(nt2::Mone<vT>())) ), 1);
  NT2_TEST_ULP_EQUAL(nt2::expi(nt2::One<vT>())   , nt2::exp(nt2::mul_i(vcT(nt2::One<vT>()))  ), 1);
  NT2_TEST_ULP_EQUAL(nt2::expi(nt2::Zero<vT>())  , nt2::exp(nt2::mul_i(vcT(nt2::Zero<vT>())) ), 1);
  NT2_TEST_ULP_EQUAL(nt2::expi(nt2::Pi<vT>())    , nt2::exp(nt2::mul_i(vcT(nt2::Pi<vT>()))), 1);
  NT2_TEST_ULP_EQUAL(nt2::expi(nt2::mul_i(nt2::Mone<vT>())) , nt2::exp( nt2::One<vcT>()) , 1);
  NT2_TEST_ULP_EQUAL(nt2::expi(nt2::mul_i(nt2::One<vT>()))  , nt2::exp( nt2::Mone<vcT>()) , 1);
  NT2_TEST_ULP_EQUAL(nt2::expi(nt2::mul_i(nt2::Zero<vT>())) , nt2::exp( nt2::Zero<vcT>()), 1);
  NT2_TEST_ULP_EQUAL(nt2::expi(nt2::mul_i(nt2::Pi<vT>()))   , nt2::exp( -nt2::Pi<vcT>()), 1);
}
