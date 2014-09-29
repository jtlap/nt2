//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/idivround.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/constant/constant.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/five.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/three.hpp>
#include <boost/simd/include/constants/mfour.hpp>

NT2_TEST_CASE_TPL ( idivround_real__2_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::idivround;
  using boost::simd::tag::idivround_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<idivround_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::Inf<vT>(), boost::simd::Inf<vT>()), boost::simd::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::Minf<vT>(), boost::simd::Minf<vT>()), boost::simd::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::Mone<vT>(), boost::simd::Mone<vT>()), boost::simd::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::Nan<vT>(), boost::simd::Nan<vT>()), boost::simd::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::One<r_t>(), 0);
} // end of test for floating_


NT2_TEST_CASE_TPL ( idivround_unsigned_int__2_0,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::idivround;
  using boost::simd::tag::idivround_;
  using boost::simd::native;
  typedef typename boost::dispatch::meta::call<idivround_(T,T)>::type r_t;

  NT2_TEST_ULP_EQUAL(idivround(boost::simd::Five<T>(),boost::simd::Three<T>()), boost::simd::Two<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::Four<T>(),boost::simd::Three<T>()), boost::simd::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::Four<T>(),boost::simd::Zero<T>()), boost::simd::Valmax<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<r_t>(), 0);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( idivround_signed_int__2_0,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::idivround;
  using boost::simd::tag::idivround_;
  using boost::simd::native;
  typedef typename boost::dispatch::meta::call<idivround_(T,T)>::type r_t;

  // specific values tests
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::Five<T>(),boost::simd::Three<T>()), boost::simd::Two<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::Four<T>(),boost::simd::Three<T>()), boost::simd::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::Four<T>(),boost::simd::Zero<T>()), boost::simd::Valmax<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::Mfour<T>(),boost::simd::Zero<T>()), boost::simd::Valmin<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<r_t>(), 0);
} // end of test for signed_int_
