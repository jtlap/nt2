//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.arithmetic toolbox - idivround/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 01/12/2010
///
#include <boost/simd/arithmetic/include/functions/idivround.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

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

NT2_TEST_CASE_TPL ( idivround_real__2_0,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::idivround;
  using boost::simd::tag::idivround_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<idivround_(T,T)>::type r_t;
  typedef iT wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::Inf<T>(), boost::simd::Inf<T>()), boost::simd::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::Minf<T>(), boost::simd::Minf<T>()), boost::simd::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::Nan<T>(), boost::simd::Nan<T>()), boost::simd::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<r_t>(), 0);
} // end of test for floating_

NT2_TEST_CASE_TPL ( idivround_unsigned_int__2_0,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::idivround;
  using boost::simd::tag::idivround_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<idivround_(T,T)>::type r_t;
  typedef iT wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );
  // specific values tests

  NT2_TEST_ULP_EQUAL(idivround(boost::simd::Five<T>(),boost::simd::Three<T>()), boost::simd::Two<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::Four<T>(),boost::simd::Three<T>()), boost::simd::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::Four<T>(),boost::simd::Zero<T>()), boost::simd::Valmax<r_t>(), 0);
   NT2_TEST_ULP_EQUAL(idivround(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<r_t>(), 0);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( idivround_signed_int__2_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::idivround;
  using boost::simd::tag::idivround_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<idivround_(T,T)>::type r_t;
  typedef iT wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::Five<T>(),boost::simd::Three<T>()), boost::simd::Two<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::Four<T>(),boost::simd::Three<T>()), boost::simd::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::Four<T>(),boost::simd::Zero<T>()), boost::simd::Valmax<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::Mfour<T>(),boost::simd::Zero<T>()), boost::simd::Valmin<r_t>(), 0);
   NT2_TEST_ULP_EQUAL(idivround(boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(idivround(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<r_t>(), 0);
} // end of test for signed_int_
