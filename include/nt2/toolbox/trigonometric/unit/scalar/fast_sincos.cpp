//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 trigonometric toolbox - fast_sincos/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of trigonometric components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by $author$ the $date$
/// modified by $author$ the $date$
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/toolbox/trigonometric/include/fast_sincos.hpp>
// specific includes for arity 1 tests
#include <nt2/toolbox/trigonometric/include/constants.hpp>

NT2_TEST_CASE_TPL ( fast_sincos_real__1,  NT2_REAL_TYPES)
{
  using nt2::fast_sincos;
  using nt2::tag::fast_sincos_;
  typedef typename nt2::meta::call<fast_sincos_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::result_of<nt2::meta::floating(T)>::type wished_r_t;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;


  // specific values tests
  NT2_TEST_ULP_EQUAL(  fast_sincos(-nt2::Pi<T>()), nt2::Zero<r_t>(), 0.75);
  NT2_TEST_ULP_EQUAL(  fast_sincos(-nt2::Pi<T>()/2), nt2::Mone<r_t>(), 0.75);
  NT2_TEST_ULP_EQUAL(  fast_sincos(-nt2::Pi<T>()/4), nt2::Sqrt_2o_2<r_t>(), 0.75);
  NT2_TEST_ULP_EQUAL(  fast_sincos(nt2::Inf<T>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  fast_sincos(nt2::Minf<T>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  fast_sincos(nt2::Nan<T>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(  fast_sincos(nt2::Pi<T>()), nt2::Zero<r_t>(), 0.75);
  NT2_TEST_ULP_EQUAL(  fast_sincos(nt2::Pi<T>()/2), nt2::One<r_t>(), 0.75);
  NT2_TEST_ULP_EQUAL(  fast_sincos(nt2::Pi<T>()/4), nt2::Sqrt_2o_2<r_t>(), 0.75);
  NT2_TEST_ULP_EQUAL(  fast_sincos(nt2::Zero<T>()), nt2::Zero<r_t>(), 0);
} // end of test for real_

NT2_TEST_CASE_TPL ( fast_sincos_unsigned_int__1,  NT2_UNSIGNED_TYPES)
{
  using nt2::fast_sincos;
  using nt2::tag::fast_sincos_;
  typedef typename nt2::meta::call<fast_sincos_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::result_of<nt2::meta::floating(T)>::type wished_r_t;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;


  // specific values tests
  NT2_TEST_ULP_EQUAL(  fast_sincos(nt2::Zero<T>()), nt2::Zero<r_t>(), 0);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( fast_sincos_signed_int__1,  NT2_INTEGRAL_SIGNED_TYPES)
{
  using nt2::fast_sincos;
  using nt2::tag::fast_sincos_;
  typedef typename nt2::meta::call<fast_sincos_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::result_of<nt2::meta::floating(T)>::type wished_r_t;

  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;


  // specific values tests
  NT2_TEST_ULP_EQUAL(  fast_sincos(nt2::Zero<T>()), nt2::Zero<r_t>(), 0);
} // end of test for signed_int_