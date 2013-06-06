//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 operator toolbox - shift_right/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of operator components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <nt2/operator/include/functions/shift_right.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <nt2/constant/constant.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/three.hpp>


NT2_TEST_CASE_TPL ( shift_right_signed_int__2_0,  NT2_INTEGRAL_SIGNED_TYPES)
{

  using nt2::shift_right;
  using nt2::tag::shift_right_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<shift_right_(T,iT)>::type r_t;
  typedef r_t wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(shift_right(nt2::Mone<T>(),nt2::One<iT>()), nt2::Mone<r_t>());
  NT2_TEST_EQUAL(shift_right(nt2::One<T>(),nt2::One<iT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(shift_right(nt2::One<T>(),nt2::Zero<iT>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(shift_right(nt2::Zero<T>(),nt2::One<iT>()), nt2::Zero<r_t>());
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( shift_right_unsigned_int__2_0,  NT2_UNSIGNED_TYPES)
{

  using nt2::shift_right;
  using nt2::tag::shift_right_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<shift_right_(T,iT)>::type r_t;
  typedef r_t wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );
  // specific values tests
  NT2_TEST_EQUAL(shift_right(nt2::One<T>(),nt2::One<iT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(shift_right(nt2::One<T>(),nt2::Zero<iT>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(shift_right(nt2::Zero<T>(),nt2::One<iT>()), nt2::Zero<r_t>());
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( shift_right_real__2_0,  NT2_REAL_TYPES)
{

  using nt2::shift_right;
  using nt2::tag::shift_right_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<shift_right_(T,iT)>::type r_t;
  typedef r_t wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(shift_right(nt2::One<T>(),nt2::Zero<iT>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(shift_right(nt2::Zero<T>(),nt2::One<iT>()), nt2::Zero<r_t>());
} // end of test for floating_


NT2_TEST_CASE_TPL ( shift_right_unsigned_int__2_0_i,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::shift_right;
  using boost::simd::tag::shift_right_;
  typedef T r_type;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<shift_right_(T,iT)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );
  // specific values tests
  NT2_TEST_EQUAL(shift_right(T(2),(1)), boost::simd::One<T>());
  NT2_TEST_EQUAL(shift_right(boost::simd::Mone<T>(),(sizeof(r_type)*8-1)), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(shift_right(boost::simd::Mone<T>(),(sizeof(r_type)*8-2)), boost::simd::Three<r_t>());
  NT2_TEST_EQUAL(shift_right(boost::simd::One<T>(),(1)), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(shift_right(boost::simd::Zero<T>(),(1)), boost::simd::Zero<r_t>());
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( shift_right_signed_int__2_0_i,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::shift_right;
  using boost::simd::tag::shift_right_;
  typedef T r_type;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<shift_right_(T,iT)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(shift_right(-boost::simd::Four<T>(),1), -boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(shift_right(T(-2),(1)), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(shift_right(T(-3),(1)), -boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(shift_right(T(2),(1)), boost::simd::One<T>());
  NT2_TEST_EQUAL(shift_right(boost::simd::Mone<T>(),(sizeof(r_type)*8-1)), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(shift_right(boost::simd::Mone<T>(),(sizeof(r_type)*8-2)), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(shift_right(boost::simd::One<T>(),1), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(shift_right(boost::simd::Zero<T>(),1), boost::simd::Zero<r_t>());
} // end of test for signed_int_
