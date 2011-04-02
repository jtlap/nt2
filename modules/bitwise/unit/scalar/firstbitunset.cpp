//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 bitwise toolbox - firstbitunset/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of bitwise components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
/// modified by jt the 16/03/2011
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/toolbox/bitwise/include/firstbitunset.hpp>

NT2_TEST_CASE_TPL ( firstbitunset_real__1,  NT2_REAL_TYPES)
{
  
  using nt2::firstbitunset;
  using nt2::tag::firstbitunset_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<firstbitunset_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename nt2::meta::as_integer<T, unsigned>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(firstbitunset(nt2::Inf<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(firstbitunset(nt2::Minf<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(firstbitunset(nt2::Nan<T>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(firstbitunset(nt2::Signmask<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(firstbitunset(nt2::Zero<T>()), nt2::One<r_t>());
} // end of test for real_

NT2_TEST_CASE_TPL ( firstbitunset_signed_int__1,  NT2_INTEGRAL_SIGNED_TYPES)
{
  
  using nt2::firstbitunset;
  using nt2::tag::firstbitunset_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<firstbitunset_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename nt2::meta::as_integer<T, unsigned>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(firstbitunset(nt2::One<T>()), nt2::Two<r_t>());
  NT2_TEST_EQUAL(firstbitunset(nt2::Signmask<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(firstbitunset(nt2::Zero<T>()), nt2::One<r_t>());
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( firstbitunset_unsigned_int__1,  NT2_UNSIGNED_TYPES)
{
  
  using nt2::firstbitunset;
  using nt2::tag::firstbitunset_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<firstbitunset_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename nt2::meta::as_integer<T, unsigned>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(firstbitunset(nt2::One<T>()), nt2::Two<r_t>());
  NT2_TEST_EQUAL(firstbitunset(nt2::Zero<T>()), nt2::One<r_t>());
} // end of test for unsigned_int_
