//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 complex.arithmetic toolbox - trunc/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////

#include <nt2/toolbox/arithmetic/include/functions/trunc.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/mhalf.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/toolbox/constant/common.hpp>


NT2_TEST_CASE_TPL ( trunc_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  using nt2::trunc;
  using nt2::tag::trunc_;

  typedef typename std::complex<T> cT;

  // specific values tests
  NT2_TEST_EQUAL(trunc(cT(T(-1.1))), cT(-1));
  NT2_TEST_EQUAL(trunc(cT(T(1.1))), cT(1));
  NT2_TEST_EQUAL(trunc(nt2::Inf<cT>()), nt2::Inf<cT>());
  NT2_TEST_EQUAL(trunc(nt2::Minf<cT>()), nt2::Minf<cT>());
  NT2_TEST_EQUAL(trunc(nt2::Mone<cT>()), nt2::Mone<cT>());
  NT2_TEST_EQUAL(trunc(nt2::Nan<cT>()), nt2::Nan<cT>());
  NT2_TEST_EQUAL(trunc(nt2::One<cT>()), nt2::One<cT>());
  NT2_TEST_EQUAL(trunc(nt2::Zero<cT>()), nt2::Zero<cT>());
} // end of test for floating_

