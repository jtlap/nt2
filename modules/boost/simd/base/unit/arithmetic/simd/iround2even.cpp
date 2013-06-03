//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.arithmetic toolbox - iround2even/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 01/12/2010
///
#include <boost/simd/arithmetic/include/functions/iround2even.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/constant/constant.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( iround2even_real__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::iround2even;
  using boost::simd::tag::iround2even_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                                   ivT;
  typedef typename boost::dispatch::meta::call<iround2even_(vT)>::type r_t;


  // specific values tests
  NT2_TEST_ULP_EQUAL(iround2even(boost::simd::splat<vT>(1.4)), boost::simd::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(iround2even(boost::simd::splat<vT>(1.5)), boost::simd::Two<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(iround2even(boost::simd::splat<vT>(1.6)), boost::simd::Two<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(iround2even(boost::simd::splat<vT>(2.5)), boost::simd::Two<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(iround2even(boost::simd::Half<vT>()), boost::simd::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(iround2even(boost::simd::Inf<vT>()), boost::simd::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(iround2even(boost::simd::Mhalf<vT>()), boost::simd::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(iround2even(boost::simd::Minf<vT>()), boost::simd::Minf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(iround2even(boost::simd::Mone<vT>()), boost::simd::Mone<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(iround2even(boost::simd::Nan<vT>()), boost::simd::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(iround2even(boost::simd::One<vT>()), boost::simd::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(iround2even(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>(), 0);
} // end of test for floating_
