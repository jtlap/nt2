//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.arithmetic toolbox - sqrt/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 30/11/2010
///
#include <nt2/include/functions/sqrt.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/include/functions/extract.hpp>
#include <nt2/include/functions/unary_minus.hpp>
#include <nt2/include/constants/cnan.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/sqrt_2o_2.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL ( abs_cplx__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef std::complex<T>                              cT;
  typedef native<T ,ext_t>                             vT;
  typedef native<cT ,ext_t>                           vcT;
  typedef typename nt2::meta::as_dry<T>::type          dT;
  typedef native<dT ,ext_t>                           vdT;


  {
    typedef vcT r_t;
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::Inf<vcT>())[0], cT(nt2::Inf<cT>()),0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::Minf<vcT>())[0], cT(0, nt2::Inf<T>()),0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::Mone<vcT>())[0], cT(0, 1),0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::Nan<vcT>())[0], cT(nt2::Cnan<cT>()),0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::One<vcT>())[0], cT(nt2::One<cT>()),0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::Zero<vcT>())[0], cT(nt2::Zero<cT>()),0);
  }
   {
    typedef vcT r_t;
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::Inf<vdT>())[0], nt2::Inf<cT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::Minf<vdT>())[0], cT(nt2::Zero<T>(), nt2::Inf<T>()),0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::Mone<vdT>())[0], cT(nt2::Zero<T>(), nt2::One<T>()),0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::Nan<vdT>())[0], nt2::Nan<cT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::One<vdT>())[0], nt2::One<cT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::Zero<vdT>())[0], nt2::Zero<cT>(),0);
  }
} // end of test for floating_


