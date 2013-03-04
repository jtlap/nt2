//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 complex.arithmetic toolbox - minusone/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////

#include <nt2/toolbox/arithmetic/include/functions/minusone.hpp>
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
#include <nt2/include/constants/two.hpp>
#include <nt2/toolbox/constant/common.hpp>


NT2_TEST_CASE_TPL ( minusone_real__1_0,  BOOST_SIMD_REAL_TYPES)
{

  using nt2::minusone;
  using nt2::tag::minusone_;
  typedef typename std::complex<T> cT;

  // specific values tests
  NT2_TEST_EQUAL(minusone(cT(nt2::Inf<T>(), nt2::Inf<T>())) ,cT( nt2::Inf<T>(), nt2::Inf<T>()));
  NT2_TEST_EQUAL(minusone(cT(nt2::Minf<T>(),nt2::Minf<T>())) , cT(nt2::Minf<T>(),nt2::Minf<T>()));
  NT2_TEST_EQUAL(minusone(cT(nt2::Mone<T>(),nt2::Mone<T>())), cT(-nt2::Two<T>(),nt2::Mone<T>()));
  NT2_TEST_EQUAL(minusone(cT(nt2::Nan<T>(), nt2::Nan<T>())) , cT(nt2::Nan<T>(),nt2::Nan<T>()));
  NT2_TEST_EQUAL(minusone(cT(nt2::One<T>(), nt2::One<T>())) , cT(nt2::Zero<T>(),nt2::One<T>()));
  NT2_TEST_EQUAL(minusone(cT(nt2::Zero<T>(),nt2::Zero<T>())), cT(nt2::Mone<T>(),nt2::Zero<T>()));

  NT2_TEST_EQUAL(minusone(nt2::Inf<cT>()), nt2::Inf<cT>());
  NT2_TEST_EQUAL(minusone(nt2::Minf<cT>()), nt2::Minf<cT>());
  NT2_TEST_EQUAL(minusone(nt2::Mone<cT>()), -nt2::Two<cT>());
  NT2_TEST_EQUAL(minusone(nt2::Nan<cT>()), nt2::Nan<cT>());
  NT2_TEST_EQUAL(minusone(nt2::One<cT>()), nt2::Zero<cT>());
  NT2_TEST_EQUAL(minusone(nt2::Zero<cT>()), nt2::Mone<cT>());
} // end of test for floating_

