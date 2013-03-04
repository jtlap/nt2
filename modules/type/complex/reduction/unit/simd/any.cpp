//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 reduction toolbox - any/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of reduction components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 24/02/2011
///
#include <nt2/toolbox/reduction/include/functions/any.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/simd/logical.hpp>
#include <nt2/sdk/functor/meta/call.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/true.hpp>
#include <nt2/include/constants/false.hpp>
#include <nt2/toolbox/constant/common.hpp>

NT2_TEST_CASE_TPL ( any_real__1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::any;
  using nt2::tag::any_;
  using boost::simd::native;
  using nt2::meta::cardinal_of;

  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<std::complex<T> ,ext_t>            vcT;
  typedef typename nt2::meta::call<any_(vcT)>::type r_t;
  typedef typename nt2::meta::call<any_(T)>::type   sr_t;

  // specific values tests
  NT2_TEST_EQUAL(nt2::any(nt2::Inf<vcT>()), nt2::True<sr_t>());
  NT2_TEST_EQUAL(nt2::any(nt2::Minf<vcT>()), nt2::True<sr_t>());
  NT2_TEST_EQUAL(nt2::any(nt2::Mone<vcT>()), nt2::True<sr_t>());
  NT2_TEST_EQUAL(nt2::any(nt2::Nan<vcT>()), nt2::True<sr_t>());
  NT2_TEST_EQUAL(nt2::any(nt2::One<vcT>()), nt2::True<sr_t>());
  NT2_TEST_EQUAL(nt2::any(nt2::Zero<vcT>()), nt2::False<sr_t>());
} // end of test for floating_
