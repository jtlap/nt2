//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.predicates toolbox - is_not_infinite/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.predicates components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 21/02/2011
///
#include <nt2/include/functions/is_not_infinite.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/simd/logical.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/mzero.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/true.hpp>
#include <nt2/include/constants/false.hpp>
#include <nt2/toolbox/constant/common.hpp>

#include <nt2/sdk/complex/complex.hpp>

NT2_TEST_CASE_TPL ( is_not_infinite_real__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::is_not_infinite;
  using nt2::tag::is_not_infinite_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<std::complex<T>, ext_t> cvT;
  typedef typename boost::dispatch::meta::call<is_not_infinite_(cvT)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type sr_t;

  // specific values tests
  NT2_TEST_EQUAL(is_not_infinite(nt2::Mzero<cvT>())[0], nt2::True<sr_t>());
  NT2_TEST_EQUAL(is_not_infinite(nt2::Inf<cvT>())[0], nt2::False<sr_t>());
  NT2_TEST_EQUAL(is_not_infinite(nt2::Minf<cvT>())[0], nt2::False<sr_t>());
  NT2_TEST_EQUAL(is_not_infinite(nt2::Mone<cvT>())[0], nt2::True<sr_t>());
  NT2_TEST_EQUAL(is_not_infinite(nt2::Nan<cvT>())[0], nt2::True<sr_t>());
  NT2_TEST_EQUAL(is_not_infinite(nt2::One<cvT>())[0], nt2::True<sr_t>());
  NT2_TEST_EQUAL(is_not_infinite(nt2::Zero<cvT>())[0], nt2::True<sr_t>());
} // end of test for floating_
