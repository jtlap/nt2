//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 exponential toolbox - nthroot/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of exponential components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 08/12/2010
/// modified by jt the 07/04/2011
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/toolbox/exponential/include/nthroot.hpp>
// specific includes for arity 2 tests
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/abs.hpp>

NT2_TEST_CASE_TPL ( nthroot_real__2_0,  NT2_REAL_TYPES)
{
  
  using nt2::nthroot;
  using nt2::tag::nthroot_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<nthroot_(T,iT)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::result_of<nt2::meta::floating(T)>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(nthroot(T(256),iT(4)), T(4), 0);
  NT2_TEST_ULP_EQUAL(nthroot(T(8),iT(3)), T(2), 0);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Inf<T>(),iT(3)), nt2::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Inf<T>(),iT(4)), nt2::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Minf<T>(),iT(3)), nt2::Minf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Minf<T>(),iT(4)), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Mone<T>(),iT(3)), nt2::Mone<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Mone<T>(),iT(4)), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Nan<T>(),iT(3)), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Nan<T>(),iT(4)), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::One<T>(),iT(3)), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::One<T>(),iT(4)), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Zero<T>(),iT(3)), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Zero<T>(),iT(4)), nt2::Zero<r_t>(), 0);
} // end of test for real_

NT2_TEST_CASE_TPL ( nthroot_signed_int__2_0,  NT2_INTEGRAL_SIGNED_TYPES)
{
  
  using nt2::nthroot;
  using nt2::tag::nthroot_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<nthroot_(T,iT)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::result_of<nt2::meta::floating(T)>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(nthroot(T(-8),iT(3)), r_t(-2), 0);
  NT2_TEST_ULP_EQUAL(nthroot(T(8),iT(3)), r_t(2), 0);
  NT2_TEST_ULP_EQUAL(nthroot(T(81),iT(4)), r_t(3), 0);
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( nthroot_unsigned_int__2_0,  NT2_UNSIGNED_TYPES)
{
  
  using nt2::nthroot;
  using nt2::tag::nthroot_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<nthroot_(T,iT)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::result_of<nt2::meta::floating(T)>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(nthroot(T(8),iT(3)), r_t(2), 0);
  NT2_TEST_ULP_EQUAL(nthroot(T(81),iT(4)), r_t(3), 0);
} // end of test for unsigned_int_
